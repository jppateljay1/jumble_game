/*
 * Jay Patel
 * file:// main.c
 */

#include <ctype.h>
#include "jumble_game.h"

int main(int argc, char *argv[])
{
	SIZE_GLOBAL = 20000;
	COUNTER_GLOBAL = 0;

	if(argc < 2)
	{
		printf("---------------------------------------------------\n");
		printf("Enter a filename after the executable\n");
		printf("ex: ./jumble <filename>\n");
		printf("---------------------------------------------------\n");
		exit(-1);
	}

	char file_name[50];

	strcpy(file_name, argv[1]);

	FILE *fin;
	fin = fopen(file_name, "r");

	if(fin == NULL)
	{
		fprintf(stderr, "can not open input file, %s\n", file_name);
		return 0;
	}

	printf("filename: %s\n", file_name);

	HEAD_NODE *hn_arr;
	hn_arr = create_list();
	char *word;

	while(fscanf(fin, "%s", word) != EOF)
	{
		//convert everything into lowercase before it begins
		for(int i = 0; word[i]; i++)
			word[i] = tolower(word[i]);

		main_list(hn_arr, word);
	}

	fclose(fin);

	printf("Enter a string or . to exit\n");
	char input_string[50];
	scanf("%48s", input_string);
	while(strcmp(input_string, ".") != 0)
	{
		//convert everything into lowercase before it begins
		for(int i = 0; input_string[i]; i++)
			input_string[i] = tolower(input_string[i]);

		int token = create_token(input_string) % SIZE_GLOBAL;

		qsort(input_string, strlen(input_string), sizeof(char), compare);

		if(jumble_words(hn_arr, input_string, token) == 0)
			printf("no matches\n");

		printf("Enter a string or . to exit\n");
		scanf("%48s", input_string);
	}

	//print_all(hn_arr);
	print_status(hn_arr);
	printf("GOODBYE\n");

	//print_specific(hn_arr, 1200);
	//print_specific_key(hn_arr);
	destroy_list(hn_arr);
	return 0;
}
