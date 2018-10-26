/*
 * 
 * Delete odd numbered element from std::map.
 * */

#include <print.h>

#include <iostream>
#include <map>
#include <stdexcept>
#include <utility>

void deleteOddNumberedElements(std::map<int, int>*  mPtr) {
	if(!mPtr) {
		return;
	}

	using mapIter = std::map<int, int>::iterator;

	for(mapIter it = std::begin(*mPtr); it != std::end(*mPtr); ++it) {
		it = mPtr->erase(it); // it will point to the element after the element that was deleted

		if(it == mPtr->end()) { // For odd-sized maps, we hit end() after deletion
			break;
		}
	}

	/*
	 * One can delete elements from a std::map while iterating over it in this case. Refer to
	 * http://www.cplusplus.com/reference/map/map/erase/
	 * "Iterators, pointers and references referring to elements removed by the function are invalidated.
	 * All other iterators, pointers and references keep their validity."
	 * */
}
/*
int main() {
	try {
		std::map<int, int> m;
		const int cnt = 3; // 0, 1, 2, 3,

		for(int i = 1; i <= cnt; ++i) {
			m[i] = i;
		}

		std::cout << "Before\n";
		printContainer(m);

		deleteOddNumberedElements(&m);

		std::cout << "\nAfter\n";
		printContainer(m);

	} catch(const std::exception& e) {
		std::cerr << "Exception in main(): " << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
*/
