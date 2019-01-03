/*
*
*lab6
*
*Created by Indra Bhurtel on 12/4/18.
*
*
*Name:Indra Bhurtel
*I am senior at UTA. My major is software Engineering.
*UTA ID NO:1001542825
*
*lab 6 assignment
*
*
*
*
*Professor Bob Weems
*
*Code compilation in Omega as follows:
*Make sure you make a.dat /b.dat / c.dat sample run from the sample run given by the professor.
*The input will be read as a shell redirect (<) from a file.
*    gcc lab6.c -lm
*   ./a.out <a.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numVertices,numEdges;
int *parent,numTrees;
double *weight;

struct edge
{
    int tail,head;
    double weight;
};
struct coordinate
{
    int x,y;
};
typedef struct coordinate coordinate_Type;
coordinate_Type *point;

typedef struct edge edgeType;
edgeType *edgeTab;

int find(int x)
// Find root of tree containing x
{
    int i,j,root;

// Find root
    for (i=x;
            parent[i]!=i;
            i=parent[i])
        ;
    root=i;
// path compression - make all nodes on path
// point directly at the root
    for (i=x;
            parent[i]!=i;
            j=parent[i],parent[i]=root,i=j)
        ;
    return root;
}

void unionFunc(int i,int j)
// i and j must be roots!
{
    if (weight[i]>weight[j])
    {
        parent[j]=i;
        weight[i]+=weight[j];
    }
    else
    {
        parent[i]=j;
        weight[j]+=weight[i];
    }
    numTrees--;
}

int weightAscending(const void* xin, const void* yin)
// Used in call to qsort()
{
    edgeType *x,*y;

    x=(edgeType*) xin;
    y=(edgeType*) yin;

    double c = x->weight - y->weight;
    if (c == 0)
    {
        return 0;
    }
    if (c > 0)
    {
        return 1;
    }
    if (c < 0)
    {
        return -1;
    }


}

int main()
{
    int i,j;
    double MSTweight=0;
    int root1,root2;

    scanf("%d",&numVertices);
    numEdges=(numVertices*(numVertices-1))/2;
    edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
    point=(coordinate_Type*) malloc(numVertices*sizeof(coordinate_Type));
    parent=(int*) malloc(numVertices*sizeof(int));
    weight=(double*) malloc(numVertices*sizeof(double));
    if (!edgeTab ||!point|| !parent || !weight)
    {
        printf("error 2\n");
        exit(0);
    }
    for (i=0; i<numVertices; i++)
        scanf("%d %d",&point[i].x,&point[i].y);

    for (i=0; i<numVertices; i++)
    {
        parent[i]=i;
        weight[i]=1;
    }
    int k=0;
    for(i=0; i<numVertices; i++)
    {
        printf("%d %d %d \n",i,point[i].x,point[i].y);
    }
    for(i=0; i<numVertices-1; i++)
    {
        for(j=i+1; j<numVertices; j++)
        {
            double distance=  sqrt(((point[j].x-point[i].x)*(point[j].x-point[i].x))+((point[j].y-point[i].y)*(point[j].y-point[i].y)));
            edgeTab[k].weight=distance;
            edgeTab[k].tail=i;
            edgeTab[k].head=j;
            k++;
        }
    }
    qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);
    for (i=0; i<numEdges; i++)
    {
        root1=find(edgeTab[i].tail);
        root2=find(edgeTab[i].head);
        if (root1==root2)
            printf("%d %d \t%.3f discarded\n",edgeTab[i].tail,edgeTab[i].head,
                   edgeTab[i].weight);
        else
        {
            printf("%d %d \t%.3f included\n",edgeTab[i].tail,edgeTab[i].head,
                   edgeTab[i].weight);
            MSTweight+=edgeTab[i].weight;
            unionFunc(root1,root2);
        }
    }
    printf("Sum of weights of spanning edges %.3f\n",MSTweight);// Prints the sum of weight
    //Free all the memory
    free(edgeTab);
    free(point);
    free(parent);
    free(weight);
}
