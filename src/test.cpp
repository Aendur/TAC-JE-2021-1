#include <iostream>

class Singletest {
private:
	static Singletest * instance;
	Singletest(int);

public:
	static Singletest & GetInstance(void);
	~Singletest(void);
};

Singletest * Singletest::instance = nullptr;

Singletest & Singletest::GetInstance(void) {
	if (Singletest::instance == nullptr) {
		Singletest * test = new Singletest(3);
		std::cout << "new pointer " << test << std::endl;
		Singletest::instance = test;
	}
	return *Singletest::instance;
}
Singletest::Singletest(int x) {
	std::cout << "this " << this << " x " << x << std::endl;
}

int main() {
	Singletest::GetInstance();
}