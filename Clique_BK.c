#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
/*
 * jiawei4@staff.sina.com.cn
 * 1. 要求输入的三元组文件为按照第一个关键字排序
 * 2. 参考： http://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 * */
#define LINE 2500   // 列2的UID数目
#define SHARE 1000  // 列1与列2 共享的互粉数目
#define NUM (LINE*SHARE)

int LEN[LINE]={0};
int Count=0;
int64_t USER;// 主角

typedef struct Index
{
	int64_t uid;
	int64_t index;
	int32_t count;
}Index;

void CreateRela(int64_t Key[],Index uid_info[], int64_t con1, int64_t con2)
{
		
}

void AddNode(int64_t * A, int64_t value)
{
	int i = 0;
	while(A[i] != value && A[i] !=0)
	{
		++i;
	}
	A[i] = value;
}

void Insect(int64_t *A, int64_t *B, int64_t *C)
{
	int i =0,j,k;
	for(j=0 ; A[j] !=0 ; ++j)
		for(k=0 ; B[k] != 0 ;++k)
		{
			if(A[j] == B[k]) C[i++] = A[j];
		}
}

void DelNode(int64_t *A, int64_t value)
{
	int i = 0,j=0;
	while(A[j] !=0)
	{
		if(A[j] != value)
		{
			A[i++]=A[j];
		}
		++j;
	}
	A[i] = 0;
}

void CopyArray(int64_t *From, int64_t *To)
{
	int i=0,j=0;
	while(0 !=From[i])
	{
		To[j++] = From[i++];
	}
}
void Tra(int64_t *T)
{
	int i = 0;
	printf("Tra:\n");
	while(T[i] != 0)
	{
		printf("%lld\t",T[i]);
		++i;
	}
	printf("\n");
}
int Find(int64_t *Graph, int64_t key)
{
	int len = Count-1;	
	int i;
	for( i = 0 ; i < Count; ++i)
	{
		if(Graph[i*SHARE] == key)
		{
			return i;
		}
	}

	while( len >= 0 && Graph[len*SHARE +0] >key)
	{
		for( i = 0 ; i < LEN[len]; ++i)
		{
			Graph[(len+1)*SHARE +i]	= Graph[len*SHARE +i];
			 Graph[len*SHARE +i] = 0;
		}
		LEN[len+1]=LEN[len];
		--len;
	}
		Graph[(len+1)*SHARE + 0] = key; // 不存在则插入	
		LEN[len+1] = 1;
		++Count;
		return len+1;
}

void BK(int64_t *Graph, int64_t *R, int64_t *P, int64_t *X )
{
	if(0 == P[0] && 0 == X[0])
	{
//		printf("get clique:\n");
		int j ;
		printf("%lld:",USER);
		for(j=0;R[j] !=0 ; ++j)
		{
			printf("%lld\t",R[j]);
		}
		printf("\n");
	}
	else if(0==P[0]) 
	{
	}
	else
	{
	int i=0;
	int64_t  P_copy[LINE]={0};
	CopyArray(P,P_copy);
	while(P[i] != 0)
	{
		int64_t R_1[LINE]={0}, P_1[LINE]={0}, X_1[LINE] = {0};
		CopyArray(R,R_1);
		AddNode(R_1,P[i]);
		int pos=Find(Graph,P[i]);
		Insect(P_copy,Graph+pos*SHARE+1,P_1);
		Insect(X,Graph+pos*SHARE+1,X_1);
		BK(Graph,R_1,P_1,X_1);
		DelNode(P_copy,P[i]);
		AddNode(X,P[i]);
		++i;
	}
	}
}

void BK_algo(int64_t Graph[])
{
	//printf("BK_algo\n");
	if(NULL == Graph )	
	{
		printf("graph is null\n");
		return ;
	}
	int64_t R[LINE]={0},P[LINE] = {0},X[LINE] = {0};
	int i ;
	for(i = 0 ; i < Count ; ++ i)
	{
		P[i] = Graph[i*SHARE + 0];
//		printf("lld:%lld\t",P[i]);
	}
	BK(Graph,R,P,X);
}


void InsertEdge(int64_t *Graph, int64_t key, int64_t value)
{
///	printf("InsertEdge\n");
	int pos1 = Find(Graph, key);
//	printf("key:%d\tpos:%d\n",key,pos1);
	Graph[pos1*SHARE + LEN[pos1]] = value;
	LEN[pos1]++;
}
void Traverse(int64_t *Graph)
{
	printf("Traverse\n");
	int i,j;
	for(i=0;i<Count;++i)
	{
		//for(j=0;j<LEN[i];++j)
		for(j=0;Graph[i*SHARE+j] !=0;++j)
		{
			printf("Graph-key:%lld\t",Graph[i*SHARE+j]);
		}
		printf("\n");
	}
}

void ReadTri(char *infile)
{
	FILE *fp;
	if((fp=fopen(infile,"r"))==NULL)
	{
		//文本只读方式重新打开文件
		printf("cannot open file:%s\n",infile);
		return ;
	}
	int64_t key,node1,node2, pre=-1;
	int pos = 0,count = 0, flag = -1;
	int64_t *Graph = (int64_t *)malloc(sizeof(int64_t)*NUM);
	memset(Graph,0,sizeof(int64_t)*NUM);
	while(fscanf(fp,"%lld%lld%lld",&key,&node1,&node2) != EOF)
	{
//		printf("%lld,%lld,%lld,%lld\n",key,node1,node2,pre);	
		if(key == pre|| -1==pre)
		{
			InsertEdge(Graph, node1,node2);
			InsertEdge(Graph, node2,node1);
			pre = key;
			USER = pre;
		}
		else
		{
		//	Traverse(Graph);
			BK_algo(Graph);			
			Count = 0;
			int i;
			for(i=0;i<LINE;++i)LEN[i]=0;
			for(i=0;i<NUM;++i)Graph[i]=0;
			pre = key;
			InsertEdge(Graph, node1,node2);
			InsertEdge(Graph, node2,node1);
		}
	}
//	Traverse(Graph);
	if(-1 != pre)
		BK_algo(Graph);			
}

int main(int argc, char* argv[])
{
	if(argc <2)
	{
		printf("need: exe,inputfile\n");	
	}
	ReadTri(argv[1]);
	return 0;
}
