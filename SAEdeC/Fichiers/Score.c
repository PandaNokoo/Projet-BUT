#include "Score.h"
#include "Recommencer.h"
#include <stdlib.h>
#include <graph.h>
#include "constantes.h"

#define IMAGE_FIN "ImageFin.png"
#define BOUTON_X (LARGEUR_FENETRE - 250)  
#define BOUTON_Y 100                      
#define BOUTON_LARGEUR 200
#define BOUTON_HAUTEUR 50


void revenirAuMenu();

void afficherScore(int gagnant) {
    int sourisX,sourisY;
 
    EffacerEcran(CouleurParNom("white"));
    ChargerImageFond(IMAGE_FIN);

    
    if (gagnant == 1) {
        ChoisirCouleurDessin(CouleurParNom("Blue"));
        EcrireTexte(LARGEUR_FENETRE / 2.27 - 100, HAUTEUR_FENETRE / 3, "Joueur 1 a gagne !", 2);
    } else if (gagnant == 2) {
        ChoisirCouleurDessin(CouleurParNom("Red"));
        EcrireTexte(LARGEUR_FENETRE / 2.27- 100, HAUTEUR_FENETRE / 3, "Joueur 2 a gagne !", 2);
    }

   
    ChoisirCouleurDessin(CouleurParNom("green"));
    RemplirRectangle(BOUTON_X, BOUTON_Y, BOUTON_LARGEUR, BOUTON_HAUTEUR);

    
    ChoisirCouleurDessin(CouleurParNom("white"));
    EcrireTexte(BOUTON_X + 60, BOUTON_Y + 30, "Rejouer", 2);

  
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(20, 30, "Appuyez sur Echap pour quitter.", 1);  

    
    while (1) {
        if (ToucheEnAttente() && Touche() == XK_Escape) {
            FermerGraphique();
            exit(0); 
        } else if (SourisCliquee()) {
            SourisPosition();
             sourisX = _X;
             sourisY = _Y;

           
            if (sourisX >= BOUTON_X && sourisX <= BOUTON_X + BOUTON_LARGEUR &&
                sourisY >= BOUTON_Y && sourisY <= BOUTON_Y + BOUTON_HAUTEUR) {
                revenirAuMenu();  
                break;
            }
        }
    }
}
