#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	FILE* file;
	if (argc > 1) {
		file = fopen(argv[1], "r");
	} else {
		file = fopen("input.txt", "r");
	}
	
	while(!feof(file)) {
		// Code goes here
	}
	
	fclose(file);
	return 0;
}

