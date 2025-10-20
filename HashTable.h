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
		HashTable(size_t initCapacity = 8);

		bool insert(std::string key, int value);
		bool remove(std::string key);
		bool contains(const std::string &key) const;

		std::optional<int> get(const std::string &key) const;

		int & operator[](const std::string &key);

		std::vector<std::string> keys() const;

		double alpha() const;

		size_t capacity() const;
		size_t size() const;

		friend std::ostream & operator<<(std::ostream &os, const HashTable &hashTable);

	private:
		std::vector<HashTableBucket> tableData;
};

#endif
