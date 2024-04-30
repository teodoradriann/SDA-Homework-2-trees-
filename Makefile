build: tema2

tema2: main.c
	gcc -Wall main.c trie.c utils.c -o tema2
clean:
	rm -f tema2
run:
	./tema2
