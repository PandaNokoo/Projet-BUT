import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * Classe qui écoute les événements de souris sur le panneau de jeu et déclenche des actions
 * telles que les sélections de blocs ou les clics de souris.
 * @author Malo Reboux
 * @author Dimitri Solar
 */
public class EcouteurDeSouris extends MouseAdapter {
    private PanneauJeu panneauJeu;

    /**
     * Constructeur de l'écouteur de souris.
     * 
     * @param panneauJeu Le panneau de jeu sur lequel l'écouteur de souris est activé.
     */
    public EcouteurDeSouris(PanneauJeu panneauJeu) {
        this.panneauJeu = panneauJeu;
    }

    /**
     * Méthode appelée lorsqu'un clic de souris est effectué.
     * Cette méthode gère la logique de sélection et de suppression de blocs.
     * 
     * @param e L'événement généré par le clic de souris.
     */
   @Override
    public void mouseClicked(MouseEvent e) {
        int largeurBloc = panneauJeu.getWidth() / panneauJeu.getLogiqueJeu().getPlateau()[0].length;
        int hauteurBloc = panneauJeu.getHeight() / panneauJeu.getLogiqueJeu().getPlateau().length;

        int colonne = e.getX() / largeurBloc;
        int ligne = e.getY() / hauteurBloc;

        panneauJeu.getLogiqueJeu().clic(ligne, colonne);
        
        panneauJeu.repaint();
    }
}
