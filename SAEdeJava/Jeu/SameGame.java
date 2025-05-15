import javax.swing.*;
import java.awt.*;

/**
 * Cette classe contient le point d'entrée du programme, le jeu `SameGame`.
 * Elle initialise l'interface graphique et commence le jeu.
 * Le jeu permet à l'utilisateur de jouer à une version interactive de SameGame.
 * @author Malo Reboux 
 * @author Dimitri Solar
 */

public class SameGame {

 /**
     * Méthode principale qui démarre le jeu.
     * @param args Arguments de la ligne de commande (non utilisés ici).
     */

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            int lignes = 10;
            int colonnes = 15;

            Bloc[][] plateauInitial = ChoixModeJeu.obtenirPlateauDepuisChoix(lignes, colonnes);
            LogiqueJeu logiqueJeu = new LogiqueJeu(lignes, colonnes, plateauInitial, null);
            PanneauJeu panneauJeu = new PanneauJeu(logiqueJeu);
            logiqueJeu.setPanneauJeu(panneauJeu);
            logiqueJeu.setSurveillerFinPartie(true);

            JLabel labelScore = new JLabel("Score : " + logiqueJeu.getScore());
            panneauJeu.setScoreLabel(labelScore);

            JPanel panneauScore = new JPanel();
            panneauScore.add(labelScore);

            JFrame fenetre = new JFrame("SameGame");
            fenetre.setLayout(new java.awt.BorderLayout());
            fenetre.add(panneauScore, java.awt.BorderLayout.SOUTH);
            fenetre.add(panneauJeu, java.awt.BorderLayout.CENTER);
            fenetre.setSize(colonnes * 30, lignes * 30 + 50);
            fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            fenetre.setVisible(true);
        });
    }
}
