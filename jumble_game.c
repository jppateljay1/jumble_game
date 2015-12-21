/*
 * Jay Patel
 * file:// jumble_game.c
 */

#include "jumble_game.h"

typedef struct wordlist
{
	char word[50];
	char annagram[50];
	struct wordlist *next;
}WORDLIST;

struct head_node
{
	int count;
	WORDLIST *list;
};

HEAD_NODE *create_list()
{
	int size = SIZE_GLOBAL;
	HEAD_NODE *to_ret = malloc(sizeof(HEAD_NODE) * size);


	int i;
	for(i = 0; i < size; i++)
	{
		to_ret[i].count = 0;
		to_ret[i].list = NULL;
	}

	return to_ret;
}

int compare(const void *a, const void *b)
{
	const char *ai = (char *)a;
	const char *bi = (char *)b;

	return (*ai - *bi);
}

void print_all(HEAD_NODE *hn_arr)
{
	int size = SIZE_GLOBAL;
	int i;
	WORDLIST *temp;

	for(i = 0; i < size; i++)
	{
		temp = hn_arr[i].list;

		while(temp != NULL)
		{
			printf("%s, ", temp->word);
			temp = temp->next;
		}

		printf("\n");
	}
}

void destroy_list(HEAD_NODE *hn_arr)
{
	int size = SIZE_GLOBAL;
	WORDLIST *temp;
	WORDLIST *temp_next;

	/*int i;
	for(i = 0; i < size; i++)
	{
		if(hn_arr[i].count > 3000)
			continue;
		temp = hn_arr[i].list;
		if(temp == NULL)
			continue;

		while(temp != NULL)
		{
			temp_next = temp->next;
			free(temp);
			temp = temp_next;
		}
	}*/

	free(hn_arr);
}

void increase_size()
{
	SIZE_GLOBAL = SIZE_GLOBAL * 2;
}

void copy_to_list(HEAD_NODE *from_arr, HEAD_NODE *to_arr)
{
	int size = SIZE_GLOBAL;

	int i;
	for(i = 0; i < size; i++)
	{
		to_arr[i].list = from_arr[i].list;
		to_arr[i].count = from_arr[i].count;
	}
}

int create_token(char *word)
{
	int total = 0;
	int i;
	for(i = 0; word[i]; i++)
		total = total + word[i];

	return total;
}

void main_list(HEAD_NODE *hn_arr, char *word)
{
	if(COUNTER_GLOBAL > SIZE_GLOBAL)
	{
		increase_size();
		HEAD_NODE *to_arr = create_list();
		copy_to_list(hn_arr, to_arr);
		*hn_arr = *to_arr;
	}

	int token = create_token(word) % SIZE_GLOBAL;
	char annagram[50];
	strcpy(annagram, word);
	qsort(annagram, strlen(annagram), sizeof(char), compare);

	add_to_list(hn_arr, word, annagram, token);

	hn_arr[token].count++;

	COUNTER_GLOBAL++;
}

int jumble_words(HEAD_NODE *hn_arr, char *word, int token)
{
	int to_return = 0;
	WORDLIST *temp = hn_arr[token].list;

	while(temp != NULL)
	{
		if(strcmp(temp->annagram, word) == 0)
		{
			to_return = 1;
			printf("%s\n", temp->word);
		}
		temp = temp->next;
	}

	return to_return;
}

void add_to_list(HEAD_NODE *hn_arr, char *word, char *annagram, int token)
{
	WORDLIST *to_add;

	WORDLIST *temp = hn_arr[token].list;

	if(temp == NULL)
	{
		to_add = malloc(sizeof(WORDLIST));
		strcpy(to_add->word, word);
		strcpy(to_add->annagram, annagram);
		to_add->next = NULL;

		hn_arr[token].list = to_add;
		return;
	}

	to_add = malloc(sizeof(WORDLIST));
	strcpy(to_add->word, word);
	strcpy(to_add->annagram, annagram);
	to_add->next = NULL;

	to_add->next = hn_arr[token].list;
	hn_arr[token].list = to_add;
}

int max_len(HEAD_NODE *hn_arr)
{
	int i, max = 0, size = SIZE_GLOBAL;
	for(i = 0; i < size; i++)
	{
		if(hn_arr[i].count > 3000)
			continue;
		if(hn_arr[i].count > max)
			max = hn_arr[i].count;
	}

	return max;
}
double avg_cmps(HEAD_NODE *hn_arr)
{
	int i, size = SIZE_GLOBAL;
	double total = 0;

	for(i = 0; i < size; i++)
	{
		int ni = hn_arr[i].count;
		if(ni > 3000)
			continue;

		total += (ni*(ni+1))/2;
	}

	return total/COUNTER_GLOBAL;
}

void print_status(HEAD_NODE *hn_arr)
{
	printf("######## TABLE STATS ##########\n");

    printf("   tblsize:               %i \n", SIZE_GLOBAL);
    printf("   numkeys:               %i \n", COUNTER_GLOBAL);
    printf("   max-collisions:        %i \n", max_len(hn_arr));
    printf("   avg-cmps-good-lookup:  %f \n", avg_cmps(hn_arr));

    printf("###### END TABLE STATS ##########\n");
}

void print_specific(HEAD_NODE *hn_arr, int token)
{
	int i, size = SIZE_GLOBAL;

	WORDLIST *temp = hn_arr[token].list;

	if(temp == NULL)
	{
		printf("list is empty\n");
		return;
	}

	while(temp != NULL)
	{
		printf("word: %s\n", temp->word);
		temp = temp->next;
	}
}

void print_specific_key(HEAD_NODE *hn_arr)
{
	int i, size = SIZE_GLOBAL;
	int token = max_len(hn_arr);

	WORDLIST *temp = hn_arr[token].list;
	if(temp == NULL)
	{
		printf("list is empty\n");
		return;
	}

	while(temp != NULL)
	{
		printf("word: %s key: %d actual_key: %d\n", temp->word, token, create_token(temp->word));
		temp = temp->next;
	}
}




