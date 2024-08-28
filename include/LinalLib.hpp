#ifndef LINALLIB_INCLUDE
#define LINALLIB_INCLUDE

enum LinalLibStatus {
	LINAL_LIB_OK,
	LINAL_LIB_ALLOC_ERROR,
	LINAL_LIB_FLAG_ERROR,
	LINAL_LIB_COND_ERROR,
	LINAL_LIB_UNDEF_ERROR
};

struct Matrix {
	int* data;
	size_t size_i;
	size_t size_j;
	int** addr;
};

const char* Messenger(LinalLibStatus status);
LinalLibStatus AddrFill(Matrix* data);
LinalLibStatus ModSwitcher(int argc, char* argv[]);
LinalLibStatus Free(Matrix data[]);
LinalLibStatus MatrixTrn(Matrix data[]);
LinalLibStatus MatrixMul(Matrix data[]);
LinalLibStatus MatrixFill(Matrix* data);
LinalLibStatus MatrixSum(Matrix data[]);
LinalLibStatus Print(Matrix* data);
LinalLibStatus MatricesMaker(Matrix data[], size_t cnt);

#endif //LINALLIB_INCLUDE
