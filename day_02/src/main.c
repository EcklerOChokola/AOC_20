#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char validatePassword(char letter, int first, int second, char password[32]) {
	return (password[first - 1] == letter) ^ (password[second - 1] == letter);
}

int countLetter(char letter, char password[32]) {
	int cursor = 0;
	int count = 0;
	while (password[cursor])
	{
		if (password[cursor] == letter)
		{
			count++;
		}
		cursor++;
	}
	return count;
}

int main(int argc, char **argv) {
	FILE* file;
	if (argc > 1) {
		file = fopen(argv[1], "r");
	} else {
		file = fopen("input.txt", "r");
	}

	int count = 0, count_two = 0;
	int min, max, letterCount;
	char letter;
	char password[32];
	
	while(!feof(file)) {
		fscanf(file, "%d-%d %c: %s", &min, &max, &letter, password);
		letterCount = countLetter(letter, password);
		if (min <= letterCount && letterCount <= max) count++;
		if (validatePassword(letter, min, max, password)) count_two++;
	}

	printf("Part 1 : %d\n", count);
	printf("Part 2 : %d\n", count_two);
	
	fclose(file);
	return 0;
}

