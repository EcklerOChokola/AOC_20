#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cond_sum(int* array, int len, int value) {
	int total = 0;
	for (int i = 0; i < len; i++) {
		if (array[i] >= value) total++;
	}
	return total;
}

void init_table(int* array, int len, int value) {
	for (int i = 0; i < len; i++) array[i] = value;
}

int main(int argc, char **argv) {
	FILE* file;
	if (argc > 1) {
		file = fopen(argv[1], "r");
	} else {
		file = fopen("input.txt", "r");
	}

	int total_one = 0;
	int total_two = 0;
	int answerers = 0;
	char line[32];
	int answered[26];
	init_table(answered, 26, 0);
	
	while(!feof(file)) {
		fgets(line, 32, file);
		// change to 1 if on Linux
		if (strlen(line) == 2) {
			total_one += cond_sum(answered, 26, 1);
			total_two += cond_sum(answered, 26, answerers);
			init_table(answered, 26, 0);
			answerers = 0;
		} else {
			answerers++;
			for (int i = 0; i < strlen(line); i++)
			{
				if ('a' <= line[i] && line[i] <= 'z')
				{
					answered[line[i] - 'a']++;
				}
			}
		}
	} 
	
	total_one += cond_sum(answered, 26, 1);
	total_two += cond_sum(answered, 26, answerers);
	init_table(answered, 26, 0);
	
	printf("Part 1 : %d\n", total_one);
	printf("Part 2 : %d\n", total_two);

	fclose(file);
	return 0;
}

