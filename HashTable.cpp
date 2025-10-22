/**
 *	HashTable.cpp
 */

#include "HashTable.h"

/**
 *	The internal capacity of the hash table is set to the initial
 *	capacity, if specified. Default is 8.
 */
HashTable::HashTable(size_t initCapacity = 8) {
	this->offsets = std::vector<size_t>(initCapacity);
	this->tableData = std::vector<HashTableBucket>(initCapacity);
}

/**
 *	Returns the load factor of the table, which is `size / capacity`.
 */
double HashTable::alpha() const {
	return static_cast<double>(this->size()) / static_cast<double>(this->capacity());
}


