#MAKEFILE for schedule project
#made by team PM 2.5

EXECUTABLES= main$(EXECEXT)

all : $(EXECUTABLES)

validate.o : validate.c validate.h
	gcc -c validate.c

linkedListStack.o : linkedListStack.c abstractStack.h
	gcc -c linkedListStack.c

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

linkedListNetwork2.o :	linkedListNetwork2.c abstractNetwork2.h abstractQueue.h abstractStack.h
	gcc -c linkedListNetwork2.c

readData.o : readData.c abstractNetwork2.h add.h
	gcc -c readData.c

displayTask.o : displayTask.c displayTask.h readData.h abstractNetwork2.h dueDate.h display.h
	gcc -c displayTask.c

dueDate.o : dueDate.c validate.h
	gcc -c dueDate.c

display.o : display.c display.h displayTask.h add.h
	gcc -c display.c

add.o : add.c add.h abstractNetwork2.h abstractQueue.h validate.h displayTask.h
	gcc -c add.c

search.o : search.c search.h abstractNetwork2.h add.h validate.h displayTask.h
	gcc -c search.c

main.o : main.c add.h search.h display.h
	gcc -c main.c

main$(EXECEXT) : main.o linkedListNetwork2.o linkedListQueue.o linkedListStack.o add.o search.o validate.o displayTask.o readData.o dueDate.o display.o
	gcc -o main$(EXECEXT) main.o linkedListNetwork2.o linkedListQueue.o linkedListStack.o add.o search.o validate.o displayTask.o readData.o dueDate.o display.o


clean :
	-rm *.o
	-rm $(EXECUTABLES)
