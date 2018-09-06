#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define run 30
#define maxIteration 50

double countDistance(double point[],double center[]);
double countsingleDistance(double point,double center);
void group(double pointToCenterDistance[],double dataSet[],int k,int row);

int main()
{
    int countRun = 1;
    double runBest = 0;
    while(countRun <= run)
    {
	    FILE *fptr;
		char x1[3]={},x2[3]={},x3[3]={},x4[3]={},x5[3]={},empty[]="EOF";
		double dataSet[150][5] = {0},read[150][5] = {0},accuracy;
		int i,j,h,count = 0,row = 4,column = 0,k = 3,co = 1,tr = 0;
		
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
		//initial rand k 
		int r[k] = {0};
		double centerData[k][row] = {0},pointToCenterDistance[column][k] = {0};
		
		srand(time(NULL));
		for(i=0;i<k;i++)
			r[i] = rand()%column;
		//sample r
		for(i=0;i<k;i++)
			for(j=i+1;j<k;j++)
				if(r[i] == r[j])
					r[j] = r[i] + 1;
		for(i=0;i<k;i++)
			for(j=0;j<row;j++)
				centerData[i][j] = dataSet[r[i]][j];
		
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
			//grouping
			for(i=0;i<column;i++)
				group(pointToCenterDistance[i],dataSet[i],k,row);
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
			//SSE count point to center distance						
			double total = 0;
			for(i=0;i<column;i++)
				for(h=0;h<k;h++)						
					pointToCenterDistance[i][h] = countDistance(dataSet[i],centerData[h]);
			//count every group sum
			for(h=1;h<=k;h++)
				for(i=0;i<column;i++)
					if(dataSet[i][row] == h)
						for(j=0;j<row;j++)
							total += countsingleDistance(dataSet[i][j],centerData[h-1][j]);		
			co++;
			printf("SSE = %f\n",total);
		}		
//		printf("\n");
//		for(i=0;i<column;i++)		
//			printf("%f   %f\n",dataSet[i][row],read[i][row]);		
		countRun++;
		printf("\n");
	}	
}

double countDistance(double point[],double center[])
{
	int i;
	double toCountDistance = 0;
	for(i=0;i<4;i++)
		toCountDistance += sqrt(pow((point[i] - center[i]),2));
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
