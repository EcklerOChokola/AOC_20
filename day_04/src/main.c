#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passport
{
	char byr[16];
	char cid[16];
	char ecl[16];
	char eyr[16];
	char hgt[16];
	char hcl[16];
	char iyr[16]; 
	char pid[16];
} passport_t;

void print_pass(passport_t* pass) {
	printf("{ byr:%s cid:%s ecl:%s eyr:%s hgt:%s hcl:%s iyr:%s pid:%s }\n",
		pass->byr,
		pass->cid,
		pass->ecl,
		pass->eyr,
		pass->hcl,
		pass->hgt,
		pass->iyr,
		pass->pid
	);
}

// cid is optional
char validate_pass_one(passport_t* pass){
	return (pass->byr[0] && pass->ecl[0] && pass->eyr[0] && pass->hcl[0] && pass->hgt[0] && pass->iyr[0] && pass->pid[0]);
}

// byr (Birth Year) - four digits; at least 1920 and at most 2002.
char validate_byr(char value[16]) {
	if (strlen(value) != 4) return 0;
	if (!(value[0] == '1' && value[1] == '9') && !(value[0] == '2' && value[1] == '0')) return 0;
	int yr = atoi(value);
	return (1920 <= yr && yr <= 2002);
}
// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
char validate_iyr(char value[16]) {
	if (strlen(value) != 4) return 0;
	if (!(value[0] == '2' && value[1] == '0')) return 0;
	int yr = atoi(value);
	return (2010 <= yr && yr <= 2020);
}

// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
char validate_eyr(char value[16]) {
	if (strlen(value) != 4) return 0;
	if (!(value[0] == '2' && value[1] == '0')) return 0;
	int yr = atoi(value);
	return (2020 <= yr && yr <= 2030);
}

// hgt (Height) - a number followed by either cm or in:
// If cm, the number must be at least 150 and at most 193.
// If in, the number must be at least 59 and at most 76.
char validate_hgt(char value[16]) {
	int size;
	int len = strlen(value);
	if (value[len - 2] == 'i' && value[len - 1] == 'n')
	{
		int match = sscanf(value, "%din", &size);
		if (!match) return 0;
		return (59 <= size && size <= 76);
	}
	if (value[len - 2] == 'c' && value[len - 1] == 'm')
	{
		int match = sscanf(value, "%dcm", &size);
		if (!match) return 0;
		return (150 <= size && size <= 193);
	}
	return 0;
}

// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
char validate_hcl(char value[16]) {
	unsigned long long color;
	return ((sscanf(value, "#%6llx", &color)) == 1);
}
	
// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
char validate_ecl(char value[16]) {
	return !(
		strcmp(value, "amb") &&
		strcmp(value, "blu") &&
		strcmp(value, "brn") &&
		strcmp(value, "gry") &&
		strcmp(value, "grn") &&
		strcmp(value, "hzl") &&
		strcmp(value, "oth") 
	);
}

// pid (Passport ID) - a nine-digit number, including leading zeroes.
char validate_pid(char value[16]) {
	if (strlen(value) != 9) return 0;
	unsigned long long pid;
	return (sscanf(value, "%9llu", &pid));
}

// cid (Country ID) - ignored, missing or not.
char validate_pass_two(passport_t* pass) {
	return (
		validate_byr(pass->byr) &&
		validate_iyr(pass->iyr) &&
		validate_eyr(pass->eyr) &&
		validate_hgt(pass->hgt) &&
		validate_hcl(pass->hcl) &&
		validate_ecl(pass->ecl) &&
		validate_pid(pass->pid)
	);
}

void init_pass(passport_t* pass) {
	for (int i = 0; i < 16; i++)
	{
		pass->byr[i] = 0;
		pass->cid[i] = 0;
		pass->ecl[i] = 0;
		pass->eyr[i] = 0;
		pass->hcl[i] = 0;
		pass->hgt[i] = 0;
		pass->iyr[i] = 0;
		pass->pid[i] = 0;
	}
}

void process_line(passport_t* pass, char line[100]) {
	char tag[4];
	int i = 0;
	int j = 0;
	while ( line[i] != ' ' && 
			line[i] != '\n' && 
			line[i] != '\r' && 
			line[i])
	{
		tag[0] = line[i+0];
		tag[1] = line[i+1];
		tag[2] = line[i+2];
		tag[3] = 0;
		i += 4;
		j = 0;
		switch (tag[0])
		{
		case 'b': 
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->byr[j] = line[i+j];
					j++;
				}			
			}
			break;
		case 'c': 
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->cid[j] = line[i+j];
					j++;
				}		
			}
			break;
		case 'e': 
			if (tag[1] == 'c')
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->ecl[j] = line[i+j];
					j++;
				} 
			}
			else
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->eyr[j] = line[i+j];
					j++;
				}		
			}
			break;
		case 'h': 
			if (tag[1] == 'c')
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->hcl[j] = line[i+j];
					j++;
				}	
			}
			else 	
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->hgt[j] = line[i+j];
					j++;
				}	
			}
			break;
		case 'i': 
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->iyr[j] = line[i+j];
					j++;
				}	
			}
			break;
		case 'p': 
			{
				while ( line[i+j] != ' ' && 
						line[i+j] != '\n' && 
						line[i+j] != '\r' && 
						line[i+j])
				{
					pass->pid[j] = line[i+j];
					j++;
				}	
			}
			break;
		default:
			break;
		}
		i += j + 1;
	}
}

int main(int argc, char **argv) {
	FILE* file;
	if (argc > 1) {
		file = fopen(argv[1], "r");
	} else {
		file = fopen("input.txt", "r");
	}

	char line[100];
	passport_t pass;
	init_pass(&pass);
	int count_one = 0;
	int count_two = 0;
	
	while(!feof(file)) {
		fgets(line, 100, file);
		if (strlen(line) < 4) {
			if (validate_pass_one(&pass)) {
				count_one++;
			}
			if (validate_pass_two(&pass)) {
				count_two++;
			}
			init_pass(&pass);
		} else {
			process_line(&pass, line);
		}
		
	}
	if (validate_pass_one(&pass)) {
		count_one++;
	}
	if (validate_pass_two(&pass)) {
		count_two++;
	}

	printf("Part 1 : %d\n", count_one);
	printf("Part 2 : %d\n", count_two);
	
	fclose(file);
	return 0;
}

