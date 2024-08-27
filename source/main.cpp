#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// TODO:
//  2) перемножение матриц, плюс обработка ошибок
//  3) транспонирование матриц
//	4) все через указательную арифметику

struct Matrix {
	int* data;
	size_t size_x;
	size_t size_y;
};

void RandPull(Matrix* data);
void MatrixSum(Matrix* data);
void Print(Matrix* data);
void ThreeMatricesMaker(Matrix* data);

void MatrixMul(Matrix* data) {
	if (data[0].size_x == data[1].size_y) {

		size_t size_x = data[1].size_x, size_y = data[1].size_y;

		for (size_t i = 0; i < size_x; i++) {

			assert( (0 <= i && i < size_x) );

			for (size_t j = 0; j < size_y; j++) {

				assert( (0 <= j && j < size_x) );

				int p = 0;
				for (size_t k = 0; k < size_x; k++) {
					p += *(data[1].data + (i + k) * size_y + j) *
						 *(data[0].data + k);
				}
				*(data[2].data + i * size_x + j) = p;
			}
		}

		printf("----- Матрица произведения -----");
		Print(&data[2]);
	}
	else {
		printf("Condition of multiple of matrices is not followed \n");
	}
}

void MatrixSum(Matrix* data) {
	if (data[0].size_x == data[1].size_x && data[0].size_y == data[1].size_y) {
		for (size_t i = 0; i < data[0].size_x; i++) {

			assert( (0 <= i && i < data[0].size_x) );

			for (size_t j = 0; j < data[0].size_x; j++) {

				assert( (0 <= j && j < data[0].size_x) );

				*(data[2].data + i * data[2].size_x + j) =
				*(data[0].data + i * data[0].size_x + j) + *(data[1].data + i * data[1].size_x + j);
			}
		}

		printf("----- Матрица суммы ---- \n");
		Print(&data[2]);
	}
	else {
		printf("Different dimensions of matrices \n");
	}
}

void Print(Matrix* data) {
	for (size_t i = 0; i < data->size_x; i++) {

		assert( (0 <= i && i < data->size_x) );

		for (size_t j = 0; j < data->size_y; j++) {

			assert( (0 <= j && j < data->size_y) );

			printf("%2d ", *(data->data + i * data->size_x + j));
		}
		printf("\n");
	}
}

void RandPull(Matrix* data) {

	size_t m = data->size_x, n = data->size_y;
	data->data = (int*)calloc(m * n, sizeof(int));

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			*(data->data + i * m + j) = rand()%10;
		}
	}
}

void ThreeMatricesMaker(Matrix* data) {
	for (size_t i = 0; i < 2; i++) {
		printf("----- Введите размеры матрицы №%lu ----- \n", i + 1);
		printf("m = ");
		scanf("%lu", &data[i].size_x);
		printf("n = ");
		scanf("%lu", &data[i].size_y);
		RandPull(&data[i]);
		Print(&data[i]);
	}
	data[2].data = (int*)calloc(data[1].size_x * data[1].size_y, sizeof(int));
	printf("%lu, %lu \n", data[2].size_x, data[2].size_y);
	Print(&data[2]);
}

int main(int argc, char* argv[]) {

	srand(time_t(NULL));

	if (argc == 2) {
		Matrix data[] = {};

		ThreeMatricesMaker(data);

		// if (!strcmp(argv[1], "--sum"))
		// 	MatrixSum(data);
		// else if (!strcmp(argv[1], "--mul"))
		// 	MatrixMul(data);

		Print(&data[2]);

	}

	return 0;
}
