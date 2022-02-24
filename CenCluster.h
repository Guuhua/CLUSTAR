#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 100

typedef struct cenclusters
{
    /* data */
    int **clusters;
    int *numclusters;
    int num;
}CENCLU;

int getLongest(int *Lens, int numL);

int *pickKids(float *sims, int idxc, int numL, float sim, int *numK);

int *delOutliers(char **strs, int *simOnes, int *idxMap, int *numK, float sim);

CENCLU *CenCluster(char **strs, int num, float sim);

void freeCENCLU(CENCLU *cenclu);