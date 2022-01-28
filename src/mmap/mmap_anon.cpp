module;
#include <sys/mman.h>
#include <iostream>
export module mmap;
import error_string;
import explicit_enum;

export namespace Mmap {
	template<typename T>
	void get_mapped_area( const int mapping_length, T*& mapped_area ) {
		mapped_area = static_cast< T* >( mmap( mapped_area, mapping_length,
											PROT_READ | PROT_WRITE,
											MAP_SHARED | MAP_ANONYMOUS,
		                                    MmapValue::anon_fd,
		                                    MmapValue::anon_offset ) );
		if ( mapped_area == MAP_FAILED ) {
			std::cerr << Error::mmap_failed( mapping_length );
			exit( ReturnValue::mmap_failed );
		}
	}
};
