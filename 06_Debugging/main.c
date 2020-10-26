#include <stdlib.h>

int main()
{
	int *a = malloc(20);
	free(a);
	free(a);
	return 0;
}
