#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stridx(char names[600][32], char name[32]) {
	for (int i = 0; i < 600; i++)
	{
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;	
}

int get_shiny_bags(int indices[600][8], int counts[600][8], int index) {
	if (index == 0)
	{
		return 1;
	}
	int result = 0;
	
	for (int i = 0; i < 8; i++)
	{
		if (counts[index][i] == 0) break;
		result += counts[index][i] * get_shiny_bags(indices, counts, indices[index][i]);
	}
	return result;
	
} 

int count_bags(int indices[600][8], int counts[600][8], int index) {
	int result = 1;
	
	for (int i = 0; i < 8; i++)
	{
		if (counts[index][i] == 0) break;
		result += counts[index][i] * count_bags(indices, counts, indices[index][i]);
	}
	return result;
}

int main(int argc, char **argv) {
	FILE* file;
	if (argc > 1) {
		file = fopen(argv[1], "r");
	} else {
		file = fopen("input.txt", "r");
	}

	int index = 0;
	char names[600][32];
	int indices[600][8];
	int counts[600][8];
	char line[128];
	char color1[16];
	char color2[16];
	char name[32];

	strcpy(names[0], "shiny gold");
	
	while(!feof(file)) {
		fgets(line, 128, file);
		sscanf(line, "%s %s", color1, color2);
		strcpy(name, color1);
		strcat(name, " ");
		strcat(name, color2);
		int p = stridx(names, name);
		if (p == -1) {
			index++;
			p = index;
		}
		strcpy(names[p], name);

		int cursor = 0;
		int spaces = 0;
		while (spaces < 4)
		{
			if (line[cursor] == ' ') spaces++;
			cursor++;
		}

		int indices_idx = 0;
		int temp_index = index;
		while (line[cursor] >= '0' && line[cursor] <= '9')
		{
			char *end = &line[cursor];

			int count;

			sscanf(end, "%d %s %s", &count, color1, color2);
			strcpy(name, color1);
			strcat(name, " ");
			strcat(name, color2);

			int place = stridx(names, name);
			if (place == -1) {
				temp_index++;
				place = temp_index;
				strcpy(names[place], name);
			}

			indices[p][indices_idx] = place;
			counts[p][indices_idx] = count;

			while (line[cursor] != ',' && line[cursor] != '.')
			{
				cursor++;
			}
			indices_idx++;
			if (line[cursor] == ',') {
				cursor+=2;
			} else {
				break;
			}
		}
		index = temp_index;
	}

	int count = 0;
	for (int i = 1; i <= index; i++)
	{
		if(get_shiny_bags(indices, counts, i)) count++;
	}

	printf("Part 1 : %d\n", count);
	printf("Part 2 : %d\n", count_bags(indices, counts, 0) - 1);
	
	fclose(file);
	return 0;
}

