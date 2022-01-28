module;
#include <signal.h>
#include <sys/types.h>
#include <iostream>
export module signal_handler;
import explicit_enum;
import error_string;

export namespace SignalHandler {
	static bool _all_good = true;
	static pid_t unit;
	void signal_terminate(int){
		_all_good = false;
	};
	void signal_continue(int){};
	void SignalHandler( pid_t _unit ) {
		unit = _unit;
		signal( SIGUSR1, signal_continue );
		signal( SIGUSR2, signal_terminate );
	}
	void terminate() {
		int return_value;
		return_value = kill( unit, SIGUSR2 );
		if( return_value == ReturnValue::bad_kill ) {
			std::cerr << Error::kill_failed( unit, SIGUSR1 );
			exit( ReturnValue::bad_kill );
		}
	};
	void resume() {
		int return_value;
		return_value = kill( unit, SIGUSR1 );
		if( return_value == ReturnValue::bad_kill ) {
			std::cerr << Error::kill_failed( unit, SIGUSR1 );
			exit( ReturnValue::bad_kill );
		} else {
			pause();
		}
	}
	bool all_good() {
		return _all_good;
	}
};
