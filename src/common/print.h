/*
 * print.h
 * Routines to pretty print sequential containers
 */

#ifndef SRC_COMMON_PRINT_H_
#define SRC_COMMON_PRINT_H_

#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/*
 * https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time/31105859#31105859
 * */
//specialize a type for all of the STL containers.
namespace is_stl_container_impl{
  template <typename T>       struct is_stl_container:std::false_type{};
  template <typename T, std::size_t N> struct is_stl_container<std::array    <T,N>>    :std::true_type{};
  template <typename... Args> struct is_stl_container<std::vector            <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::deque             <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::list              <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::forward_list      <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::set               <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::multiset          <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::map               <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::multimap          <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::unordered_set     <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::unordered_multiset<Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::unordered_map     <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::unordered_multimap<Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::stack             <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::queue             <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::priority_queue    <Args...>>:std::true_type{};
}

//type trait to utilize the implementation type traits as well as decay the type
template <typename T> struct is_stl_container {
  static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};

/*
* "if constexpr (std::is_pointer_v<T>)" only works with raw pointers, and not smart pointers. Hence, creating isSharedPtr<>
*/

template<typename T>
struct isSharedPtr : std::false_type {};

template<typename T>
struct isSharedPtr<std::shared_ptr<T>> : std::true_type {};

template <typename T>
void printFunc(std::ostream& out, const std::shared_ptr<T>& t) {
	if(t) {
		out << *t;
	} else {
		throw std::runtime_error("Encountered nullptr while printing!");
	}
}

template <typename T>
void printFunc(std::ostream& out, const T& t) {
	out << t;
}

/*
 * Simple implementation that suits my needs, only for STL containers - a comprehensive version can be found here
 * http://louisdx.github.io/cxx-prettyprint/
 * */
template<typename T>
void printContainer(const T& t, const std::string delim = ", "){
	// If it's a container of containers, recurse to the leaf-level containers first
	if constexpr(is_stl_container<typename T::value_type>::value) {
		std::for_each(std::cbegin(t), std::cend(t), [&t, &delim](const auto& val) {printContainer(val, delim);}); // auto works in C++14 onwards
	} else {
		// Print a leaf-level container
		std::ostringstream ostr;
		//ostr << "{";
		int i = 0;
		auto printLambda = [&i, &t, &ostr, &delim](const typename T::value_type valueType) {
			printFunc(ostr, valueType);
			ostr << (++i == t.size() ? "" : delim);
		};

		std::for_each(std::cbegin(t), std::cend(t), printLambda);
		//ostr << "}\n";
		std::cout << ostr.str();

		// Alternate implementation using constexpr (C++17). Has separate branches for primitive types vs. smart pointers.
			/*
			if constexpr (isSharedPtr<typename T::value_type>{}) {
				int i = 0;
				auto printLambda = [&i, &t, &ostr, &delim](const typename T::value_type ptr) {ostr << *ptr << (++i == t.size() ? "" : delim); };
				std::for_each(std::cbegin(t), std::cend(t), printLambda);
			} else {
				// printLamda could be used here as well, but trying a different technique
				std::copy(std::cbegin(t), std::prev(std::cend(t), 1), std::ostream_iterator<typename T::value_type>(ostr, delim.c_str()));
				if(t.size()) {
					ostr << *std::prev(std::end(t), 1);
				}
			}
		*/

	}
}

#endif /* SRC_COMMON_PRINT_H_ */
