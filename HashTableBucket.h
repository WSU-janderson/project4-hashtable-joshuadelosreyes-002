/**
 *	HashTableBucket.h
 */

#ifndef HASHTABLEBUCKET_H
#define HASHTABLEBUCKET_H

#include <string>

class HashTableBucket {
	private:
		enum class BucketType {

			/**
			 *	The bucket is non-empty and currently storing a
			 *	key-value pair.
			 */
			NORMAL,

			/**
			 *	The bucket has never had a key-value pair.
			 */
			ESS,

			/**
			 *	The bucket previously stored a key-value pair, but
			 *	that pair was removed from the table.
			 */
			EAR
		};

		std::string key;
		size_t value;
		BucketType bucketType;

	public:
		using enum BucketType;

		HashTableBucket();
		HashTableBucket(const std::string &key, const size_t &value);

		void load(const std::string &key, const size_t &value);

		std::string getKey() const;
		size_t & valueOf();

		void makeNormal();
		void makeESS();
		void makeEAR();

		bool isEmpty() const;
		bool isEmptySinceStart() const;
		bool isEmptyAfterRemove() const;

		friend std::ostream & operator<<(std::ostream &os, const HashTableBucket &bucket);
};

#endif
