import javax.swing.*;
import java.awt.*;
import java.util.List;

/**
 * Ce panneau représente le plateau du jeu et le score.
 * @author Malo Reboux
 * @author Dimitri Solar
 */
public class PanneauJeu extends JPanel {

    /** La logique du jeu. */
    private LogiqueJeu logiqueJeu;

    /** L'écouteur d'événements de souris pour les interactions sur le plateau. */
    private EcouteurDeSouris ecouteurDeSouris;

    /** Le label affichant le score du jeu. */
    private JLabel scoreLabel;

    /** La position de la souris en ligne. */
    int sourisLigne = -1;

    /** La position de la souris en colonne. */
    int sourisColonne = -1;

    /** Liste des blocs à surbriller. */
    List<Bloc> groupeSurbrillance = null;

    /** L'objet gérant la surbrillance des blocs au survol de la souris. */
    private SurbrillanceSouris surbrillanceSouris;

    /**
     * Crée un panneau de jeu avec la logique du jeu spécifiée.
     * @param logiqueJeu La logique du jeu.
     */
    public PanneauJeu(LogiqueJeu logiqueJeu) {
        this.logiqueJeu = logiqueJeu;
        this.ecouteurDeSouris = new EcouteurDeSouris(this);
        this.addMouseListener(ecouteurDeSouris);

        surbrillanceSouris = new SurbrillanceSouris(this);
        this.addMouseMotionListener(surbrillanceSouris);
    }

    /**
     * Méthode appelée pour dessiner le contenu du panneau de jeu.
     * Cette méthode est responsable de dessiner les blocs du plateau ainsi que les surbrillances.
     * @param g L'objet Graphics utilisé pour dessiner sur le panneau.
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Bloc[][] plateau = logiqueJeu.getPlateau();

        // Vérification que le plateau n'est pas vide
        if (plateau == null || plateau.length == 0 || plateau[0].length == 0) {
            return;
        }

        int lignes = plateau.length;
        int colonnes = plateau[0].length;

        int largeurBloc = Math.min(getWidth() / colonnes, getHeight() / lignes);
        int hauteurBloc = largeurBloc;

        for (int i = 0; i < lignes; i++) {
            for (int j = 0; j < colonnes; j++) {
                if (plateau[i][j] != null && plateau[i][j].getCouleur() != -1) {
                    g.setColor(obtenirCouleur(plateau[i][j].getCouleur()));
                    g.fillRect(j * largeurBloc, i * hauteurBloc, largeurBloc, hauteurBloc);
                    g.setColor(Color.BLACK);
                    g.drawRect(j * largeurBloc, i * hauteurBloc, largeurBloc, hauteurBloc);

                    // Dessiner la surbrillance du groupe
                    if (groupeSurbrillance != null) {
                        for (Bloc bloc : groupeSurbrillance) {
                            int ligneBloc = logiqueJeu.obtenirLigne(bloc);
                            int colonneBloc = logiqueJeu.obtenirColonne(bloc);
                            if (ligneBloc == i && colonneBloc == j) {
                                g.setColor(Color.YELLOW);
                                g.drawRect(j * largeurBloc + 2, i * hauteurBloc + 2, largeurBloc - 4, hauteurBloc - 4);
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * Retourne la couleur correspondante à un code de couleur.
     * @param couleur Le code couleur à convertir.
     * @return La couleur correspondante.
     */
    private Color obtenirCouleur(int couleur) {
        switch (couleur) {
            case 0: return Color.RED;
            case 1: return Color.GREEN;
            case 2: return Color.BLUE;
            default: return null;
        }
    }

    /**
     * Met à jour le label du score.
     */
    public void updateScore() {
        if (scoreLabel != null) {
            scoreLabel.setText("Score: " + logiqueJeu.getScore());
        }
    }

    /**
     * Définit le label du score.
     * @param scoreLabel Le label du score.
     */
    public void setScoreLabel(JLabel scoreLabel) {
        this.scoreLabel = scoreLabel;
    }

    /**
     * Redessine le panneau.
     */
    public void repaintPanneau() {
        repaint();
    }

    /**
     * Retourne la logique du jeu.
     * @return La logique du jeu.
     */
    public LogiqueJeu getLogiqueJeu() {
        return logiqueJeu;
    }
}
