/**
 *	HashTable.cpp
 */

#include "HashTable.h"
#include <random>

/**
 *	The internal capacity of the hash table is set to the initial
 *	capacity, if specified. Default is 8.
 */
HashTable::HashTable(size_t initCapacity = 8) {
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
 *	At its worst case, the time complexity is at most `O(n)`.
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
			else {bucket.setValue(value);}
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
