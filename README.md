[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---

|	**Method**	|	**Time Complexity Bounds**	|	**Explanation**	|
|	---	|	---	|	---	|
|	```bool HashTable::insert(const std::string &key, const size_t &value);```	|	`O(1) <= T <= O(n)`	|	The hash function and bucket modulus are assumed to take constant time. The number of probes to take depends on the number of bucket collisions. So the best case is at least `O(1)`.	|
|	```bool HashTable::remove(const std::string &key);```	|	`O(1) <= T <= O(n)`	|	Similar functionality to `HashTable::insert`, in particular the probe sequence.	|
|	```bool HashTable::contains(const std::string &key) const;```	|	`O(1) <= T <= O(n)`	|	Similar functionality to `HashTable::remove`, except no key is removed, and if found, returns `true`. The overall time complexity bounds are similar to the previously defined methods.	|
|	```std::optional<size_t> HashTable::get(const std::string &key) const;```	|	`O(1) <= T <= O(n)`	|	Returns the value associated with the key if `HashTable::contains` returns `true`. The time complexity bounds is similar to the previously defined methods.	|
|	```size_t & HashTable::operator[](const std::string &key);```	|	`O(1) <= T <= O(n)`	|	Similar to `HashTable::get`, but it returns a reference to the value associated with the key, so the functionality of obtaining a value if the key exists are similar to the other methods. Thus the overall time complexity is at least `O(1)`.	|

Each method described above has the same functionality of probing each bucket because a key must be passed for each method. The key gets hashed, which determines the initial bucket index. Since a collision is not likely to occur, each function gets executed in its best case, which is `O(1)`. If multiple collisions occur with distinct keys all having the same initial bucket index, the number of probes increase, which a loop exists within the probing sequence. A single loop multiplies a linear factor into the worst-case bound, resulting in `O(n)`.

These 5 methods use that probing functionality to determine the resulting bucket index. In conclusion, the time complexity bounds for all 5 methods are `O(1) <= T <= O(n)`.
