#include "pmsort.h"



void msort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*)){
  	if (num <= MERGE_LIM){
  		// std::cout << "qsort" << std::endl;
  		qsort(base, num, size, (*compar));
  	}
	else
	{
		if (size <= 1) return;
		// std::cout << "split" << std::endl;
		msort(base, num/2, size, (*compar));
		msort((void*)((char*)base + (num/2)*size), num - num/2, size, (*compar));
	}

		merge(base, num, num/2, num - (num/2), size, (*compar));

}

void pmsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*) ,
            size_t threads){
 
	// size_t threads =  (size_t)omp_get_thread_num();

	// std::cout << "threads:" << threads << std::endl;

	if (threads == 1){
		msort(base, num, size, (*compar));
	}
	else if (threads > 1){
		#pragma omp parallel sections
		{
			#pragma omp section
			pmsort(base, num/2, size,(*compar), threads/2);
			#pragma omp section
			pmsort((void*)((char*)base + (num/2)*size), num - num/2, size, (*compar), threads - threads/2);
		}
	}

	merge(base, num, num/2, num - num/2, size, (*compar));
}

void merge (void* base, size_t num, size_t num1, 
	size_t num2, size_t size,
    int (*compar)(const void*,const void*)){

	int i, j, k;
  	register char* a = (char*)base;
  	register char* b = a + num1*size;
  	char *c;

  	if (!compar((void*)(a + (num1-1)*size), (void*)(b))) return;

  	c = (char *)malloc(num2 * size);
  	memcpy(c, b, num2 * size);

 	i = num1 - 1; j = num2 - 1; k = num - 1;
	while (i >= 0 && j >= 0)
	{
		if (compar((void*)(a + i*size), (void*)(c + j*size)))
			// *((char*)base + (k--)*size) = *(a + (i--)*size);
			memcpy((char*)base + (k--)*size,a + (i--)*size,size);
		else
			// *((char*)base + (k--)*size) = *(c + (j--)*size);
			memcpy((char*)base + (k--)*size,c + (j--)*size,size);
	}
	while (j >= 0){
		// *((char*)base + (k--)*size) = *(c + (j--)*size);
		memcpy((char*)base + (k--)*size,c + (j--)*size,size);
	} 
	free(c);

}