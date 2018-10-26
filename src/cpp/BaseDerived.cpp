/*
 * A pair of base and derived classes for experimentation.
 */

#include <iostream>
#include <stdexcept>

class Base {
public:
	Base() {
		std::cout << "Base ctor\n";
	}

	 ~Base() {
		std::cout << "Base dtor\n";
	}

};

class Derived : public Base {
public:
	Derived() {
		std::cout << "Derived ctor\n";
	}

	~Derived() {
		std::cout << "Derived dtor\n";
	}
};

/*
int main() {
	try {
	 	const Base &bRef = Derived(); // bRef has to be a const ref
	 	// ~Derived and then ~Base called when bRef goes out of scope

//		Base *bPtr = new Derived();
		// ~Derived and then ~Base called only if delete bPtr called
		// otherwise the memory leaks
//		delete bPtr;
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
*/


