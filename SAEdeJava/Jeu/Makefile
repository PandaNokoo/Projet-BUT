# Variables
JC = javac
JCFLAGS = -encoding UTF-8 -implicit:none

JVM = java
JVMFLAGS = 

# Règles essentielles
SameGame.class: SameGame.java ChoixModeJeu.class PanneauJeu.class LogiqueJeu.class Bloc.class EcouteurDeSouris.class
	${JC} ${JCFLAGS} SameGame.java

ChoixModeJeu.class: ChoixModeJeu.java LogiqueJeu.class Bloc.class
	${JC} ${JCFLAGS} ChoixModeJeu.java

PanneauJeu.class: PanneauJeu.java LogiqueJeu.class Bloc.class EcouteurDeSouris.class SurbrillanceSouris.class
	${JC} ${JCFLAGS} PanneauJeu.java

SurbrillanceSouris.class: SurbrillanceSouris.java
	${JC} ${JCFLAGS} SurbrillanceSouris.java
	
LogiqueJeu.class: LogiqueJeu.java Bloc.class
	${JC} ${JCFLAGS} LogiqueJeu.java

EcouteurDeSouris.class: EcouteurDeSouris.java
	${JC} ${JCFLAGS} EcouteurDeSouris.java

Bloc.class: Bloc.java
	${JC} ${JCFLAGS} Bloc.java

# Règles optionnelles
run: SameGame.class
	${JVM} ${JVMFLAGS} SameGame

clean:
	-rm -f *.class

mrproper: clean

# Buts factices
.PHONY: run clean mrproper
