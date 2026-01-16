CC=gcc
NAME=DataWatch

all: dataBase
	$(CC) DataWatch.c -o $(NAME)

dataBase:
	touch DataText.txt

clean:
	rm $(NAME)

cleanAll: clean
	rm DataText.txt
