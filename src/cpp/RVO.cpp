/*
 * Experiment with RVO
 */

#include <iostream>
#include <stdexcept>
#include <utility>

class Base {
	char val;
public:
	Base() : val('\0') {
		std::cout << "Base default ctor\n";
	}

	Base(const char c) : val(c) {
		std::cout << "Base one-arg ctor " << "for " << val << '\n';
	}

	Base(const Base& b) {
		std::cout << "Base cctor " << "for " << val << '\n';
		val = b.val;
	}

	// Explicitly defined move constructor means copy assignment implicitly deleted
	// So copy assignment operator should be defined explicitly
	Base(const Base&& b) {
		std::cout << "Base mctor " << "for " << val << '\n';
		val = std::move(b.val);
	}

   ~Base() {
		std::cout << "Base dtor " << "for " << val << '\n';
	}

   Base& operator =(const Base& b) {
		std::cout << "Base cao " << "for " << val << '\n';
		val = b.val;
		return *this;
   }

};

Base getBase() {
	Base tmp('t');
	return tmp;
}
/*
int main() {
	try {
	//	const Base b('b'), c('c');
	//	b = c; // Copy assignment

	//	const Base& b = getBase(); // RVO observed on clang/gcc
	//	Base&& b = getBase(); // Ditto
	//	Base& b = getBase(); // Compilation error - error: non-const lvalue reference to
		// type 'Base' cannot bind to a temporary of type 'Base'

	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	} catch(...) {
		std::cerr << "Unexpected error, main() returning -999\n" << '\n';
		return -999;
	}
}
*/


