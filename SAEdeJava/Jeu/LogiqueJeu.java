import javax.swing.*;
import java.util.*;

/**
 * La classe LogiqueJeu gère la logique du jeu. Elle gère le plateau, les actions des joueurs, le calcul du score,
 * ainsi que la gestion de la fin de la partie.
 * @author Malo Reboux
 * @author Dimitri Solar
 */
public class LogiqueJeu {
    private Bloc[][] plateau;
    private int lignes;
    private int colonnes;
    private int score;
    private PanneauJeu panneauJeu;
    private boolean surveillerFinPartie = false;

    /**
     * Constructeur de la classe LogiqueJeu.
     *
     * @param lignes          Le nombre de lignes du plateau de jeu.
     * @param colonnes        Le nombre de colonnes du plateau de jeu.
     * @param plateauInitial  Le plateau de jeu initial, ou null pour générer un plateau aléatoire.
     * @param panneauJeu      Le panneau de jeu sur lequel les informations seront affichées.
     */
    public LogiqueJeu(int lignes, int colonnes, Bloc[][] plateauInitial, PanneauJeu panneauJeu) {
        this.lignes = lignes;
        this.colonnes = colonnes;
        this.panneauJeu = panneauJeu;
        this.plateau = new Bloc[lignes][colonnes];

        if (plateauInitial != null) {
            for (int i = 0; i < lignes; i++) {
                for (int j = 0; j < colonnes; j++) {
                    char c = Character.toUpperCase(plateauInitial[i][j].getLettre());
                    int couleur = switch (c) {
                        case 'R' -> 0;
                        case 'V' -> 1;
                        case 'B' -> 2;
                        default -> -1;
                    };
                    this.plateau[i][j] = new Bloc(couleur);
                }
            }
        } else {
            Random rand = new Random();
            for (int i = 0; i < lignes; i++) {
                for (int j = 0; j < colonnes; j++) {
                    plateau[i][j] = new Bloc(rand.nextInt(3));
                }
            }
        }
    }

    /**
     * Définit le panneau de jeu associé.
     *
     * @param panneauJeu Le panneau de jeu.
     */
    public void setPanneauJeu(PanneauJeu panneauJeu) {
        this.panneauJeu = panneauJeu;
    }

    /**
     * Récupère le plateau de jeu.
     *
     * @return Le plateau de jeu.
     */
    public Bloc[][] getPlateau() {
        return plateau;
    }

    /**
     * Récupère le score actuel du joueur.
     *
     * @return Le score du joueur.
     */
    public int getScore() {
        return score;
    }

    /**
     * Effectue un clic sur le plateau en sélectionnant un groupe de blocs à supprimer et met à jour le score.
     *
     * @param ligne    La ligne où le clic a été effectué.
     * @param colonne La colonne où le clic a été effectué.
     */
    public void clic(int ligne, int colonne) {
        List<Bloc> groupe = trouverGroupe(ligne, colonne);
        if (groupe.size() >= 2) {
            for (Bloc bloc : groupe) {
                plateau[obtenirLigne(bloc)][obtenirColonne(bloc)] = null;
            }
            score += (groupe.size() - 2) * (groupe.size() - 2);
            compacter();
            if (panneauJeu != null) panneauJeu.updateScore();

            if (surveillerFinPartie && !resteGroupes()) {
                finDePartie();
            }
        }
    }

    /**
     * Réorganise les blocs du plateau après un clic pour combler les espaces vides.
     */
    private void compacter() {
        for (int j = 0; j < colonnes; j++) {
            int vide = lignes - 1;
            for (int i = lignes - 1; i >= 0; i--) {
                if (plateau[i][j] != null) {
                    plateau[vide][j] = plateau[i][j];
                    if (vide != i) plateau[i][j] = null;
                    vide--;
                }
            }
        }

        int destination = 0;
        for (int source = 0; source < colonnes; source++) {
            boolean colonneVide = true;
            for (int i = 0; i < lignes; i++) {
                if (plateau[i][source] != null) {
                    colonneVide = false;
                    break;
                }
            }
            if (!colonneVide) {
                if (destination != source) {
                    for (int i = 0; i < lignes; i++) {
                        plateau[i][destination] = plateau[i][source];
                        plateau[i][source] = null;
                    }
                }
                destination++;
            }
        }
    }

    /**
     * Trouve le groupe de blocs connectés à partir d'un bloc donné.
     *
     * @param ligne    La ligne du bloc de départ.
     * @param colonne La colonne du bloc de départ.
     * @return La liste des blocs du groupe.
     */
    public List<Bloc> trouverGroupe(int ligne, int colonne) {
        List<Bloc> groupe = new ArrayList<>();
        boolean[][] visite = new boolean[lignes][colonnes];
        if (plateau[ligne][colonne] == null) return groupe;

        int couleur = plateau[ligne][colonne].getCouleur();
        Queue<int[]> file = new LinkedList<>();
        file.add(new int[]{ligne, colonne});
        visite[ligne][colonne] = true;

        while (!file.isEmpty()) {
            int[] courant = file.poll();
            int i = courant[0];
            int j = courant[1];
            groupe.add(plateau[i][j]);

            int[][] directions = {{-1,0},{1,0},{0,-1},{0,1}};
            for (int[] d : directions) {
                int ni = i + d[0];
                int nj = j + d[1];
                if (ni >= 0 && ni < lignes && nj >= 0 && nj < colonnes && !visite[ni][nj]
                        && plateau[ni][nj] != null && plateau[ni][nj].getCouleur() == couleur) {
                    file.add(new int[]{ni, nj});
                    visite[ni][nj] = true;
                }
            }
        }
        return groupe;
    }

    /**
     * Récupère la ligne du bloc spécifié.
     *
     * @param bloc Le bloc pour lequel obtenir la ligne.
     * @return La ligne du bloc.
     */
    public int obtenirLigne(Bloc bloc) {
        for (int i = 0; i < lignes; i++) {
            for (int j = 0; j < colonnes; j++) {
                if (plateau[i][j] == bloc) return i;
            }
        }
        return -1;
    }

    /**
     * Récupère la colonne du bloc spécifié.
     *
     * @param bloc Le bloc pour lequel obtenir la colonne.
     * @return La colonne du bloc.
     */
    public int obtenirColonne(Bloc bloc) {
        for (int i = 0; i < lignes; i++) {
            for (int j = 0; j < colonnes; j++) {
                if (plateau[i][j] == bloc) return j;
            }
        }
        return -1;
    }

    /**
     * Trouve un groupe de blocs pour la surbrillance à afficher avec la souris.
     *
     * @param ligne    La ligne du bloc à examiner.
     * @param colonne La colonne du bloc à examiner.
     * @return Le groupe de blocs à surligner, ou null si aucun groupe valide n'est trouvé.
     */
    public List<Bloc> trouverGroupePourSurbrillance(int ligne, int colonne) {
        List<Bloc> groupe = trouverGroupe(ligne, colonne);
        return groupe.size() >= 2 ? groupe : null;
    }

    /**
     * Vérifie s'il reste des groupes de blocs valides sur le plateau.
     *
     * @return True si des groupes sont encore présents, sinon False.
     */
    private boolean resteGroupes() {
        for (int i = 0; i < lignes; i++) {
            for (int j = 0; j < colonnes; j++) {
                List<Bloc> groupe = trouverGroupe(i, j);
                if (groupe.size() >= 2) return true;
            }
        }
        return false;
    }

    /**
     * Affiche la fin de la partie et propose au joueur de rejouer ou quitter.
     */
    private void finDePartie() {
        int reponse = JOptionPane.showOptionDialog(null,
                "Partie terminée ! Score final : " + score + "\nVoulez-vous rejouer ?",
                "Fin de partie",
                JOptionPane.DEFAULT_OPTION,
                JOptionPane.PLAIN_MESSAGE,
                null,
                new String[]{"Rejouer", "Quitter"},
                "Rejouer");

        if (reponse == JOptionPane.YES_OPTION) {
            SwingUtilities.invokeLater(() -> {
                SameGame.main(new String[0]);
            });
        } else {
            System.exit(0);
        }
    }

    /**
     * Définit si la fin de partie doit être surveillée.
     *
     * @param surveillerFinPartie True pour surveiller la fin de partie, sinon False.
     */
    public void setSurveillerFinPartie(boolean surveillerFinPartie) {
        this.surveillerFinPartie = surveillerFinPartie;
    }
}
