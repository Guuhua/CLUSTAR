#include "FastCluster.h"
#include "CenCluster.h"


LENCLU *LenCluster(char **strs, int num)
{
    int *Lens = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++)
    {
        Lens[i] = strlen(strs[i]);
    }
    int remainder = num, count = 0;
    int *residx = (int *)malloc(sizeof(int) * num);
    int *records = (int *)malloc(sizeof(int) * SIZE), idxR = 0, numsize = 1;
    while (remainder > 0)
    {
        int idxc = getLongest(Lens, num);
        int length = (int) Lens[idxc] * 0.9;
        Lens[idxc] = -1;

        if (idxR >= (numsize * SIZE))
        {
            records = (int *)realloc(records, sizeof(int) * SIZE * (++numsize));
        }
        records[idxR++] = count;
        residx[count++] = idxc;
        for (int i = 0; i < num; i++)
        {
            if (Lens[i] >= length)
            {
                residx[count++] = i;
                Lens[i] = -1;
            } 
        }
        remainder = num - count;
    }
    records = (int *)realloc(records, sizeof(int) * (idxR + 1));
    records[idxR] = num;
    
    LENCLU *lclu = (LENCLU *)malloc(sizeof(LENCLU));
    lclu->cluIDx = residx;
    lclu->startIdx = records;
    lclu->numc = num;
    lclu->nums = idxR;
    return lclu;
}


LENCLU *FastCluster(char **strs, int num, float sim)
{
    // 1. lens clustering
    // printf("1. lens clustering \n");
    LENCLU *lenclus = LenCluster(strs, num);
    int *residx = (int *)malloc(sizeof(int) * num), count = 0;
    int *records = (int *)malloc(sizeof(int) * SIZE), idxR = 0, numsize = 1;
    for (int i = 0; i < lenclus->nums; i++)
    {
        // printf("parse : %d\n", i);
        int size = lenclus->startIdx[i+1] - lenclus->startIdx[i];
        char **clustrs = (char **)malloc(sizeof(char *) * size);
        for (int j = 0; j < size; j++)
        {
            clustrs[j] = strs[lenclus->cluIDx[lenclus->startIdx[i] + j]];
        }
        CENCLU *cenclu = CenCluster(clustrs, size, sim);
        // printf(" over\n");
        for (int j = 0; j < cenclu->num; j++)
        {
            if (idxR >= (numsize * SIZE))
                records = (int *)realloc(records, sizeof(int) * SIZE * (++numsize));
            records[idxR++] = count;
            for (int k = 0; k < cenclu->numclusters[j]; k++)
            {
                residx[count++] = lenclus->cluIDx[lenclus->startIdx[i] + cenclu->clusters[j][k]];
            }
        }
        free(clustrs);
        freeCENCLU(cenclu);
    }
    freeLENCLU(lenclus);
    records = (int *)realloc(records, sizeof(int) * (idxR + 1));
    records[idxR] = count;
    lenclus = (LENCLU *)malloc(sizeof(LENCLU));
    lenclus->cluIDx = residx;
    lenclus->startIdx = records;
    lenclus->numc = num;
    lenclus->nums = idxR;
    return lenclus;
}


void freeLENCLU(LENCLU *lenclu)
{
    free(lenclu->cluIDx);
    free(lenclu->startIdx);
    free(lenclu);
}