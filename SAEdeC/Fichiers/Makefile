### VARIABLES ###

CC = gcc
CFLAGS = -Wall -ansi -pedantic
LIBS = -lgraph
EXE = projet  # Nom de l'exécutable final

# Liste des fichiers objets (ajustée selon les fichiers listés)
OFILES = AffichageGrille.o \
         CreationGrille.o \
         main.o \
         Menu.o \
         MenuAffichage.o \
         MenuInteractions.o \
         MenuOption.o \
         Recommencer.o \
         Score.o \
         Sprites.o

### BUT PAR DÉFAUT ###

but : ${EXE}

### RÈGLES ESSENTIELLES ###

# Dépendances pour les fichiers objets

AffichageGrille.o : AffichageGrille.c AffichageGrille.h constantes.h
	$(CC) $(CFLAGS) -c AffichageGrille.c

CreationGrille.o : CreationGrille.c CreationGrille.h constantes.h
	$(CC) $(CFLAGS) -c CreationGrille.c

main.o : main.c Menu.h AffichageGrille.h CreationGrille.h MenuAffichage.h MenuInteractions.h MenuOption.h Recommencer.h Score.h Sprites.h constantes.h
	$(CC) $(CFLAGS) -c main.c

Menu.o : Menu.c Menu.h constantes.h
	$(CC) $(CFLAGS) -c Menu.c

MenuAffichage.o : MenuAffichage.c MenuAffichage.h Menu.h constantes.h
	$(CC) $(CFLAGS) -c MenuAffichage.c

MenuInteractions.o : MenuInteractions.c MenuInteractions.h Menu.h CreationGrille.h constantes.h
	$(CC) $(CFLAGS) -c MenuInteractions.c

MenuOption.o : MenuOption.c MenuOption.h CreationGrille.h MenuInteractions.h constantes.h
	$(CC) $(CFLAGS) -c MenuOption.c

Recommencer.o : Recommencer.c Recommencer.h Menu.h AffichageGrille.h CreationGrille.h MenuAffichage.h constantes.h
	$(CC) $(CFLAGS) -c Recommencer.c

Score.o : Score.c Score.h constantes.h
	$(CC) $(CFLAGS) -c Score.c

Sprites.o : Sprites.c Sprites.h constantes.h
	$(CC) $(CFLAGS) -c Sprites.c

# Génération de l'exécutable
${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES} ${LIBS}

### RÈGLES OPTIONNELLES ###

run : but
	./${EXE}

clean :
	-rm -f ${OFILES} ${EXE}

mrproper : clean but

### BUTS FACTICES ###
.PHONY : but clean mrproper

### FIN ###
