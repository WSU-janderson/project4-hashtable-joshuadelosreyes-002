/**
 *	HashTableDebug.cpp
 *
 *	Write your tests in this file.
 */

#include "HashTable.h"
#include <iostream>

int main() {
	HashTable h1;

	/**
	 *	// TODO:	contains() after remove() still returns true.
	 */

	{
		bool b;
		h1.insert("CAR", 101);
		b = h1.contains("CAR");
		std::cout << (b ? "true" : "false") << "\n"; // expected true
		b = h1.remove("CAR");
		std::cout << (b ? "true" : "false") << "\n"; // expected true
		b = h1.contains("CAR");
		std::cout << (b ? "true" : "false") << "\n"; // expected false
	}
	std::cout << "\n";

	/**
	 *	// TODO:	get() still returns a value after remove().
	 */

	{
		std::optional<size_t> v1;
		h1.insert("GAR", 102);
		v1 = h1.get("GAR");
		if (v1) {
			std::cout << *v1 << "\n";
		} else {
			std::cout << "nullopt\n";
		} // expected 102
		h1.remove("GAR");
		v1 = h1.get("GAR");
		if (v1) {
			std::cout << *v1 << "\n";
		} else {
			std::cout << "nullopt\n";
		} // expected nullopt
	}
	std::cout << "\n";

	/**
	 *	// TODO:	operator[] on write still hasn't updated value.
	 */

	{
		h1.insert("OOW", 103);
		std::cout << h1["OOW"] << "\n"; // expected 103
		h1["OOW"] = 203;
		std::cout << h1["OOW"] << "\n"; // expected 203
	}
	std::cout << "\n";

	return 0;
}
