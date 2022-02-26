#include "fasta.h"
#include "FastCluster.h"


void main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("\nerror!\n");
        printf("\n  Usage: %s [input filename in fasta format] [output filename]", argv[0]);
        printf("\nExample: %s ./test/rna.fasta ./test/rna.clstr\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *path = argv[1];
    char *wpath = argv[2];

    FILE *fp = fopen(wpath, "w");
    if (fp == NULL) 
    {
        printf("Couldn't open the file %s\n", wpath);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    char **strs = NULL, **labels = NULL;
    size_t num = 0;

    readFasta(path, &strs, &labels, &num);

    LENCLU *lenclus = FastCluster(strs, num, 0.9);

    for (int i = 0; i < lenclus->nums; i++)
    {
        fprintf(fp, ">Cluster %d\n", i);
        for (int j = lenclus->startIdx[i], k = 0; j < lenclus->startIdx[i+1]; j++, k++)
        {
            fprintf(fp, "%-6d %ldnt, ", k, strlen(strs[lenclus->cluIDx[j]]));
            fprintf(fp, ">%s\n", labels[lenclus->cluIDx[j]]);
        }
    }

    printf("DONE!\n");

    for (int i = 0; i < num; i++)
    {
        free(labels[i]);
        free(strs[i]);
    }
    free(strs);
    free(labels);
    freeLENCLU(lenclus);

}
