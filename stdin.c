#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

// make re STDIN=1 && (< test_files/basic_no_newline_end ./get_next_line --jobs 1 --filter '*/*')

int main(void) {
	printf("---------\n");
	char *out;
	do {
		out = get_next_line(STDIN_FILENO);
		if (out != NULL)
			printf("%s", out);
	} while (out != NULL);
	printf("---------\n");
	return (EXIT_SUCCESS);
}
