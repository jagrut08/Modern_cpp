/*
 * print.h
 * Routines to pretty print sequential containers
 */

#ifndef SRC_COMMON_PRINT_H_
#define SRC_COMMON_PRINT_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


/*
"if constexpr (std::is_pointer_v<T>)" only works with raw pointers, and not smart pointers
Hence, creating isSharedPtr, and then using Tag Dispatch technique to print containers containing pointers as well as
containers containing primitive types
*/

template<typename T>
struct isSharedPtr : std::false_type {};

template<typename T>
struct isSharedPtr<std::shared_ptr<T>> : std::true_type {};

// Print values that the shared_ptrs within a container point to. ostr needs to be passed in as a ref, and not a pointer.
template <typename T>
void printHelper(std::ostringstream& ostr, const T& t, std::true_type) {
	int i = 0;
	std::for_each(std::cbegin(t), std::cend(t), [&i, &t, &ostr](const typename T::value_type ptr) {ostr << *ptr << (++i == t.size() ? "" : ", ");} );
}

// Print primitive types within containers, could also use std::for_each here
template <typename T>
void printHelper(std::ostringstream& ostr, const T& t, std::false_type) {
	std::copy(std::cbegin(t), std::prev(std::cend(t), 1), std::ostream_iterator<typename T::value_type>(ostr, ", "));
	if(t.size()) {
		ostr << *std::prev(std::end(t), 1);
	}
}
template<typename T>
void printContainer(const T& c){
	std::ostringstream ostr;
	ostr << "{";
	printHelper(ostr, c, isSharedPtr<typename T::value_type>{});
	ostr << "}";
	std::cout << ostr.str();
}

/*
template <typename T>
void printContainerOfContainers(const T& t) {
	std::for_each(std::cbegin(t), std::cend(t), printContainer);
}
*/
#endif /* SRC_COMMON_PRINT_H_ */
