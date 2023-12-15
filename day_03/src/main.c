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
	
	unsigned long count_one = 0;
	unsigned long count_two = 0;
	unsigned long count_three = 0;
	unsigned long count_five = 0;
	unsigned long count_seven = 0;
	int x = 1;

	// Max length in input is 31 + CR + null
	char line[36];

	// dump first line
	fgets(line, 36, file);

	// Copied from Windows, discard 1 for CR and 1 because of null termination
	int mod = strlen(line) - 2;

	while(!feof(file)) {
		fgets(line, 36, file);
		if (line[(x)%mod] == '#') count_one++;
		if (line[(x*3)%mod] == '#') count_three++;
		if (line[(x*5)%mod] == '#') count_five++;
		if (line[(x*7)%mod] == '#') count_seven++;
		if (line[(x/2)%mod] == '#' && (x%2 == 0)) count_two++;
		x++;
	}

	//printf("%lu\n", count_one);
	//printf("%lu\n", count_two);
	//printf("%lu\n", count_three);
	//printf("%lu\n", count_five);
	//printf("%lu\n", count_seven);

	printf("Part 1 : %lu\n", count_three);
	printf("Part 2 : %lu\n", count_one * count_three * count_five * count_seven * count_two);
	
	fclose(file);
	return 0;
}

