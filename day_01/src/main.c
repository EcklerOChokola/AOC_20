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

	char line[8];
	char found = 0;
	char found_two = 0;
	int values[256];
	int cursor = 0;
	
	while(!feof(file)) {
		fgets(line, 16, file);

		values[cursor] = atoi(line);
		cursor++;
	}

	for (int i = 0; i < cursor; i++)
	{
		for (int j = i; j < cursor; j++)
		{
			for (int k = 0; (!found_two && (k < cursor)); k++)
			{
				if (values[i] + values[j] + values[k] == 2020)
				{
					printf("Part 2 : %d\n", values[i] * values[j] * values[k]);
					found_two++;
					break;
				}
				
			}
			
			if (values[i] + values[j] == 2020) {
				printf("Part 1 : %d\n", values[i] * values[j]);
				found++;
				break;
			}
		}
		if (found && found_two) break;
	}
	
	fclose(file);
	return 0;
}

