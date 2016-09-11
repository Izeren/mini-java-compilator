SRC=src
NODES=$(SRC)/nodes
STATEMENTS=$(NODES)/statements
EXPRESSIONS=$(NODES)/expressions

all: main

main.bin: main.o visitor.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) -c $^ -o $@

#Visitors block
visitor.o: visitor.cpp
	$(CC) -c $^ -o $@



#Statements block
IdExp.o: CIdExp.cpp
	$(CC) -c $^ -o $@



#Expressions block