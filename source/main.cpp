#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/LinalLib.hpp"

#define PRINT(error)																\
	printf("\nLINAL_LIB_STATUS: %s, error code: %d \n\n", Messenger(error), error);

int main(int argc, char* argv[]) {

	LinalLibStatus status = LINAL_LIB_OK;

	srand(time_t(NULL));

	status = ModSwitcher(argc, argv);
	if (status != LINAL_LIB_OK)
		PRINT(status);

	return 0;
}
