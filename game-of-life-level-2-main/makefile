CC = gcc
DEP = grille.h io.h jeu.h 
MODE = GRAPHIC
TEXT_MODE = TEXTE

ifeq ($(MODE), $(TEXT_MODE))
	OBJ = main.o grille.o jeu.o io.o
	CFLAGS = -Wall -I include -g
else
	OBJ = main.o grille.o jeu.o io_cairo.o
	CFLAGS = -Wall -I include -g -lcairo -lm -lX11 -Iinclude -I/usr/include/cairo
endif

vpath %.c src/
vpath %.h include/
vpath %.o obj/
vpath %.a lib/

%.o: %.c $(DEP)
	@$(CC) -D $(MODE) -c -o $@ $< $(CFLAGS)
	@mkdir -p bin
	@mkdir -p obj
	@mv *.o obj/

main: $(OBJ) libjeu.a
	@mv obj/*.o ./ 
	@$(CC) -o $@ -Llib $(OBJ) $(CFLAGS) -ljeu
	@mv *.o obj/
	@mkdir -p bin
	@mv main bin/

libjeu.a: grille.o jeu.o
	@ar -crv libjeu.a obj/grille.o obj/jeu.o
	@mkdir -p  lib
	@mv *.a lib/

clean:
	@rm -f bin/main
	@rm -f obj/*
	@rm -f *.o

cleanlib:
	@rm lib/*
	
doc:
	@doxygen

dist:
	@tar -Jcvf GHAMATSetayesh-GOL-v.05.tar.xz makefile Doxyfile src/ include/ 

distclean:
	@rm -r doc
	@rm -r *.tar.xz
