OBJ = main.o helper.o queue.o
all: main
main: $(OBJ)
	gcc $(OBJ) -o main -pthread
$(OBJ): entities.h queue.h helper.h
.PHONY: clean
clean:
	rm -f *.o main