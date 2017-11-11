INCLUDE = ./include
LIB = ./lib
SRC = ./src
TEST = ./test
SRC = ./src
IMG = ./images
FLAGS = -O3 -Wall -g


all: lib app

lib: $(LIB)/Imagem.o

app: \
	$(SRC)/catarata \
#	$(TEST)/cunit_main

$(LIB)/%.o: $(LIB)/%.c $(INCLUDE)/%.h
	gcc -c $< -I $(INCLUDE) $(FLAGS) -o $@

$(SRC)/%: $(SRC)/%.c
	gcc $< $(LIB)/*.o -I $(INCLUDE) $(FLAGS) -o $@

#$(TEST)/%: $(TEST)/%.c
#	gcc $< -lcunit $(LIB)/*.o -I $(INCLUDE) $(FLAGS) -o $@

run:
	$(SRC)/catarata -i ./images/Catarata2.ppm -f ppm -o diagnostico.txt

#teste:
#	$(TEST)/cunit_main

clean:
	rm $(LIB)/*.o
	rm $(SRC)/catarata
	rm $(IMG)/cinza.tmp
#	rm $(TEST)/cunit_main
