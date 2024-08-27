#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void Print(int* data, size_t size_x, size_t size_y) {
	for (size_t i = 0; i < size_x; i++) {

		assert( (0 <= i && i < size_x) );

		for (size_t j = 0; j < size_y; j++) {

			assert( (0 <= j && j < size_y) );

			printf("data[%lu][%lu] = %d ", i, j, *(data + i * size_y + j));
		}
		printf("\n");
	}
}

int main() {

	int data[][4] = { {11, 12, 13, 14},
					  {21, 22, 23, 24},
					  {31, 32, 33, 34},
					  {41, 42, 43, 44},
					  {51, 52, 53, 54} };

	size_t size_x = (sizeof(data) / sizeof(data[0])),
		   size_y = (sizeof(data[0]) / sizeof(data[0][0]));

	Print((int*)data, size_x, size_y);

	return 0;
}
