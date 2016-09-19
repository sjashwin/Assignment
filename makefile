main: loglib.c log.h main.c
	gcc loglib.c main.c -o file
clean:
	rm file *.txt
	
