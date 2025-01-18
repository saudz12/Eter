#include "ConsolePlayableGUI.h"

//class idk {
//	int a;
//	int b;
//	int c;
//public:
//
//	idk() {
//		a = 2;
//		b = 3;
//		c = 4;
//	}
//	idk(int a, int b, int c) :
//		a{ a }, b{ b }, c{ c } {
//	}
//	void set(int a, int b, int c) {
//		this->a = a;
//		this->b = b;
//		this->c = c;
//	}
//	friend std::ostream& operator<<(std::ostream& os, const idk& item) {
//		os << item.a << item.b << item.c;
//		return os;
//	}
//};

int main()
{
	GameView test;
	test.Loop();
	
	/*char x = 'a';

	int16_t b = int16_t(x);

	std::cout << b;*/
	
	//int a = 3;
	//int b = 1;
	/*int a = 100;
	int* b = &a;
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	int c = std::move(a);
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;

	std::deque<idk> ex;
	ex.push_back(idk{0, 0, 0});
	ex.push_back(idk{1, 1, 1});
	auto d = &ex.back();
	std::cout << "d: " << d << std::endl;

	std::deque<idk> az;
	az.push_back(std::move(ex[1]));
	ex.pop_back();
	ex.pop_back();
	az.push_back(idk{2, 2, 2});
	std::cout << "d: " << d << std::endl;
	std::cout << "d: " << *d << std::endl;
	az[0].set(9, 9, 9);
	std::cout << "d: " << *d << std::endl;*/


	return 0;
}