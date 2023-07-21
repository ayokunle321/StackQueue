squeue: squeue_client.o squeue.o
	gcc -Wall -ggdb -std=c99 -o squeue squeue_client.o squeue.o

squeue_client.o: squeue.h squeue_client.c
	gcc -Wall -ggdb -std=c99 -c -o squeue_client.o squeue_client.c

squeue.o: squeue.h squeue.c
	gcc -Wall -ggdb -std=c99 -c -o squeue.o squeue.c

clean:
	rm -f *.o
	rm -f squeue