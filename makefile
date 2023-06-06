EXE = solve
SRC = main.c

all: $(EXE)

$(EXE): $(SRC)
	gcc $(SRC) -o $(EXE) -g

clean:
	rm -f $(EXE)
	rm *.o