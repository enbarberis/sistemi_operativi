compiler = gcc
compiler_option = -g -Wall
executable_name = lsr.o

compile:
	${compiler} lsr.c -o ${executable_name} ${compiler_option}

install: compile
	mkdir -p bin
	mv ./lsr.o ./bin/

clean:
	rm -f ./*.o

distclean: clean
	rm -fr ./bin


