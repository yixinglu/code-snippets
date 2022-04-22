SRC:=$(shell echo *.cc)
OBJ:=$(SRC:%.cc=%.o)

all:$(OBJ) $(SRC)
	@echo $(SRC) $(OBJ)
	make --directory=./target/ $(OP)

%.o:%.cc
	g++ -c -o $@ $<
	cp $@ ./target/ -f 

clean:
	rm -f *.o
