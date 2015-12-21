
jumble: jumble_game.o
	gcc main.c jumble_game.o -o jumble
jumble_game.o: jumble_game.c
	gcc -c jumble_game.c
val: jumble_game.o
	gcc main.c jumble_game.o -g -o0
clean:
	rm jumble_game.o jumble
