/**
 *	HashTableBucket.cpp
 *
 *	Definitions of all the methods declared in the HashTableBucket class.
 */

#include "HashTableBucket.h"
#include <iostream>

/**
 *	The default constructor sets the bucket type to `ESS`
 *	(empty since start).
 */
HashTableBucket::HashTableBucket() : bucketType(ESS) {}

/**
 *	Sets the bucket type to `NORMAL`, as well as initializing
 *	the key and value for this bucket.
 */
HashTableBucket::HashTableBucket(const std::string &key, const size_t &value) {this->load(key, value);}

/**
 * 	A key-value pair is assigned to this bucket, which also sets the
 * 	bucket type to `NORMAL`.
 */
void HashTableBucket::load(const std::string &key, const size_t &value) {
	this->makeNormal();
	this->key = key;
	this->value = value;
}

/** Returns the key contained in this bucket. */
std::string HashTableBucket::getKey() const {return this->key;}

/** Sets the bucket type to `NORMAL`. */
void HashTableBucket::makeNormal() {this->bucketType = NORMAL;}

/** Sets the bucket type to `ESS`. */
void HashTableBucket::makeESS() {this->bucketType = ESS;}

/** Sets the bucket type to `EAR`. */
void HashTableBucket::makeEAR() {this->bucketType = EAR;}

/** If the bucket is normal, this should return `false`. */
bool HashTableBucket::isEmpty() const {
	return this->isEmptySinceStart() || this->isEmptyAfterRemove();
}

/** Returns `true` if the bucket type is set to `ESS`. */
bool HashTableBucket::isEmptySinceStart() const {
	return this->bucketType == ESS;
}

/** Returns `true` if the bucket type is set to `EAR`. */
bool HashTableBucket::isEmptyAfterRemove() const {
	return this->bucketType == EAR;
}

/**
 *	Prints a string representation of a bucket which can contain a
 *	key-value pair. If this bucket is empty, it should indicate the
 *	bucket type.
 *
 *	The key-value pair can be represented as `<key, value>`. 
 */
std::ostream & operator<<(std::ostream &os, const HashTableBucket &bucket) {
	switch (bucket.bucketType) {
		case HashTableBucket::NORMAL: {
			os << "<" << bucket.key << ", " << bucket.value << ">";
		} case HashTableBucket::ESS: {
			os << "ESS";
		} case HashTableBucket::EAR: {
			os << "EAR";
		}
	}
	return os;
}
