#include "MenuAffichage.h"
#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <graph.h>
#include "constantes.h"
#include "MenuInteractions.h"

int fondMenu;
int fondJeu1;
int fondJeu2;

void chargerSprites() {

   

    fondMenu = ChargerSprite(IMAGE_MENU);   
    fondJeu1 = ChargerSprite(IMAGE_FOND2);  
    fondJeu2 = ChargerSprite(IMAGE_FOND2);  

    
    
    if (fondMenu == -1) {
        fprintf(stderr, "Erreur de chargement de l'image du menu : %s (code d'erreur: %d)\n", IMAGE_MENU, errno);
    }

    if (fondJeu1 == -1) {
        fprintf(stderr, "Erreur de chargement de l'image de fond 1 : %s (code d'erreur: %d)\n", IMAGE_FOND1, errno );
    }
    if (fondJeu2 == -1) {
        fprintf(stderr, "Erreur de chargement de l'image de fond 2 : %s (code d'erreur: %d)\n", IMAGE_FOND2, errno);
    }

    if (fondMenu == -1 || fondJeu1 == -1 || fondJeu2 == -1) {
        exit(EXIT_FAILURE);
    }
}


void afficherFondMenu() {
    ChargerImageFond(IMAGE_MENU);  
}

void afficherFondJeu1() {
    ChargerImageFond(IMAGE_FOND2); 
}

void afficherFondJeu2() {
    ChargerImageFond(IMAGE_FOND2); 
}

void libererSprites() {
    LibererSprite(fondMenu);
    LibererSprite(fondJeu1);
    LibererSprite(fondJeu2);
}

void TailleJeux() {

    int i;
    int taille;
    int optionX;
    int optionY; 
    int caseX; 
    int caseY; 
    int caseSize;
    char optionText[10]; 
    int boutonLargeur;
    int boutonHauteur; 
    int boutonX;
    int boutonY;
    char *texte = "Commencer"; 
    int largeurTexte; 
    int texteX; 
    int texteY; 
    
    int PositionTexteX = 120; 
    int PositionTexteY = 145; 

    afficherFondMenu(); 

    
    ChoisirCouleurDessin(CouleurParNom("white")); 
    EcrireTexte(120, 80, "Choisissez la taille de la grille :", 2);

    for (i = 0; i < MAX_OPTIONS; i++) {

        taille = i + 3; 
        optionX = 75; 
        optionY = 130 + (i * 30); 
        caseX = optionX + 150; 
        caseY = optionY - 5; 
        caseSize = 20; 

        ChoisirCouleurDessin(CouleurParNom("white"));
        RemplirRectangle(caseX, caseY, caseSize, caseSize);
        if (casesCochees[i]) { 
            ChoisirCouleurDessin(CouleurParNom("red")); 
            RemplirRectangle(caseX + 2, caseY + 2, caseSize - 4, caseSize - 4); 
        }

        sprintf(optionText, "%dx%d", taille, taille);
        ChoisirCouleurDessin(CouleurParNom("white")); 
        EcrireTexte(PositionTexteX, PositionTexteY + (i * 30), optionText, 2);
    }

    
    boutonLargeur = LARGEUR_BOUTON; 
    boutonHauteur = HAUTEUR_BOUTON; 
    boutonX = (LARGEUR_FENETRE - boutonLargeur) / 2; 
    boutonY = 400; 

    ChoisirCouleurDessin(CouleurParNom("red")); 
    RemplirRectangle(boutonX, boutonY, boutonLargeur, boutonHauteur); 

    ChoisirCouleurDessin(CouleurParNom("black")); 
    DessinerRectangle(boutonX, boutonY, boutonLargeur, boutonHauteur); 

    ChoisirCouleurDessin(CouleurParNom("black")); 
    largeurTexte = TailleChaineEcran(texte, 2); 
    texteX = boutonX + (boutonLargeur / 2) - (largeurTexte / 2); 
    texteY = boutonY + boutonHauteur - (TailleSupPolice(2) / 2); 
    EcrireTexte(texteX, texteY, texte, 2); 

    afficherOptionsJoueurs(); 
}
