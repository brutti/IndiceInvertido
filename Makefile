FLAGS=-Wall
BINEXEC=a.out

All: ${BINEXEC}

${BINEXEC}: upIndice.o main.c
		gcc main.c upIndice.o ${FLAGS}

arv.o: arv.c
	gcc -c upIndice.c ${FLAGS}

clean:
	rm -f *.o rank.txt ${BINEXEC}
