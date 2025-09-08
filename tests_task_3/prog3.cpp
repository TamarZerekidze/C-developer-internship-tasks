#include <iostream>
#include <string>

int main() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::cout << "prog3" << line << std::endl;
	}
	return 0;
}