import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Cette classe gère le choix du mode de jeu, permettant de choisir entre un plateau généré aléatoirement
 * ou un plateau chargé depuis un fichier.
 * @author Malo Reboux
 * @author Dimitri Solar
 */
public class ChoixModeJeu {

    /**
     * Permet à l'utilisateur de choisir entre un plateau aléatoire ou un plateau chargé depuis un fichier.
     * @param lignes Le nombre de lignes du plateau.
     * @param colonnes Le nombre de colonnes du plateau.
     * @return Le plateau de jeu, soit généré aléatoirement, soit chargé depuis un fichier.
     */
    public static Bloc[][] obtenirPlateauDepuisChoix(int lignes, int colonnes) {
        int choix = JOptionPane.showOptionDialog(null,
                "                   Choisissez le mode de jeu",
                "Mode de Jeu",
                JOptionPane.DEFAULT_OPTION,
                JOptionPane.PLAIN_MESSAGE,
                null,
                new String[]{"Aléatoire", "Charger un fichier"},
                "Aléatoire");

        if (choix == 1) {
            return chargerPlateauDepuisFichier(lignes, colonnes);
        } else {
            return genererPlateauAleatoire(lignes, colonnes);
        }
    }

    /**
     * Charge un plateau depuis un fichier sélectionné par l'utilisateur.
     * Le fichier doit contenir un plateau de taille spécifique avec des lettres représentant les couleurs.
     * @param lignes Le nombre de lignes du plateau.
     * @param colonnes Le nombre de colonnes du plateau.
     * @return Le plateau de jeu chargé depuis le fichier, ou un plateau aléatoire en cas d'erreur.
     */
    private static Bloc[][] chargerPlateauDepuisFichier(int lignes, int colonnes) {
        JFileChooser fileChooser = new JFileChooser();
        int returnValue = fileChooser.showOpenDialog(null);
        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                List<String> lignesFichier = new ArrayList<>();
                String ligne;
                while ((ligne = br.readLine()) != null) {
                    lignesFichier.add(ligne);
                }

                if (lignesFichier.size() != lignes || lignesFichier.get(0).length() != colonnes) {
                    JOptionPane.showMessageDialog(null, "Le fichier ne correspond pas à la taille du plateau.");
                    return genererPlateauAleatoire(lignes, colonnes); // Retourner un plateau aléatoire en cas d'erreur
                }

                Bloc[][] plateau = new Bloc[lignes][colonnes];
                for (int i = 0; i < lignes; i++) {
                    for (int j = 0; j < colonnes; j++) {
                        char couleurChar = lignesFichier.get(i).charAt(j);
                        int couleur = (couleurChar == 'R') ? 0 : (couleurChar == 'V') ? 1 : 2;
                        plateau[i][j] = new Bloc(couleur);
                    }
                }
                return plateau;

            } catch (IOException e) {
                JOptionPane.showMessageDialog(null, "Erreur lors de la lecture du fichier.");
            }
        }
        return genererPlateauAleatoire(lignes, colonnes); // Retourner un plateau aléatoire si aucun fichier n'est sélectionné
    }

    /**
     * Génère un plateau aléatoire avec des couleurs choisies au hasard pour chaque bloc.
     * @param lignes Le nombre de lignes du plateau.
     * @param colonnes Le nombre de colonnes du plateau.
     * @return Un plateau de jeu généré aléatoirement.
     */
    private static Bloc[][] genererPlateauAleatoire(int lignes, int colonnes) {
        Bloc[][] plateau = new Bloc[lignes][colonnes];
        for (int i = 0; i < lignes; i++) {
            for (int j = 0; j < colonnes; j++) {
                plateau[i][j] = new Bloc((int) (Math.random() * 3)); // Génère un nombre aléatoire entre 0 et 2
            }
        }
        return plateau;
    }
}
