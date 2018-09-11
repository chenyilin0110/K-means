#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define run 1 
#define maxIteration 50

double countDistance(double point[],double center[]);
double countsingleDistance(double point,double center);
void group(double pointToCenterDistance[],double dataSet[],int k,int row);
int permutation(int p);
void swap(int* a, int* b);
void perm(int pData[],int sortData[],int index,int k);
int countPerm = 0;

int main()
{
    int countRun = 1;
    double runBest = 0;
    srand(time(NULL));
    while(countRun <= run)
    {
    	countPerm = 0;
	    FILE *fptr;
		char x1[3]={},x2[3]={},x3[3]={},x4[3]={},x5[3]={},empty[]="EOF";
		double dataSet[150][5] = {0},read[150][5] = {0},accuracy;
		int i,j,h,row = 4,column = 0,k = 3,co = 1,p,bestTrueGroup = 0;
				
		fptr = fopen("K-meansDataSet.txt","r");
		while(fscanf(fptr,"%s %s %s %s %s",&x1,&x2,&x3,&x4,&x5) != EOF)
		{
			if(strcmp(x1,empty) != 0)
			{			
				read[column][0] = dataSet[column][0] = atof(x1);
				read[column][1] = dataSet[column][1] = atof(x2);
				read[column][2] = dataSet[column][2] = atof(x3);
				read[column][3] = dataSet[column][3] = atof(x4);
				read[column][4] = dataSet[column][4] = atof(x5);
				column++;
			}
			else
				break;
		}
		fclose(fptr);				
		
		p = permutation(k);		
//		printf("countRun = %d\n",countRun);		
		//initial rand k 
		int r[k] = {0},sortTempData[column] = {0},sortData[k] = {0},trueGroupData[column] = {0},countTrueGroup[p]={0},pData[p*k]={0},countPerm = 0;
		double centerData[k][row] = {0},pointToCenterDistance[column][k] = {0};		
//		printf("\ncountTrueGroup:\n");
//		for(i=0;i<p;i++)
//				printf("%d ",countTrueGroup[i]);
//		printf("\n");
		//save true group
		for(i=0;i<column;i++)			
			trueGroupData[i] = dataSet[i][row];
		//reset sortData
		for(i=0;i<k;i++)
			sortData[i] = i+1;
		//rand k center		
		for(i=0;i<k;i++)
			r[i] = rand()%column;
		//sample r
		for(i=0;i<k;i++)
		{
			for(j=i+1;j<k;j++)
			{	if(r[i] == r[j])
				{
					if(r[j] < (column-1) )
						r[j] = r[i] + 1;
					else
						r[j] = rand()%column;
				}
			}
		}
//		printf("r:\n");
//		for(i=0;i<k;i++)
//			printf("%d  ",r[i]);
//		printf("\n");
		for(i=0;i<k;i++)
			for(j=0;j<row;j++)
				centerData[i][j] = dataSet[r[i]][j];
//		printf("\ncenterData:\n");
//		for(i=0;i<k;i++)
//		{
//			for(j=0;j<row;j++)
//				printf("%f  ",centerData[i][j]);
//			printf("\n");
//		}
		while(co <= maxIteration)
		{
			double x[k][row] = {0};
			int countx[k] = {0};		
			//clear x[][]
			for(h=0;h<k;h++)
				for(j=0;j<row;j++)
					x[h][j] = 0;			
			//count point to center distance			
			for(i=0;i<column;i++)
				for(h=0;h<k;h++)						
					pointToCenterDistance[i][h] = countDistance(dataSet[i],centerData[h]);
//			printf("\npointToCenterDistance:\n");
//			for(i=0;i<column;i++)
//			{
//				for(h=0;h<k;h++)
//						printf("%f  ",pointToCenterDistance[i][h]);
//				printf("\n");
//			}
			//grouping
			for(i=0;i<column;i++)
				group(pointToCenterDistance[i],dataSet[i],k,row);
//			printf("\ngroup:\n");
//			for(i=0;i<column;i++)
//			{
//				for(h=0;h<=row;h++)
//						printf("%f  ",dataSet[i][h]);
//				printf("\n");
//			}
			//count every group
			for(h=1;h<=k;h++)
			{
				for(i=0;i<column;i++)
				{
					if(dataSet[i][row] == h)
					{
						for(j=0;j<row;j++)
							x[h-1][j] += dataSet[i][j];
						countx[h-1]++;
					}				
				}			
			}
			//count every avg(group)
			for(h=0;h<k;h++)
				for(j=0;j<row;j++)
					x[h][j] = x[h][j] / countx[h];
			//copy new center 
			for(i=0;i<k;i++)
				for(j=0;j<row;j++)
					centerData[i][j] = x[i][j];
//			printf("\ncenterData:\n");
//			for(i=0;i<k;i++)
//			{
//				for(j=0;j<row;j++)
//					printf("%f  ",centerData[i][j]);
//				printf("\n");
//			}
			//SSE count every group sum
			double total = 0;			
			for(h=1;h<=k;h++)
			{
//				printf("h = %d\n",h);
				for(i=0;i<column;i++)
				{
					if(dataSet[i][row] == h)
					{
						for(j=0;j<row;j++)
						{
//							printf("dataSet[%d][%d] = %f\n",i,j,dataSet[i][j]);
//							printf("centerData[%d][%d] = %f\n",h-1,j,centerData[h-1][j]);
							total += countsingleDistance(dataSet[i][j],centerData[h-1][j]);
						}
					}
				}
//				printf("total = %f\n\n",total);
			}						
			co++;
			printf("SSE = %f\n",total);			
//			printf("---------------------------------------------\n");			
		}		
		countRun++;
//		printf("\n");
		//taken out the dataSet group
		perm(pData,sortData,0,k);
		
		for(int q=0;q<p;q++)
		{	
			int count=0;
			for(i=0;i<column;i++)
				sortTempData[i] = dataSet[i][row];
//			printf("\nsortTempData:\n");
//			for(i=0;i<column;i++)
//				printf("%d\n",sortTempData[i]);
			for(h=q*3;h<(q+1)*3;h++)
			{				
				sortData[count] = pData[h];
				count++;
			}
//			printf("\nsortData:\n");
//			for(i=0;i<k;i++)
//				printf("%d",sortData[i]);
//			printf("\nHHHHHHHHHHHHHHHHHHHHHHHH:\n");
			for(i=0;i<column;i++)
	    	{
				for(j=0;j<k;j++)
				{
					if(sortTempData[i] == sortData[j])
					{			
						sortTempData[i] = j+1;					
						break;
					}
				}				
			}			
//			printf("\nnewSortTempData:\n");
//			for(i=0;i<column;i++)
//				printf("%d\n",sortTempData[i]);
//			printf("\ntrueGroupData:\n");
//			for(i=0;i<column;i++)
//				printf("%d\n",trueGroupData[i]);			
			for(i=0;i<column;i++)
	    	{
	    		if(trueGroupData[i] == sortTempData[i])
				{
//					printf("\ntrueGroupData[%d] = %d\n",i,sortTempData[i]);
//					printf("sortTempData[%d] = %d\n",i,sortTempData[i]);					
					countTrueGroup[q]++;
				}
			}
//			printf("\ncountTrueGroup:\n");
//			for(i=0;i<=q;i++)
//				printf("%d ",countTrueGroup[i]);
//			printf("\n");
			if(bestTrueGroup < countTrueGroup[q])
				bestTrueGroup = countTrueGroup[q];			
		}
		printf("bestTrueGroup = %d\n",bestTrueGroup);
		double percentage;
		percentage = ((double)bestTrueGroup/(double)column)*100.0;
		printf("percentage = %f\n",percentage);					
	}
}

double countDistance(double point[],double center[])
{
	int i;
	double toCountDistance = 0;
	for(i=0;i<4;i++)
		toCountDistance += pow((point[i] - center[i]),2);
	toCountDistance = sqrt(toCountDistance);
	return toCountDistance;
}

double countsingleDistance(double point,double center)
{
	int i;
	double toCountsingleDistance = 0;
	toCountsingleDistance = pow((point - center),2);
	return toCountsingleDistance;
}

void group(double pointToCenterDistance[],double dataSet[],int k,int row)
{
	double best = 99999999;
	int j;
	for(j=0;j<k;j++)
	{
		if(best > pointToCenterDistance[j])
		{
			dataSet[row] = (j+1);
			best = pointToCenterDistance[j];
		}
	}
}

int permutation(int p)
{	
	if(p == 1)
		return 1;
	else
		return permutation(p-1)*p;
}

void perm(int pData[],int sortData[],int index,int k)
{
	int i = 0,j = 0;

    if(index == k)    
    {
    	for(i=0;i<k;i++)
    	{
			pData[countPerm] = sortData[i];
			countPerm++;			
		}
	}
    else
    {
        for(j=index;j<k;j++)
        {
            swap(&sortData[j],&sortData[index]);
            perm(pData,sortData,index+1,k);
            swap(&sortData[j],&sortData[index]);
        }
    }
}

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

