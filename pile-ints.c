/* Paul Gaborit - IMT Mines Albi - 2020 */
#include <stdio.h>
#include <stdlib.h>
#include "pile-ints.h"

pile_ints creer_pile_ints(int taille_max) {
  pile_ints newpile;
  newpile = (pile_ints_interne *) malloc(sizeof(pile_ints_interne));
  if (newpile == NULL) {
    fprintf(stderr, "Erreur fatale (%s): allocation de la pile interne impossible!\n", __func__);
    exit(1);
  }
  newpile->valeurs = (int *) calloc(taille_max, sizeof(int));
  if (newpile->valeurs == NULL) {
    fprintf(stderr, "Erreur fatale (%s): allocation de la pile impossible!\n", __func__);
    exit(1);
  }
  newpile->taille_max = taille_max;
  newpile->cour = -1;

  return newpile;
}

void detruire_pile_ints(pile_ints p) {
  free(p);
}

void empile(pile_ints p, int val) {
  p->cour++;
  if (p->taille_max == p->cour) {
    fprintf(stderr, "Erreur fatale (%s): pile pleine (max=%d)\n", __func__, p->taille_max);
    exit(1);
  }
  p->valeurs[p->cour] = val;
}

int depile(pile_ints p) {
  if (p->cour < 0) {
    fprintf(stderr, "Erreur fatale (%s): pile vide\n", __func__);
    exit(1);
  }
  return(p->valeurs[p->cour--]);
}

int est_vide(pile_ints p) {
  return (p->cour < 0);
}
