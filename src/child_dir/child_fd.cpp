#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
import mmap;
import exec_arg;
import prime_number;
import explicit_enum;
import signal_handler;

int main( int argc, char** argv ) {
	int fd;
	const int mapping_length = 100;
	int* mapped_area = nullptr;
	if( argc != 3 ) //name, ptr, ptr_mask
		return ReturnValue::error_not_enough_args;
	ExecArg::get_execve_arg< int >( fd, argv );

	std::fstream file( "numbers.ans", std::ios::trunc | std::ios::out );
	int number = 0;
	bool all_good = true;
	std::cout << "accessing signal handler:..." << std::endl;
	SignalHandler::SignalHandler( getppid() );

	Mmap::get_mapped_area(fd, mapping_length, mapped_area);
	std::cout << "child: mapped_area = " << mapped_area << '\n';
	SignalHandler::resume();
	all_good = SignalHandler::all_good();
	while( all_good ) {
		std::cout << "accessing mapped_area:..." << std::endl;
		number = mapped_area[ 0 ];
		std::cout << "success: " << number << std::endl;
		bool negative = number < 0;
		bool prime = false;
		if( !negative ) {
			prime = is_prime(number);
		}
		bool num_is_correct = !( negative || prime );
		if( num_is_correct ) {
			std::cout << "correct" << std::endl;
			file << std::to_string(number) << std::endl;
			SignalHandler::resume();
		} else {
			std::cout << "incorrect" << std::endl;
			SignalHandler::terminate();
			all_good = false;
		}
		all_good = SignalHandler::all_good() && all_good;
	}
	file.close();
	return ReturnValue::nice;
}
