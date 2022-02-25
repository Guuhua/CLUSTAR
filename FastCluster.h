#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LENCLUSTER
{
    /* data */
    int *cluIDx;
    int *startIdx;
    // numc: the number of seqs
    // nums: the number of clus 
    int numc, nums;
}LENCLU;

LENCLU *LenCluster(char **strs, int num);

LENCLU *FastCluster(char **strs, int num, float sim);

void freeLENCLU(LENCLU *lenclu);