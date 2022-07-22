/* Paul Gaborit - IMT Mines Albi - 2020 */
#ifndef PILE_INTS_H
#define PILE_INTS_H

typedef struct pile_ints_interne {
  int * valeurs;
  int taille_max;
  int cour;
} pile_ints_interne;

typedef pile_ints_interne * pile_ints;

pile_ints creer_pile_ints(int taille_max);
void detruire_pile_ints(pile_ints p);
void empile(pile_ints p, int val);
int depile(pile_ints p);
int est_vide(pile_ints p);

#endif

