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
	
	char line[16];
	int max = 0, min = 1000;
	int first;
	int cursor = 0;
	int seat_ids[1000];
	int your_seat_id;

	while(!feof(file)) {
		fgets(line, 16, file);
		first = 0;
		for(int i = 0; i < 10; i++) {
			if (line[i] == 'B' || line[i] == 'R') first |= 1 << (9-i);
			if (line[i] == 'F' || line[i] == 'L') 
			;
		}
		// printf("%s : %d (%d, %d)\n", line, first, first / 8, first % 8);
		if(max < first) max = first;
		if(min > first) min = first;
		seat_ids[cursor] = first;
		cursor++;
	}

	for (int i = min; i < max; i++)
	{
		char found = 0;
		for (int j = 0; j < cursor; j++)
		{
			if (seat_ids[j] == i) {
				found = 1;
				break;
			}
		}
		if (!found) {
			your_seat_id = i;
			break;
		}
	}
	
	printf("Part 1 : %d\n", max);
	printf("Part 2 : %d\n", your_seat_id);
	
	fclose(file);
	return 0;
}

