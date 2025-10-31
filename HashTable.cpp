/**
 *	HashTable.cpp
 */

#include "HashTable.h"
#include <random>
#include <iostream>

/**
 *	Returns `true` if and only if `key` matches the bucket's key and that bucket is nonempty.
 */
bool normalAndEqual(const HashTableBucket &bucket, const std::string &key) {
	return (bucket.getKey() == key) && !bucket.isEmpty();
}

/**
 *	The internal capacity of the hash table is set to the initial
 *	capacity, if specified. Default is 8.
 */
HashTable::HashTable(size_t initCapacity) {
	this->length = 0;
	this->generate_permutation(initCapacity);
	this->tableData = std::vector<HashTableBucket>(initCapacity);
}

/**
 *	Returns the load factor of the table, which is `size / capacity`.
 */
double HashTable::alpha() const {
	return static_cast<double>(this->size()) / static_cast<double>(this->capacity());
}

/**
 *	Returns the number of buckets in the hash table.
 */
size_t HashTable::capacity() const {
	return this->tableData.size();
}

/**
 *	Returns the number of existing key-value pairs in the hash table.
 */
size_t HashTable::size() const {
	return this->length;
}

/**
 *	Generates a vector of offsets using random number generation.
 *
 *	Index `0` of the offsets vector is always `0`, and other indices
 *	starting at `1` are shuffled in-place.
 */
void HashTable::generate_permutation(const size_t length) {
	std::mt19937_64 s;
	std::vector<size_t> offsets(length);

	// Each element in the offsets vector starts with the indices themselves.
	for (size_t i = 0; i < offsets.size(); ++i) {offsets[i] = i;}

	// Then shuffle each element starting at index 1 with another element starting at index 1.
	// Shuffling size - 1 elements.
	for (size_t i = 1; i < offsets.size(); ++i) {
		size_t randomOffset, indexToSwap, temp;

		// Generate an integer between 1 to size - 2.
		// Offset cannot be 0 for a true swap under a subvector of length (size - 1).
		randomOffset = 1 + s() % (offsets.size() - 2);

		// Resolve to an index between 1 to size - 1.
		indexToSwap = 1 + (i + randomOffset - 1) % (offsets.size() - 1);

		// Then swap the elements between the two indices.
		temp = offsets[indexToSwap];
		offsets[indexToSwap] = offsets[i];
		offsets[i] = temp;
	}

	this->offsets = offsets;
}

/**
 *	@brief Inserts a new key-value pair into the table.
 *
 *	Returns `true` if a unique key is inserted. Also `size` is increased.
 *
 *	Returns `false` if a duplicate key is attempted to be inserted.
 *
 *	The hash code is determined using the key. It is then used modulo capacity
 *	as the bucket number in probe index `0`. If a probed bucket is occupied
 *	but the keys themselves are not equal, increment the probe sequence index
 *	until an `EAR` or `ESS` bucket is reached.
 *
 *	The time complexity is bounded to `O(1) <= T <= O(n)`.
 */
bool HashTable::insert(const std::string &key, const size_t &value) {
	bool uniqueInsert = true;

	/**
	 *	Determine the hash code for the string.
	 *	The hash itself modulo capacity is then the initial bucket number.
	 *	It is also the resolved bucket number at the 0th probe.
	 */
	const size_t bucketIndex = std::hash<std::string>{}(key) % this->capacity();

	/**
	 *	If a bucket is occupied, but the keys themselves are not equal, increment the
	 *	probe sequence index until an `EAR` or `ESS` bucket is reached.
	 */
	size_t probeIndex = 0, finalBucketIndex;
	while (true) {
		finalBucketIndex = (bucketIndex + this->offsets[probeIndex]) % this->capacity();
		HashTableBucket &bucket = this->tableData[finalBucketIndex];
		if ((bucket.getKey() == key) || bucket.isEmpty()) {
			uniqueInsert &= (bucket.getKey() != key);
			if (bucket.isEmpty()) {bucket.load(key, value);}
			else {bucket.valueOf() = value;}
			break;
		} else {
			++probeIndex;
			continue;
		}
	}

	if (uniqueInsert) {++this->length;}
	if (this->alpha() >= 0.5) {this->resize();}
	return uniqueInsert;
}

/**
 *	@brief Returns `true` if and only if a specified key exists in the table.
 *
 *	Starting with the initial bucket derived from the key's hash, the probes
 *	are traversed in addition to checking for equality of a bucket's contained
 *	key. The probes still continue on `EAR` buckets, but it stops if either a
 *	bucket's contained key is equivalent to the specified key or an `ESS` bucket
 *	is reached.
 *
 *	The time complexity is bounded to `O(1) <= T <= O(n)`.
 */
bool HashTable::contains(const std::string &key) const {
	const size_t bucketIndex = std::hash<std::string>{}(key) % this->capacity();

	size_t probeIndex = 0, finalBucketIndex;
	while (true) {
		finalBucketIndex = (bucketIndex + this->offsets[probeIndex]) % this->capacity();
		HashTableBucket bucket = this->tableData[finalBucketIndex];
		if (normalAndEqual(bucket, key)) {return true;}
		else if (bucket.isEmptySinceStart()) {return false;}
		else {++probeIndex; continue;}
	}
}

/**
 *	@brief Returns `true` if and only if a specified key exists in the table,
 *		in addition, removes that key in the table.
 *
 *	A successful removal of a key sets its corresponding bucket to `EAR` and
 *	decrements `size`.
 *
 *	The time complexity is bounded to `O(1) <= T <= O(n)`.
 */
bool HashTable::remove(const std::string &key) {
	bool keyRemoved = false;
	const size_t bucketIndex = std::hash<std::string>{}(key) % this->capacity();

	size_t probeIndex = 0, finalBucketIndex;
	while (true) {
		finalBucketIndex = (bucketIndex + this->offsets[probeIndex]) % this->capacity();
		HashTableBucket bucket = this->tableData[finalBucketIndex];
		if (normalAndEqual(bucket, key) || bucket.isEmptySinceStart()) {
			keyRemoved |= (bucket.getKey() == key);
			if (keyRemoved) {bucket.makeEAR();}
			break;
		} else {
			++probeIndex;
			continue;
		}
	}

	if (keyRemoved) {--this->length;}
	return keyRemoved;
}

/**
 *	If the key is found in the table, return the value that is associated with that key.
 *	Otherwise, returns `nullopt`, which is value-equivalent for `nullptr` without using
 *	pointers.
 *
 *	The time complexity is bounded to `O(1) <= T <= O(n)`.
 */
std::optional<size_t> HashTable::get(const std::string &key) const {
	const size_t bucketIndex = std::hash<std::string>{}(key) % this->capacity();

	size_t probeIndex = 0, finalBucketIndex;
	while (true) {
		finalBucketIndex = (bucketIndex + this->offsets[probeIndex]) % this->capacity();
		HashTableBucket bucket = this->tableData[finalBucketIndex];
		if (normalAndEqual(bucket, key)) {return std::optional<size_t>(bucket.valueOf());}
		else if (bucket.isEmptySinceStart()) {return std::nullopt;}
		else {++probeIndex; continue;}
	}
}

/**
 *	Returns a reference to the value associated with the specified key.
 *	If a key is not found in the table, this method is ill-formed, causing
 *	undesirable behavior.
 *
 *	This is different than inserting a new key with its value if the key
 *	is not in the table.
 *
 *	The time complexity is bounded to `O(1) <= T <= O(n)`.
 */
size_t & HashTable::operator[](const std::string &key) {
	const size_t bucketIndex = std::hash<std::string>{}(key) % this->capacity();

	size_t probeIndex = 0, finalBucketIndex;
	while (true) {
		finalBucketIndex = (bucketIndex + this->offsets[probeIndex]) % this->capacity();
		HashTableBucket bucket = this->tableData[finalBucketIndex];
		if (normalAndEqual(bucket, key) || bucket.isEmptySinceStart()) {
			return bucket.valueOf();
		} else {++probeIndex; continue;}
	}
}

/**
 *	Returns a vector of keys that are currently in the table.
 *	Every bucket is traversed in the hash table. If a normal bucket is passed,
 *	its key gets pushed into the vector.
 */
std::vector<std::string> HashTable::keys() const {
	std::vector<std::string> keyList;

	for (HashTableBucket bucket : this->tableData) {
		if (!bucket.isEmpty()) {
			keyList.push_back(bucket.getKey());
		}
	}

	keyList.shrink_to_fit();
	return keyList;
}

/**
 *	Resizing the hash table changes the effective capacity, usually by doubling
 *	the current capacity. 
 *
 *	Because the capacity is changed, all internal vectors need to be sized
 *	correctly and to have every normal bucket in the previous vector containing
 *	table data be transferred to new bucket indices in the new table.
 */
void HashTable::resize() {
	const size_t newSize = this->capacity() * 2;
	this->generate_permutation(newSize);
	std::vector<HashTableBucket> newTableData(newSize);

	for (HashTableBucket bucket : this->tableData) {
		if (!bucket.isEmpty()) {
			std::string bucketKey = bucket.getKey();
			const size_t bucketIndex = std::hash<std::string>{}(bucketKey) % newSize;

			size_t probeIndex = 0, finalBucketIndex;
			while (true) {
				finalBucketIndex = (bucketIndex + this->offsets[probeIndex]) % newSize;
				HashTableBucket &bucket2 = newTableData[finalBucketIndex];
				if ((bucket2.getKey() == bucketKey) || bucket2.isEmpty()) {
					bucket2 = bucket;
					break;
				} else {
					++probeIndex;
					continue;
				}
			}
		}
	}

	this->tableData = newTableData;
}

/**
 *	Prints all contents of a hash table by printing each normal bucket.
 *	Empty buckets are not included in printing.
 *
 *	The output representation of a hash table can be seen as:
 *	`[0: <key0, value0>, 1: <key1, value1>, ...]`
 *	with each index containing a normal bucket residing in that index.
 */
std::ostream & operator<<(std::ostream &os, const HashTable &hashTable) {
	size_t printedBuckets = 0;
	os << std::string{"["};
	for (size_t bucketIndex = 0; bucketIndex < hashTable.capacity(); ++bucketIndex) {
		HashTableBucket bucket = hashTable.tableData[bucketIndex];
		if (!bucket.isEmpty()) {
			if (printedBuckets > 0) {os << std::string{", "};}
			os << bucketIndex << std::string{": "} << bucket;
			++printedBuckets;
		}
	}
	os << std::string{"]"};
	return os;
}
