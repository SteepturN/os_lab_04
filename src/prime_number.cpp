module;
#include <set>
#include <cmath>

export module prime_number;


void put_all_primes_until( std::set<int>& primes, int num );

export bool is_prime( const int& number ) {
	static std::set< int > primes{ 2, 3, 5, 7, 11, 13 };
	if( number < 2 ) return false;
	if( primes.count( number ) ) return true;
	int sqrt_num = std::trunc( std::sqrt( number ) );
	if( sqrt_num > *primes.rbegin() )
		put_all_primes_until( primes, sqrt_num );
	for( auto another_prime : primes )
		if( number % another_prime == 0 )
			return false;

	primes.insert( number );

	return true;
}
void put_all_primes_until( std::set<int>& primes, int num ) {
	int max_exist = *( primes.rbegin() );
	if( max_exist > num ) return;

	for( int i = ( max_exist - max_exist % 6 ) + 6; i <= num; i += 6 ) {
		is_prime( i - 1 );
		is_prime( i + 1 ); //it pushes them for u
	}
}
