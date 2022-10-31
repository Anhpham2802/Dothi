#include<stdio.h>
#include"queue.h"
#include<string.h>
#define MAX 6000
#define MAXC 100000

typedef struct
{
    char word[10];
} Eltype;
void docfile(char *filename, Eltype element[], int *n)
{
    FILE *f;
    f = fopen(filename,"r");
    if(f == NULL)
    {
        printf("Khong the mo file !! \n");
        return;
    }
    int i=0;
    while( !feof(f) )
    {   
        i++;
        fscanf(f, "%s" , element[i].word);
        
    }
    *n = i;
    fclose(f);

}
int KTcanh(char v1[], char v2[])
{
    int i;
    int dem=0;
    for( i=0 ; i<strlen(v1) ; i++)
    {
        if(v1[i] == v2[i])             
            dem++;
    }
    if(dem == 4)
	{
		return 1;
	}
	return 0;
}
void explore(Eltype element[], int u, int d[], int n)
{
    d[u] = 0;
    AddTail(u);
    while(headd != NULL)
    {
        int v = Delhead();
        int i;
        for(i = 1 ; i<=n ; i++)
            {
                if(d[i] == -1 && KTcanh(element[i].word , element[v].word))
                    {
                        AddTail(i);
                        d[i] = d[v]+1;
                    }
            }
    }
}
int BFS(Eltype element[],int n,int d[])    
{
    int a=0;
    int i;
    for( i=1 ; i<=n ; i++)
        d[i] = -1;
    
    for( i=1 ; i<=n ; i++)
    {
        if(d[i] == -1)
            {
                a++;
                explore(element,i,d,n);
            }
    }
    return a;

}
void PATH(Eltype element[],int n,int d[])
{
    char u[10],v[10];
    printf("Tu xuat phat: ");
    gets(u);
    printf("\nTu ket thuc: ");
    gets(v);
    
    int u1,v1;
    int i;
    int temp =0;
    for( i=1 ; i<=n ; i++)
        {
            if(strcmp(u , element[i].word) == 0)
                {
                    u1 = i;
                    break;
                }
        }
        for( i=1 ; i<=n ; i++)
        {
            if(strcmp(v, element[i].word) == 0)
                {
                    v1 = i;
                    break;
                }
        }
        for( i=1 ; i<=n ; i++)
            d[i] = -1;
        d[u1] = 0;
        AddTail(u1);
        while(headd != NULL)
        {
            int s=Delhead();
            for( i=1 ; i<=n ; i++)
                if(d[i] == -1 && KTcanh(element[s].word , element[i].word))
                {
                    AddTail(i);
                    d[i] = d[s] + 1;
                    if(strcmp(element[i].word , v) == 0)
                    {
                        headd = NULL;
                    }
                }
        }
        AddTail(v1);
        for( i=1 ; i<=n ; i++)
        {
            if(d[v1]-d[i] == 1 && KTcanh(element[v1].word , element[i].word))
            {
                AddTail(i);
                v1 = i;
                if(d[i] == 0 )
                    break;
                i=0;
            }
        }
        printf("\n");
        while(headd != NULL)
        {
            i = Delhead();
            printf("-> %s " , element[i].word);
        }
}
int main()
{
    int d[MAX];
    Eltype element[MAX];
    int n;
    docfile("tu.txt", element , &n);
    printf("So tu: %d\n",n);
    int p = BFS(element,n,d);
    printf("So thanh phan lien thong: ");
    printf("%d\n",p);
    PATH(element,n,d);
    return 0;
}