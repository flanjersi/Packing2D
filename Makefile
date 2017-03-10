CC = gcc
CCFLAGS = -W -Wall -g -std=c99
OBJ1 = objet.o
OBJ2 = objet.o bande.o
OBJ3 = objet.o bande.o boite.o
OBJ4 = boite.o objet.o lecture.o bande.o probleme.o
OBJ5 = objet.o bande.o boite.o tri.o k_largeurs_valides.o remplir_boite.o lecture.o probleme.o sac_a_dos.o

all: genere visualisation test_objet test_lecture test_boite test_bande test_glouton test_SAD test_probleme


#-------------------------------------------------------------------------

test_objet: test_objet.c $(OBJ1)
	$(CC) $(CCFLAGS) test_objet.c -o test_objet $(OBJ1)

test_lecture: test_lecture.c $(OBJ4)
	$(CC) $(CCFLAGS) test_lecture.c -o test_lecture $(OBJ4)

test_boite: test_boite.c $(OBJ3)
	$(CC) $(CCFLAGS) test_boite.c -o test_boite $(OBJ3)

test_bande: test_bande.c $(OBJ2)
	$(CC) $(CCFLAGS) test_bande.c -o test_bande $(OBJ2)

test_glouton: test_glouton.c $(OBJ5)
	$(CC) $(CCFLAGS) test_glouton.c -o test_glouton $(OBJ5)

test_SAD: test_SAD.c $(OBJ5)
	$(CC) $(CCFLAGS) test_SAD.c -o test_SAD $(OBJ5)

test_probleme: test_probleme.c $(OBJ5)
	$(CC) $(CCFLAGS) test_probleme.c -o test_probleme $(OBJ5)

genere: genere.c
	$(CC) $(CCFLAGS) genere.c -o genere

visualisation: visualisation.c $(OBJ5)
	$(CC) $(CCFLAGS) visualisation.c lib/ez-draw.c -o visualisation $(OBJ5) -lX11 -lXext



#---------------------------------------------------------------------------------

remplir_boite.o: lib/remplir_boite.c
	$(CC) $(CCFLAGS) -c lib/remplir_boite.c

lecture.o: lib/lecture.c
	$(CC) $(CCFLAGS) -c lib/lecture.c

objet.o: lib/objet.c
	$(CC) $(CCFLAGS) -c lib/objet.c

bande.o: lib/bande.c
	$(CC) $(CCFLAGS) -c lib/bande.c

boite.o: lib/boite.c
	$(CC) $(CCFLAGS) -c lib/boite.c

k_largeurs_valides.o: lib/k_largeurs_valides.c
	$(CC) $(CCFLAGS) -c lib/k_largeurs_valides.c

probleme.o: lib/probleme.c
	$(CC) $(CCFLAGS) -c lib/probleme.c


sac_a_dos.o: lib/sac_a_dos.c
	$(CC) $(CCFLAGS) -c lib/sac_a_dos.c

tri.o: lib/tri.c
	$(CC) $(CCFLAGS) -c lib/tri.c

#-----------------------------------------------------------------------------------


clean:
	- rm -f *.o
	- rm genere
	- rm test_objet
	- rm test_boite
	- rm test_lecture
	- rm test_bande
	- rm test_glouton
	- rm test_probleme
	- rm test_SAD
	- rm visualisation
