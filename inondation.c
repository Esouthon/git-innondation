#include <stdio.h>
#include <stdlib.h>
#include "libimage.h"
#include "pile-ints.h"
#include <math.h>



int testseuil(couleur pixel, double seuil) {
  /*Fonction qui test si le pixel est bien en dessous du seuil */
  int a;
  double u;
  u=pow(pixel.rouge,2)+pow(pixel.vert,2)+pow(pixel.bleu,2)
  if u<pow(seuil,2) {
    a=1;
  }
  else {
    a=0;
  }
  return(a)
}

/*Fonction innondation*/
image inondation(image im_in, int dx, int dy, couleur remplissage, double seuil) {
  image im_out, im_controle;
  couleur blc,noir;
  int x,y,maxi,x_k,y_k,x_k_gauche,x_k_droite,y_k_haut,y_k_bas;
  pile_ints p_y,p_x;



  blc.rouge=255
  blc.vert=255
  blc.bleu=255
  noir.rouge=0
  noir.vert=0
  noir.bleu=0
  maxi=1000000

  im_out = nouvelle_image(im_in.largeur, im_in.hauteur);
  im_controle= nouvelle_image(im_in.largeur, im_in.hauteur);
  p_x=creer_pile_ints(maxi)
  p_y=creer_pile_ints(maxi)

  /* Ici on rend l'image de controle blanche
   On fait la copie ,im_out, de l'image de départ  */
  for (x=0;x<im_in.largeur;x++) {
    for (y=0;y<im_in.hauteur;y++) {
      change_couleur(im_controle,x,y,blc);
      change_couleur(im_out,x,y,lire_couleur(im_in,x,y));
    }
  }
/* On fait la première étape de l'innondation */
  empile(p_x,dx)
  empile(p_y,dy)
  change_couleur(im_controle,dx,dy,noir)
  change_couleur(im_out,dx,dy,remplissage)

/* On dépile les coordonnees des pixels et on regarde s'ils sont sujets à être innondé. */
while est_vide(p_x)!=0 {
    x_k=depile(p_x)
    y_k=depile(p_y)
    /* Voici tous les pixels voisins d'un pixel de départ */
    x_k_gauche=x_k-1;
    x_k_droite=x_k+1;
    y_k_haut=y_k+1;
    y_k_bas=y_k-1;
    /* On test si le voisin de gauche est sujet à l'innondation */
    if x_k>0 && lire_couleur(im_controle,x_k_gauche,y_k)==blc && testseuil(lire_couleur(im_in,x_k_gauche,y_k),seuil)==1{
      empile(p_x,x_k_gauche)
      empile(p_y,y_k)
      change_couleur(im_controle,x_k_gauche,y_k,noir)
      change_couleur(im_out,x_k_gauche,y_k,remplissage)
    }
    /* On test si le voisin de droite est sujet à l'innondation */
    if x_k_droite<im_in.largeur && lire_couleur(im_controle,x_k_droite,y_k)==blc && testseuil(lire_couleur(im_in,x_k_droite,y_k),seuil)==1 {
      empile(p_x,x_k_droite)
      empile(p_y,y_k)
      change_couleur(im_controle,x_k_droite,y_k,noir)
      change_couleur(im_out,x_k_droite,y_k,remplissage)
    }
    /* On test si le voisin du haut est sujet à l'innondation */
    if y_k_haut<im_in.hauteur && lire_couleur(im_controle,x_k,y_k_haut)==blc && testseuil(lire_couleur(im_in,x_k,y_k_haut),seuil)==1 {
      empile(p_x,x_k)
      empile(p_y,y_k_haut)
      change_couleur(im_controle,x_k,y_k_haut,noir)
      change_couleur(im_out,x_k,y_k_haut,remplissage)
    }
    /* On test si le voisin du bas est sujet à l'innondation */
    if y_k_bas<im_in.hauteur && lire_couleur(im_controle,x_k,y_k_bas)==blc && testseuil(lire_couleur(im_in,x_k,y_k_bas),seuil)==1 {
      empile(p_x,x_k)
      empile(p_y,y_k_bas)
      change_couleur(im_controle,x_k,y_k_bas,noir)
      change_couleur(im_out,x_k_droite,y_k_bas,remplissage)
    }
    return(im_out)
}

void usage(char * nomprog, char * erreur) {
  fprintf(stderr, "\n");
  fprintf(stderr, "!!! %s: %s !!!\n", nomprog, erreur);
  fprintf(stderr, "\n");
  fprintf(stderr, "Usage: %s im_in.ppm x,y r,v,b d im_out.ppm\n", nomprog);
  fprintf(stderr, "\n");
  fprintf(stderr, "\tim_in.ppm, im_out.pmm: nom des images source et resultat\n");
  fprintf(stderr, "\tx,y: position du point de depart dans l'image\n");
  fprintf(stderr, "\tr,v,b: composantes de la couleur de remplissage (entiers: 0-255)\n");
  fprintf(stderr, "\td: seuil pour la distance colorimetrique (0-442)\n");
  fprintf(stderr, "\n");
  exit(1);
}

int main(int argc, char * argv[]) {
  image im_entree, im_resultat;
  int dx, dy;
  couleur remplissage;
  double seuil;

  // test du nombre d'arguments
  if (argc != 6) {
    usage(argv[0], "nombre d'arguments incorrect");
  }

  // lecture de l'image a traiter
  im_entree = lire_image(argv[1]);

  // les coordonnees du point de depart de l'inondation
  if (sscanf(argv[2], "%d,%d", &dx, &dy) != 2) {
    usage(argv[0], "coordonnees x,y illisibles");
  }
  if (dx < 0 || dx >= im_entree.largeur || dy < 0 || dy >= im_entree.hauteur) {
    usage(argv[0], "position de depart hors image");
  }

  // les 3 composantes de la couleur de remplissage
  if (sscanf(argv[3], "%d,%d,%d", &remplissage.rouge, &remplissage.vert, &remplissage.bleu) != 3) {
    usage(argv[0], "composantes r,v,b illisibles");
  }
  if (remplissage.rouge < 0 || remplissage.rouge > 255) {
    usage(argv[0], "composante rouge hors bornes (0-255)");
  }
  if (remplissage.vert < 0 || remplissage.vert > 255) {
    usage(argv[0], "composante verte hors bornes (0-255)");
  }
  if (remplissage.bleu < 0 || remplissage.bleu > 255) {
    usage(argv[0], "composante bleu hors bornes (0-255)");
  }

  // la seuil  pour la distance colorimetrique
  if (sscanf(argv[4], "%lf", &seuil) != 1) {
    usage(argv[0], "seuil illisible");
  }
  if (seuil < 0 || seuil > 442) {
    usage(argv[0], "seuil hors bornes (0-442)");
  }

  // inondation effective
  im_resultat = inondation(im_entree, dx, dy, remplissage, seuil);

  // ecriture de l'image produite dans un fichier
  ecrire_image(im_resultat, argv[5]);

  return 0;
}
