/*
 * Jay Patel
 * file:// jumble_game.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct head_node HEAD_NODE;

int SIZE_GLOBAL; //will keep track of the size of the table
int COUNTER_GLOBAL; //will get incremented every time a new word is added to the list

/*
 * Returns a pointer array of type HEAD_NODE
 * init includes a NULL pointer that is of type WORDLIST
 */
HEAD_NODE *create_list();

/*
 * only function that the user is able to call, in addition with destroy_list and jumble_words
 * no return type
 * calls the add_to_list function within itself to add words on the list
 */
void main_list(HEAD_NODE *hn_arr, char *word);

/*
 * no return type
 * prints all the words stored on the list
 */
void print_all(HEAD_NODE *hn_arr);

/*
 * grows the size of the array by doubling the size each time the function is called
 * function doesn't get used by the user, only gets called by function call within 
 * add_to_list()
 */
void increase_size();

/*
 * no return type
 * destroys the entire list by freeing one node at a time
 * and then freeing the list itself after everything is freed
 */
void destroy_list(HEAD_NODE *hn_arr);

/*
 * no return type
 * copies the content of one array into another
 * no actual nodes get copies, only the head gets copied
 */
void copy_to_list(HEAD_NODE *from_arr, HEAD_NODE *to_arr);

/*
 * no return type
 * takes in the pointer to the main list, the word to be stored, along with the annagram of that word, and a token
 * 
 * for example: word:     "steak"
 				annagram: "aekst"
 				token   : the place at which to be stored
 *
 * checks to see if global counter is equal to the global size
 * grows the global size in double by making a function call to increase_size
 * 
 */
void add_to_list(HEAD_NODE *hn_arr, char *word, char *anngram, int token);

/*
 * returns 1 or 0
 * 1 if there were words found
 * 0 if no words were found
 * 
 * takes in a pointer of the head node, annagram, and a token
 *
 * compares all the annagram within the head node based on the token
 */
int jumble_words(HEAD_NODE *hn_arr, char *word, int token);

/*
 * returns an int value
 * creates a "token" based on char value of the strings
 * for example: input string is: "hello"
 *                 	     return: "532"
 * the function will add the int value associated with that char
 * 'h' = 104
 * 'e' = 101
 * 'l' = 108
 * 'l' = 108
 * 'o' = 111
 */
int create_token(char *word);

/*
 * helper function for qsort
 * quickly sorts two values
 * function only gets called using qsort
 */
int compare(const void *a, const void *b);

/*
 * prints the status of the entire list
 */
void print_status(HEAD_NODE *hn_arr);

/*
 * returns an int value
 * finds the max amount of words that can be associated with one word within the dictionary
 */
int max_len(HEAD_NODE *hn_arr);

/*
 * returns a double value by finding the average words that are contained
 * within a linked list inside the hash table
 */
double avg_cmps(HEAD_NODE *hn_arr);

/*
 * no return type
 * used within the program for internal testing
 * prints the entire linked list associated within the token
 */
void print_specific(HEAD_NODE *hn_arr, int token);

/*
 * no return type
 * prints the entire list that is associated with the max_len function
 */
void print_specific_key(HEAD_NODE *hn_arr);
