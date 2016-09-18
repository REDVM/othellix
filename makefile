CFLAGS = -W -Wall -pedantic
OPTIMISATION = -O3 -fomit-frame-pointer
EXE = Othellix 

THREAD = '-lpthread'
GTK = `pkg-config --cflags --libs gtk+-2.0`

JEU = main.o init.o gestion.o victoire.o
ALGO = placement.o renversement.o
IN_OUT = affichage.o enregistrement.o
IA = CPU.o evaluation.o
INTERFACE = callbacks.o signaux.o

Othellix: $(JEU) $(ALGO) $(IN_OUT) $(IA) $(INTERFACE)
	gcc $(OPTIMISATION) $^ $(GTK) $(THREAD) -o $(EXE) 

%.o : %.c main.h
	gcc $(OPTIMISATION) $(GTK) $(THREAD) -c $<

clean:
	rm -f *.o
	
clean_all:
	rm -f *.o $(EXE)
	
archive: 
	zip -9 Othellix.zip *.c *.h *.data Othellix makefile interface.glade images/* rapport.pdf

exec:
	make
	./Othellix
