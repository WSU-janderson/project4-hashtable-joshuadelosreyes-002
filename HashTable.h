/**
 *	HashTable.h
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <optional>
#include "HashTableBucket.h"

class HashTable {
	public:

		/**
		 *	Placeholder value to store the default capacity for the hash table.
		 *
		 *	Required for `HashTableTests.cpp`.
		 */
		static constexpr size_t DEFAULT_INITIAL_CAPACITY = 8;

		HashTable(size_t initCapacity = DEFAULT_INITIAL_CAPACITY);

		bool insert(const std::string &key, const size_t &value);
		bool remove(const std::string &key);
		bool contains(const std::string &key) const;

		std::optional<size_t> get(const std::string &key) const;

		size_t & operator[](const std::string &key);

		std::vector<std::string> keys() const;

		double alpha() const;

		size_t capacity() const;
		size_t size() const;

		friend std::ostream & operator<<(std::ostream &os, const HashTable &hashTable);

	private:
		std::vector<size_t> offsets;
		std::vector<HashTableBucket> tableData;

		size_t length;

		void generate_permutation(const size_t length);
		void resize();
};

#endif
