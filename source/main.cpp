#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// TODO:

struct Matrix {
	int* data;
	size_t size_i;
	size_t size_j;
};

void Free(Matrix data[]);
void MatrixTrn(Matrix data[]);
void MatrixMul(Matrix data[]);
void MatrixFill(Matrix* data);
void MatrixSum(Matrix data[]);
void Print(Matrix* data);
void MatricesMaker(Matrix data[], size_t cnt);

void MatrixTrn(Matrix data[]) {

	size_t size_i = data[2].size_i, size_j = data[2].size_j;

	for (size_t i = 0; i < size_i; i++) {

		assert( (0 <= i && i < size_i) );

		for (size_t j = 0; j < size_j; j++) {

			assert( (0 <= j && j < size_j) );

			*(data[2].data + i * size_j + j) = *(data[0].data + j * data[0].size_j + i);
		}
	}

	printf("----- Транспонированная матрица ----- \n");
	Print(&data[2]);
}

void MatrixMul(Matrix data[]) {
	if (data[0].size_j == data[1].size_i) {

		size_t size_i = data[1].size_i, size_j = data[1].size_j;

		for (size_t i = 0; i < size_i; i++) {

			assert( (0 <= i && i < size_i) );

			for (size_t j = 0; j < size_j; j++) {

				assert( (0 <= j && j < size_j) );

				int p = 0;
				for (size_t k = 0; k < size_i; k++) {
					p += (*(data[1].data + k * size_j + j) *
						  *(data[0].data + i * size_i + k));
				}
				*(data[2].data + i * size_j + j) = p;
			}
		}

		printf("----- Матрица произведения ----- \n");
		Print(&data[2]);
	}
	else {
		printf("Condition of multiple of matrices is not followed \n");
	}
}

void MatrixSum(Matrix data[]) {
	if (data[0].size_i == data[1].size_i && data[0].size_j == data[1].size_j) {

		size_t size_i = data[0].size_i, size_j = data[0].size_j;

		for (size_t i = 0; i < size_i; i++) {

			assert( (0 <= i && i < size_i) );

			for (size_t j = 0; j < size_i; j++) {

				assert( (0 <= j && j < size_i) );

				*(data[2].data + i * size_j + j) =
				*(data[0].data + i * size_j + j) + *(data[1].data + i * size_j + j);
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
	for (size_t i = 0; i < data->size_i; i++) {

		assert( (0 <= i && i < data->size_i) );

		for (size_t j = 0; j < data->size_j; j++) {

			assert( (0 <= j && j < data->size_j) );

			printf("%2d ", *(data->data + i * data->size_j + j));
		}
		printf("\n");
	}
}

void MatrixFill(Matrix* data) {

	size_t m = data->size_i, n = data->size_j;
	data->data = (int*)calloc(m * n, sizeof(int));

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			*(data->data + i * n + j) = rand()%10;
		}
	}
}

void MatricesMaker(Matrix data[], size_t cnt) {

	for (size_t i = 0; i < cnt; i++) {

		printf("----- Введите размеры матрицы №%lu ----- \n", i + 1);

		printf("m = ");
		scanf("%lu", &data[i].size_i);

		printf("n = ");
		scanf("%lu", &data[i].size_j);

		MatrixFill(&data[i]);
		Print(&data[i]);

	}

	switch (cnt) {
		case 1: {
			data[2].size_i = data[0].size_j;
			data[2].size_j = data[0].size_i;
			break;
		}
		case 2: {
			data[2].size_i = data[0].size_i;
			data[2].size_j = data[1].size_j;
			break;
		}
		default: {
			printf("Undefined error \n");
			break;
		}
	}

	data[2].data = (int*)calloc(data[2].size_i * data[2].size_j, sizeof(int));

}

void Free(Matrix data[]) {
	size_t size = 3;
	for(size_t i = 0; i < size; i++) {
		free(data[i].data);
		data[i].data = NULL;
	}
}

int main(int argc, char* argv[]) {

	srand(time_t(NULL));

	if (argc == 2) {

		if (strcmp(argv[1], "--sum") && strcmp(argv[1], "--mul") && strcmp(argv[1], "--trn")) {
			printf("Error flag \n");
			return 0;
		}

		Matrix data[] = { { {}, 0, 0 },
						  { {}, 0, 0 },
						  { {}, 0, 0 } };

		if (!strcmp(argv[1], "--sum")) {
			MatricesMaker(data, 2);
			MatrixSum(data);
		}
		else if (!strcmp(argv[1], "--mul")) {
			MatricesMaker(data, 2);
			MatrixMul(data);
		}
		else if (!strcmp(argv[1], "--trn")) {
			MatricesMaker(data, 1);
			MatrixTrn(data);
		}

		Free(data);

	}

	return 0;
}
