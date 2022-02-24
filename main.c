#include "fasta.h"
#include "CenCluster.h"
#include "FastCluster.h"
// #include "cstarAlign.h"


void main(void)
{
    // if (argc == 1)
    // {
    //     printf("Usage: %s [options]\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }
    // char *path = "./data/mtgenome.fasta";
    char *path = "/home/siyang/Documents/data/origin/SARS-1020.fasta";

    char **strs = NULL, **labels = NULL;
    size_t num = 0;

    readFasta(path, &strs, &labels, &num);
    printf("%ld\n", num);

    // CENCLU *cels = CenCluster(strs, num, 0.9);
    LENCLU *lenclus = FastCluster(strs, num, 0.9);
    // printf("%d, %d\n", lenclus->numc, lenclus->nums);

}