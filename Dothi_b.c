#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
clock_t Start, End;
#define KT 5757
#define INF 10000;
int **a;
int *stack, *num, *low, *linked;
int index = 0;
int top = -1;
int so = 0;

typedef struct node{
	char string[6];
	bool TThai;
	struct node *next;
} Node;
typedef struct
{
	int vertices;
	Node **Adj;
	Node **Tail;
} WGraph;
WGraph g; 
int LK_ab(char*a, char*b);      
int same(char* a, char *b);
Node *createNode(char *x);
WGraph createWGraph();
void insNode(WGraph *g,int v, Node*tmp);
void insGraph(WGraph *g, Node *tmp);
void DFS(int i);
void docfile(FILE *f, WGraph *g);
int kiemTra(WGraph g);
int MinGraph(WGraph g,int d[]);

int Min (int x, int y)
{
	if ( y<x ) return y;
	else return x;
}
int MinGraph(WGraph g, int d[])
{
	int m,i, min;
	for( i=0 ; i<g.vertices ; i++)
	{
		if( g.Adj[i]->TThai == false)
		{
			min = d[i];
			m = i;
			break;
		}
	}
	for(int j=i+1 ; j<g.vertices ; j++)
	{
		if( g.Adj[j]->TThai == false)
			if( min > d[j])
			{
				min = d[j];
				m = j;
			}
	}
	return m;
}
void docfile(FILE *f, WGraph *g)
{
	f = fopen("tu.txt" , "r");
	while( !feof(f) )
	{
		char x[6];
		fscanf(f , "%s" , x);
		fscanf(f, "\n");
		Node *tmp = createNode(x);
		insGraph(g, tmp);
	}
	fclose(f);
}
void DFS(int v)
{
	low[v] = num[v] = index++;
	top++;
	stack[top] = v;
	linked[v] = true;
	for(int i=0 ; i< g.vertices ; i++)
	{
		if(a[v][i] == 1)
		{
			if(num[i] == -1) DFS(i);
			if(linked[i]) low[v] = Min(low[v], low[i]);
		}
	}
	if(num[v] == low[v])
	{
		so++;
		while(true)
		{
			int u = stack[top];
			top--;
			linked[u] = 0;
			if(v == u) break;
		}
	}
}
int KTra(WGraph g)
{
	for(int i=0 ; i<g.vertices ; i++)
	{
		if( !g.Adj[i]->TThai )
			return i;
	}
	return -1;
}
void insNode(WGraph *g, int vertex, Node*tmp)
{
		g->Tail[vertex]->next = tmp;
		g->Tail[vertex] = tmp;
}
void insGraph(WGraph *g, Node *tmp)
{
	g->Adj[g->vertices] = tmp;
	g->Tail[g->vertices] = tmp;
	
	for(int i=0 ; i<g->vertices ; i++)
	{
		if(LK_ab(g->Adj[i]->string , tmp->string))
		{
			Node *add = createNode(tmp->string);
			insNode(g, i, add);
			a[i][g->vertices] = 1;
		}
		if(LK_ab(tmp->string , g->Adj[i]->string))
		{
			Node* add = createNode(g->Adj[i]->string);
			insNode(g , g->vertices , add);
			a[g->vertices][i] = 1;
		}
	}
	g->vertices++;
}
Node *createNode(char *a)
{
	Node *new = (Node*) malloc(sizeof(Node));
	new->next = NULL;
	new->TThai = false;
	strcpy(new->string,a);
	return new;
}
WGraph createWGraph()
{
	WGraph tu;
	tu.vertices = 0;
	tu.Adj = (Node**) malloc(KT*sizeof(Node*));
	tu.Tail = (Node**) malloc(KT*sizeof(Node*));
	for(int i=0 ; i<KT ; i++)
		{
			tu.Adj[i] = NULL;
			tu.Tail[i] = NULL;
		}
	return tu;
}
int same(char* a,char *b)
{
	if(strlen(a) != strlen(b)) return 0;
	char u,i;
	for(i=0 ; i<strlen(a) ; i++)
	{
		if(a[i] != b[i])
		{
			u = i;
			break;
		}
	}
	for(int j=i+1 ; j<strlen(a) ; j++)
	{
		if(a[j] != b[j]) return 0;
	}
	return 1;
}
int LK_ab(char*a, char*b)
{
	char c[4];
	for(int i=0 ; i<4 ; i++)
	{
		c[i] = a[strlen(a)-1-i];
	}
	int i=0, j=0;
	while(j<4 && i<strlen(b))
	{
		if(b[i] == c[j])
		{
			j++;
			i = 0;
		}
		else i++;
	}
	return j == 4;
}

int main()
{
	FILE *f;
	a = (int**) malloc(KT*sizeof(int*));
 		for(int i=0 ; i<KT ; i++)
			a[i] = (int*) malloc(KT*sizeof(int));
	for(int i=0 ; i<KT-1 ; i++)
	{
		a[i][i] = 0;
		for(int j=i+1 ; j<KT ; j++)
		{
			a[i][j] = a[j][i] = INF;
		}	
	}
	g = createWGraph();
	printf("\nLoading ...");
	docfile(f,&g);
	printf("\nDone!!\n");
	stack = (int*) malloc(g.vertices*sizeof(int));
	num = (int*) malloc(g.vertices*sizeof(int));
	low = (int*) malloc(g.vertices*sizeof(int));
	linked = (int*) malloc(g.vertices*sizeof(int));
	for(int i=0 ; i<g.vertices ; i++)
	{
		num[i] = -1;
		low[i] = -1;
		linked[i] = 0;
	}
	int l;
	do
	{
		for(int i=0 ; i<g.vertices ; i++)
		{
			g.Adj[i]->TThai = false;
		}
		printf("\n----------------------------------------------------"
		"\n1. Dem so thanh phan lien thong manh\n"
		"2. Tim cac tu cung thanh phan lien thong manh\n"
		"3. Tim duong ngan nhat\n"
		"0. Thoat\n----------------------------------------------------");
		printf("\nBan chon: ");
		fflush(stdin);
		scanf("%d", &l);
		switch(l)
		{
			case 1:
				{
					printf("\nLoading ...\n");
					int i;
					for(i=0 ; i<g.vertices ; i++)
					{
						if(num[i] == -1) DFS(i);
					}
					printf("\nSo thanh phan lien manh tinh duoc la :%d\n", so);
					break;					
				}
			case 2:
				{
					char input[6];
					int s = -1;
					printf("\nNhap tu bat dau: ");
					scanf("%s", input);
					for(int i=0 ; i<g.vertices ; i++)
					{
						char chuoi[6];
						strcpy(chuoi, g.Adj[i]->string);
						if(strcmp(input, chuoi) == 0)
						{
							s = i;
							break;
						}
					}
					if( s == -1)
					{
						printf("\nTu nhap vao khong co trong tu dien!");
						break;
					}
					else
					{
						printf("\nLoading ...\n");
						for(int i=0 ; i<g.vertices ; i++)
						{
							if(low[s] == low[i])
								if(strcmp(g.Adj[i]->string , input) != 0)
									printf("%s   ", g.Adj[i]->string);
						}
					}
					break;
				}
			case 3:
				{
					int *d,*v;
					v = (int*) malloc(g.vertices*sizeof(int));
					d = (int*) malloc(g.vertices*sizeof(int));
					for(int i=0 ; i<g.vertices ; i++)
					{
						d[i] = INF;
						v[i] = -1;
					}
					char start[6];
					int x;
					int y;
					char end[6];
					printf("\nNhap tu bat dau: ");
					scanf("%s",start);
					bool check = false;
					for(int i=0 ; i<g.vertices ; i++)
					{
						if(strcmp(start, g.Adj[i]->string) == 0)
						{
							check  = true;
							x = i;
							break;
						}
					}
					if(!check)
					{
						printf("\nTu nhap vao khong co trong tu dien!");
						break;
					}
					check = false;
					printf("\nNhap tu ket thuc: ");
					fflush(stdin);
					scanf("%s",end);
					for(int i=0 ; i<g.vertices ; i++)
					{
						if(strcmp(end, g.Adj[i]->string) == 0)
						{
							y = i;
							check = true;
							break;
						}
					}
					if(!check)
					{
						printf("\nTu nhap vao khong co trong tu dien!");
						break;
					}
					else
						printf("\nLoading ...\n"); 
					d[x] = 0;
					v[y] = x;
					while(KTra(g) != -1)
					{
						int u = MinGraph(g, d);
						g.Adj[u]->TThai = true;
						for(int i=0 ; i<g.vertices ; i++)
						{
							int duong_di = a[u][i];
							int last = d[i];
							d[i] = Min(d[i], d[u]+duong_di);
							if(d[i] != last) v[i] = u;
						}
					}
					if(d[y] == 10000)
					{
						printf("\nKhong tim thay duong di!");
						break;
					}
					int n = y;
					while(n != v[n])
					{
						printf("%s <-- ",g.Adj[n]->string);
						n = v[n];
					}
					printf("%s", g.Adj[n]->string);
					printf("\nKhoang cach: %d",d[y]);
					break;
				}
			case 0:
				{
					exit(0);	
				}
			default: 
				{
					printf("\nKhong hop le!\n");
					break;
				}
		}	
	}
	while(l!=0);
	return 0;
}
