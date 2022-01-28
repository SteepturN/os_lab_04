#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/mman.h>

import explicit_enum;
import error_string;
import read_input;
import mmap;
import exec_arg;
import signal_handler;

int main() {
	std::string pathname;
	ReadInput::read_string( pathname );

	int* mapped_area = nullptr;
	const int mapping_length = 1;
	Mmap::get_mapped_area< int >( mapping_length, mapped_area );

	char** exec_arg;
	ExecArg::make_execve_arg< void* >( mapped_area, pathname, exec_arg );

	// for( int i = 0; i <= pathname.size(); ++i ) {
	// 	std::cout << static_cast< int >( pathname[ i ] ) << '\n';
	// }
	// std::cout << '\n';
	// for( int i = 0; exec_arg[2][i] != '\0'; ++i ) {
	// 	std::cout << static_cast< int >( exec_arg[2][ i ] ) << '\n';
	// }

	pid_t child_pid = fork();
	if( child_pid == ReturnValue::bad_fork ) {
		std::cerr << Error::forking_process( getpid() );
		return ReturnValue::error_forking_process;
	} else if( child_pid == ReturnValue::fork_child_program ) {
		int exec_return_value = execv( pathname.c_str(), exec_arg );
		if( exec_return_value == ReturnValue::bad_exec ) {
			std::cerr << Error::executing_program( pathname );
			return ReturnValue::error_executing_program;
		}
	}

	SignalHandler::SignalHandler( child_pid );
	bool all_good = true;
	int number = 0;
	//SignalHandler::resume();
	while( all_good ) {
		std::cin >> number;
		if( !std::cin.good() ) {
			all_good = false;
			SignalHandler::terminate();
		} else {
			std::cout << "read number: " << number;
			mapped_area[ 0 ] = number;
			std::cout << "; mapped_area = " << mapped_area[ 0 ] << std::endl;
			SignalHandler::resume();
			all_good = SignalHandler::all_good();
		}
	}
	munmap(mapped_area, mapping_length);

	return ReturnValue::nice;
}
