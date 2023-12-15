#include <iostream>
#include "CSocketClient.h"

int main(int n, const char* args) {
	std::cout << "HelloWorld" << std::endl;

	CSocketClient cSocketClient;
	cSocketClient.test();
}