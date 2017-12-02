INCLUDE = ./include
LIB = ./lib
SRC = ./src
TEST = ./test
SRC = ./src
IMG = ./images
FLAGS = -O3 -Wall -g -O0 -lm


all: lib app

lib: \
	$(LIB)/Imagem.o \
	$(LIB)/Filtros.o

app: \
	$(SRC)/catarata \
	$(TEST)/cunit_imagem

$(LIB)/%.o: $(LIB)/%.c $(INCLUDE)/%.h
	gcc -c $< -I $(INCLUDE) $(FLAGS) -o $@

$(SRC)/%: $(SRC)/%.c
	gcc $< $(LIB)/*.o -I $(INCLUDE) $(FLAGS) -o $@

$(TEST)/%: $(TEST)/%.c
	gcc $< -lcunit $(LIB)/*.o -I $(INCLUDE) $(FLAGS) -o $@

run:
	$(SRC)/catarata -i ./images/Normal.ppm -f ppm -o diagnostico.txt

teste:
	$(TEST)/cunit_imagem

clean:
	rm $(LIB)/*.o
	rm $(SRC)/catarata
	rm $(TEST)/cunit_imagem
	rm $(IMG)/cinza.ppm
	rm $(IMG)/gauss.ppm
	rm $(IMG)/sobel.ppm
