CFLAGS= -g

main: main.o tree.o
	gcc $(CFLAGS) -Wall main.o tree.o -o PA3_AVL

all: main docs
	gcc $(CFLAGS) -Wall main.c tree.c -o PA3_AVL
	
docs: 
	doxygen

clean:
	rm -f main.o tree.o PA3_AVL
				


	
			
