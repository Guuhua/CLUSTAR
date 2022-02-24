#include "CenCluster.h"
#include "cstarAlign.h"
#include "PSA_fmindex.h"
#include "dist.h"


int getLongest(int *Lens, int numL)
{
    int idx = 0;
    for (int i = 1; i < numL; i++)
    {
        idx = Lens[i] > Lens[idx] ? i : idx;
    }
    return idx;
}

int *pickKids(float *sims, int idxc, int numL, float sim, int *numK)
{
    (*numK) = 0;
    for (int i = 0; i < numL; i++)
    {
        if (sims[i] >= sim)
        {
            (*numK)++;
        }
    }
    int *res = (int *)malloc(sizeof(int) * (*numK));
    res[0] = idxc;
    if ((*numK) == 1)
    {
        free(sims);
        return res;
    }
    for (int i = 0, j = 1; i < numL; i++)
    {
        if (sims[i] >= sim && i != idxc)
        {
            res[j++] = i;
        }
    }

    free(sims);
    return res;
}

int *delOutliers(char **strs, int *simOnes, int *idxMap, int *numK, float sim)
{
    // if ((*numK) >= 1)
    // {   
    for (int i = 0; i < (*numK); i++)
    {
        int temp = simOnes[i];
        simOnes[i] = idxMap[temp];
        idxMap[temp] = -1;
        // printf("%d,", simOnes[i]);
    }
    // printf("\n");
    return simOnes;
    // }
    // FM *fmA = FMbulid(strs[simOnes[0]]);
    // float *scores = (float *)malloc(sizeof(float) * (*numK));
    // float ave = 0;
    // for (int i = 1; i < (*numK); i++)
    // {
    //     char **tempstrs = AlignStr(fmA, strs[simOnes[0]], strs[idxMap[simOnes[i]]]);
    //     scores[i] = compare(tempstrs[0], tempstrs[1]);
    //     ave += scores[i];
    //     free(tempstrs[0]);
    //     free(tempstrs[1]);
    //     free(tempstrs);
    // }
    // ave /= ((*numK)-1);
    // freeFM(fmA);

    // int numD = 0;
    // for (int i = 0; i < (*numK); i++)
    // {
    //     if (scores[i] >= ave || scores[i] >= sim)
    //     {
    //         numD++;
    //     }
    // }
    // if (numD == (*numK))
    // {
    //     for (int i = 0; i < (*numK); i++)
    //     {
    //         simOnes[i] = idxMap[simOnes[i]];
    //         idxMap[simOnes[i]] = -1;
    //     }
    //     free(scores);
    //     return simOnes;
    // }
    // else 
    // {
    //     *numK = numD;
    //     int *simdels = (int *)malloc(sizeof(int) * numD);
    //     for (int i = 0, j = 0; i < (*numK); i++)
    //     {
    //         if (scores[i] >= ave || scores[i] >= sim)
    //         {
    //             simdels[j++] = idxMap[simOnes[i]];
    //             idxMap[simOnes[i]] = -1;
    //         } 
    //     }
    //     free(scores);
    //     free(simOnes);
    //     return simdels;
    // }

}


CENCLU *CenCluster(char **strs, int num, float sim)
{
    // get Len
    int *Lens = (int *)malloc(sizeof(int) * num);
    // change idx --> origin idx
    int *idxMap = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++)
    {
        idxMap[i] = i;
        Lens[i] = strlen(strs[i]);
    }

    char **strsed = starAlign(strs, num);
    int **clusters = (int **)malloc(sizeof(int *) * SIZE), idxCLU = 0, numCLU = 1;
    int *numClusters = (int *)malloc(sizeof(int) * (numCLU * SIZE));

    int numL = num;
    while (numL > 1)
    {
        printf("numL:%d\n", numL);
        int idxc = getLongest(Lens, numL), numK = 0;
        int *simOnes = pickKids(getdist(strsed, idxc, numL), idxc, numL, sim, &numK);
        simOnes = delOutliers(strs, simOnes, idxMap, &numK, sim);

        if (idxCLU >= (numCLU * SIZE))
        {
            clusters = (int **)realloc(clusters, sizeof(int *) * ((++numCLU) * SIZE));
            numClusters = (int *)realloc(numClusters, sizeof(int) * (numCLU * SIZE));
        }

        clusters[idxCLU] = simOnes;
        simOnes = NULL;
        numClusters[idxCLU++] = numK;

        if (numK == numL)
        {
            numL = 0;
            break;
        }

        numL -= numK;
        int *tempLens = (int *)malloc(sizeof(int) * numL);
        int *tempIdxMap = (int *)malloc(sizeof(int) * numL);
        char **tempStrs = (char **)malloc(sizeof(char *) * numL);

        for (int i = 0, j = 0; i < numL+numK; i++)
        {
            if (idxMap[i] != -1)
            {
                tempLens[j] = Lens[i];
                tempIdxMap[j] = idxMap[i];
                tempStrs[j++] = strsed[i];
            }
            else
            {
                free(strsed[i]);
            }
        }
        free(strsed);
        free(Lens);
        free(idxMap);

        strsed = tempStrs;
        Lens = tempLens;
        idxMap = tempIdxMap;
    }
    if (numL == 1)
    {
        if (idxCLU >= (numCLU * SIZE))
        {
            clusters = (int **)realloc(clusters, sizeof(int *) * (idxCLU + 1));
            numClusters = (int *)realloc(numClusters, sizeof(int) * (idxCLU + 1));
        }
        free(strsed[0]);
        free(strsed);
        clusters[idxCLU] = idxMap;
        numClusters[idxCLU++] = 1;
    }
    clusters = (int **)realloc(clusters, sizeof(int *) * idxCLU);
    numClusters = (int *)realloc(numClusters, sizeof(int) * idxCLU);
    CENCLU *res = (CENCLU *)malloc(sizeof(CENCLU));
    res->clusters = clusters;
    res->numclusters = numClusters;
    res->num = idxCLU;
    return res;
}

void freeCENCLU(CENCLU *cenclu)
{
    for (int i = 0; i < cenclu->num; i++)
    {
        free(cenclu->clusters[i]);
    }
    free(cenclu->clusters);
    free(cenclu->numclusters);
    free(cenclu);
}