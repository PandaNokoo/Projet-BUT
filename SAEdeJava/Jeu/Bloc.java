/**
 * Représente un bloc dans le jeu.
 * Ce bloc a une couleur et une lettre associée.
 */
public class Bloc {

    private int couleur; // 0 = Rouge, 1 = Vert, 2 = Bleu
    private char lettre;


    /**
     * Crée un bloc avec la couleur spécifiée.
     * @param couleur La couleur du bloc (un entier représentant la couleur).
     * @author Malo Reboux
     * @author Dimitri Solar
     */

    public Bloc(int couleur) {
        this.couleur = couleur;
        this.lettre = couleur == 0 ? 'R' : couleur == 1 ? 'V' : 'B';
    }

    /**
     * Obtient la couleur du bloc.
     * @return La couleur du bloc.
     */

    public int getCouleur() {
        return couleur;
    }

     /**
     * Définit la couleur du bloc.
     * @param couleur La couleur à affecter au bloc.
     */

    public void setCouleur(int couleur) {
        this.couleur = couleur;
    }


     /**
     * Obtient la lettre associée au bloc.
     * @return La lettre du bloc.
     */

    public char getLettre() {
        return lettre;
    }

     /**
     * Définit la lettre associée au bloc.
     * @param lettre La lettre à affecter au bloc.
     */

    public void setLettre(char lettre) {
        this.lettre = lettre;
    }
}
