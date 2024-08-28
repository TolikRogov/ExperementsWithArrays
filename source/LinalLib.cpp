#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/LinalLib.hpp"

#define STATUS(status)				\
	if (status != LINAL_LIB_OK)	   \
		return status

LinalLibStatus ModSwitcher(int argc, char* argv[]) {
	if (argc == 2) {
		Matrix data[] = { { {}, 0, 0 },
						  { {}, 0, 0 },
						  { {}, 0, 0 } };

		if (!strcmp(argv[1], "--sum")) {
			STATUS(MatricesMaker(data, 2));
			STATUS(MatrixSum(data));
		}
		else if (!strcmp(argv[1], "--mul")) {
			STATUS(MatricesMaker(data, 2));
			STATUS(MatrixMul(data));
		}
		else if (!strcmp(argv[1], "--trn")) {
			STATUS(MatricesMaker(data, 1));
			STATUS(MatrixTrn(data));
		}
		else {
			goto flag_error;
		}

		STATUS(Free(data));
	}
	else {
		flag_error:
			return LINAL_LIB_FLAG_ERROR;
	}

	return LINAL_LIB_OK;
}

LinalLibStatus MatrixTrn(Matrix data[]) {

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
	return LINAL_LIB_OK;
}

LinalLibStatus MatrixMul(Matrix data[]) {
	if (data[0].size_j == data[1].size_i) {

		size_t size_i = data[1].size_i, size_j = data[1].size_j;

		for (size_t i = 0; i < size_i; i++) {

			assert( (0 <= i && i < size_i) );

			for (size_t j = 0; j < size_j; j++) {

				assert( (0 <= j && j < size_j) );

				for (size_t k = 0; k < size_i; k++) {
					*(data[2].data + i * size_j + j) += (*(data[1].data + k * size_j + j) *
						  								 *(data[0].data + i * size_i + k));
				}
			}
		}

		printf("----- Матрица произведения ----- \n");
		Print(&data[2]);
		return LINAL_LIB_OK;
	}
	else {
		return LINAL_LIB_COND_ERROR;
	}
}

LinalLibStatus MatrixSum(Matrix data[]) {
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
		return LINAL_LIB_OK;
	}
	else {
		return LINAL_LIB_COND_ERROR;
	}
}

LinalLibStatus Print(Matrix* data) {
	for (size_t i = 0; i < data->size_i; i++) {

		assert( (0 <= i && i < data->size_i) );

		for (size_t j = 0; j < data->size_j; j++) {

			assert( (0 <= j && j < data->size_j) );

			printf("%2d ", *(data->data + i * data->size_j + j));
		}
		printf("\n");
	}
	return LINAL_LIB_OK;
}

LinalLibStatus MatrixFill(Matrix* data) {

	size_t m = data->size_i, n = data->size_j;
	data->data = (int*)calloc(m * n, sizeof(int));

	if (!data->data) {
		return LINAL_LIB_ALLOC_ERROR;
	}

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			*(data->data + i * n + j) = rand() % 10;
		}
	}

	return LINAL_LIB_OK;
}

LinalLibStatus MatricesMaker(Matrix data[], size_t cnt) {

	for (size_t i = 0; i < cnt; i++) {

		printf("----- Введите размеры матрицы №%lu ----- \n", i + 1);

		printf("m = ");
		scanf("%lu", &data[i].size_i);

		printf("n = ");
		scanf("%lu", &data[i].size_j);

		STATUS(MatrixFill(&data[i]));
		STATUS(Print(&data[i]));
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
			return LINAL_LIB_UNDEF_ERROR;
		}
	}

	data[2].data = (int*)calloc(data[2].size_i * data[2].size_j, sizeof(int));

	if (!data[2].data) {
		return LINAL_LIB_ALLOC_ERROR;
	}

	return LINAL_LIB_OK;
}

LinalLibStatus Free(Matrix data[]) {

	size_t size = 3;

	for(size_t i = 0; i < size; i++) {
		free(data[i].data);
		data[i].data = NULL;
	}

	return LINAL_LIB_OK;
}

const char* Messenger(LinalLibStatus status) {
	switch (status) {
		case LINAL_LIB_OK:			return "OK";
		case LINAL_LIB_ALLOC_ERROR: return "ALLOCATION ERROR";
		case LINAL_LIB_FLAG_ERROR:	return "FLAG ERROR";
		case LINAL_LIB_COND_ERROR:	return "CONDITION ERROR";
		case LINAL_LIB_UNDEF_ERROR: return "UNDEFINED ERROR";
	}
}
