module;
#include <string>
#include <iostream>
export module read_input;

export namespace ReadInput {
	void read_string( std::string& str ) {
		std::cin >> str;
	}
};
