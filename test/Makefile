CFLAGS+=-pedantic -Wall -std=c99 -g -O0

# TODO: These are not linked correctly. The objects, they refer to have evolved from their original forms. Generally the
# functions that have only been in the tests are now in the shared library files. This is a mess. It should be modified
# into a single test file as in the numerical methods solution. <24-04-24> 

KONTROLA_1: ../objects/axiom_string-module.o ../objects/kontrola_1-action.o # FIX:   
	${CC} ${CFLAGS} ../objects/*.o -o KONTROLA_1

KONTROLA_2: ../objects/axiom_string-module.o ../objects/alpha_mod_module.o ../objects/inputread-module.o ../objects/kontrola_2-alpha.o # FIX:   
	${CC} ${CFLAGS} ../objects/*.o -o KONTROLA_2

KONTROLA_3: ../objects/axiom_string-module.o ../objects/alpha_mod_module.o ../objects/inputread-module.o ../objects/kontrola_3-axiom.o # FIX:   
	${CC} ${CFLAGS} ../objects/*.o -o KONTROLA_3
 
KONTROLA_4: ../objects/axiom_string-module.o ../objects/alpha_mod_module.o ../objects/inputread-module.o ../objects/kontrola_4-mod.o # FIX:   
	${CC} ${CFLAGS} ../objects/*.o -o KONTROLA_4

KONTROLA_5: ../objects/axiom_string-module.o ../objects/alpha_mod_module.o ../objects/inputread-module.o ../objects/kontrola_5-load.o # FIX:   
	${CC} ${CFLAGS} ../objects/*.o -o KONTROLA_5

../objects/axiom_string-module.o: ../program/axiom_string-module.c ../program/axiom_string-module.h
	${CC} ${CFLAGS} -c ../program/axiom_string-module.c -o ../objects/axiom_string-module.o

../objects/alpha_mod_module.o: ../program/alpha_mod-module.c ../program/alpha_mod-module.h
	${CC} ${CFLAGS} -c ../program/alpha_mod-module.c -o ../objects/alpha_mod-module.o

../objects/inputread-module.o: ../program/inputread-module.c ../program/inputread-module.o
	${CC} ${CFLAGS} -c ../program/inputread-module.c -o ../objects/inputread-module.o


../objects/kontrola_1-action.o: kontrola_1-action.c
	${CC} ${CFLAGS} -c ../kontroly/kontrola_1-action.c -o ../objects/kontrola_1-action.o

../objects/kontrola_2-alpha.o: kontrola_2-alpha.c
	${CC} ${CFLAGS} -c ../kontroly/kontrola_2-alpha.c -o ../objects/kontrola_2-alpha.o

../objects/kontrola_3-axiom.o: kontrola_3-axiom.c
	${CC} ${CFLAGS} -c ../kontroly/kontrola_3-axiom.c -o ../objects/kontrola_3-axiom.o

../objects/kontrola_4-mod.o: ../kontroly/kontrola_4-mod.c
	${CC} ${CFLAGS} -c ../kontroly/kontrola_4-mod.c -o ../objects/kontrola_4-mod.o

../objects/kontrola_5-load.o: ../kontroly/kontrola_5-load.c
	${CC} ${CFLAGS} -c ../kontroly/kontrola_5-load.c -o ../objects/kontrola_5-load.o


zip:
	zip zapoctak.zip input_read.c alpha_update.c alpha_update.h input.txt Makefile
	
clean:
	rm -f ../objects/*.o
	rm -f semestralka.zip
