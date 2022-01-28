module;
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
export module mmap;
import error_string;
import explicit_enum;

export namespace Mmap {
	enum {
		dont_have_fd,
	};
	template<typename T>
	void get_mapped_area( int& fd, const int mapping_length, T*& mapped_area ) {
		const char sentence[] = "fucking fuck stupid feature";
		const char directory_for_tmp_file[] = ".";
		if( fd == Mmap::dont_have_fd ) {
			fd = open( directory_for_tmp_file, O_TMPFILE | O_RDWR, O_TMPFILE | S_IRWXU );
			write( fd, sentence, sizeof( sentence ) ); // Why I should do this WTF
			if( fd == ReturnValue::open_fail ) {
				std::string filename = "temporary file in directory";
				std::cerr << Error::opening_file( filename + directory_for_tmp_file );
				exit( ReturnValue::error_opening_file );
			}
													   // otherwise I get Ошибка шины (стек памяти сброшен на диск)
		}

		// if( fd == 0 ) {
		// 	fd = open( ".some_unique_file", O_CREAT | O_TRUNC | O_RDWR, O_CREAT | S_IRWXU );
		// 	write( fd, sentence, sizeof( sentence ) ); // Why I should do this WTF
		// 											   // otherwise I get Ошибка шины (стек памяти сброшен на диск)
		// 	if( fd == -1 ) {
		// 		std::cerr << "can't open file";
		// 		exit(1);
		// 	}
		// }
		mapped_area = static_cast< T* >( mmap( NULL, mapping_length,
		                                       PROT_READ | PROT_WRITE | PROT_EXEC,
		                                       MAP_SHARED,
		                                       fd, MmapValue::no_offset ) );
		if ( mapped_area == MAP_FAILED ) {
			std::cerr << Error::mmap_failed( mapping_length );
			exit( ReturnValue::mmap_failed );
		}
	}
};
