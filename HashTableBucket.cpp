/**
 *	HashTableBucket.cpp
 */

#include "HashTableBucket.h"

/**
 *	The default constructor sets the bucket type to `ESS`
 *	(empty since start).
 */
HashTableBucket::HashTableBucket() : bucketType(ESS) {}

/**
 *	Sets the bucket type to `NORMAL`, as well as initializing
 *	the key and value for this bucket.
 */
HashTableBucket::HashTableBucket(std::string key, int value) {this->load(key, value);}

/**
 * 	A key-value pair is assigned to this bucket, which also sets the
 * 	bucket type to `NORMAL`.
 */
void HashTableBucket::load(std::string key, int value) {
	this->makeNormal();
	this->key = key;
	this->value = value;
}

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
