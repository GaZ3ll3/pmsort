#include "pmsort.h"

#include <iostream>

// int val[] = {1,2,3,4,5,6,7,8,9,100,99,98,97,96,95,94,93};
int val[] = {1,3,2,4,5,7,8,6,10,9,8,6,7,9,10,11,9};
// double val[] = {0.5,0.8,0.7,1.0,1.5,1.3,0.11,0.32,1.45,1.90};
// double val[] = {0.5,0.7,0.8,1.0,1.5,0.11,0.32,1.45,1.90};

int compar(const void * a, const void *b){
	// std::cout << *(double*)a << " and " << *(double*)b << " result " << ( *(double*)a > *(double*)b ) << std::endl;
	return ( *(int*)a > *(int*)b );
}


int main(int argc, char const *argv[])
{
	size_t threads =  (size_t)omp_get_max_threads();

	// std::cout << "threads:" << threads << std::endl;


	pmsort(val, 17, sizeof(int), compar, threads);

	// merge(val,9, 5,4,sizeof(double),compar);
	for (int i = 0 ; i < 17; i++){
		std::cout << val[i] << std::endl;
	}
	return 0;
}