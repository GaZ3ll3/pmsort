#include <omp.h>
#include <cstring>
#include <cstdlib>

#include <iostream>


#define MERGE_LIM 20

void msort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*));

void pmsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*), 
            size_t threads);

void merge (void* base, size_t num, size_t num1, 
	size_t num2, size_t size,
    int (*compar)(const void*,const void*));