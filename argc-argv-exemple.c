#include <stdlib.h>
#include <stdio.h>

void usage(char * message, char *nomprog)
{
  fprintf(stderr, "Erreur: %s\n", message);
  fprintf(stderr, "Usage : %s nomimage1 nomimage2\n", nomprog);
  exit(1);
}

int main(int argc, char * argv[])
{

  /* on teste le nombre d'arguments */
  if (argc < 3) {
    usage("pas assez d'arguments", argv[0]);
  } else if (argc > 3) {
    usage("trop d'arguments", argv[0]);
  }

  printf("Le nom de la 1re image est '%s'\n", argv[1]);
  printf("Le nom de la 2e image est '%s'\n", argv[2]);

  return(0);
}
