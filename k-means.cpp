#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define run 30
#define maxIteration 50

double countDistance(double point[],double center[]);

int main()
{
    FILE *fptr;
    char x1[3]={},x2[3]={},x3[3]={},x4[3]={},x5[3]={},empty[]="EOF";
	double dataSet[150][5] = {0},read[150][5] = {0};
	int i,j,h,count = 0,column = 0,k = 3;
	
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
	double rData[k][5] = {0},pointToCenterDistance[column][k] = {0};
	
	srand(time(NULL));	
	for(i=0;i<k;i++)
		r[i] = rand()%column;
	//sample r
	for(i=0;i<k;i++)
		for(j=i+1;j<k;j++)
			if(r[i] == r[j])
				r[j] = r[i] + 1;	
				
	printf("r = ");
	for(i=0;i<k;i++)
		printf("%d ",r[i]);
	printf("\n");
	
	for(i=0;i<k;i++)
		for(j=0;j<4;j++)
			rData[i][j] = dataSet[r[i]][j];
	for(i=0;i<k;i++)
	{
		for(j=0;j<4;j++)
			printf("%f ",rData[i][j]);
		printf("\n");
	}
//	for(i=0;i<column;i++)
//	{
//		printf("i = %d ",i);
//		for(h=0;h<5;h++)
//		{
//			printf("%f ",dataSet[i][h]);
//		}
//		printf("\n");
//	}

	//count point to center distance			
	for(i=0;i<column;i++)
		for(h=0;h<k;h++)		
			for(j=0;j<4;j++)
				pointToCenterDistance[i][h] = countDistance(dataSet[i],rData[h]);
	
	
	printf("\n\n\n");
	for(i=0;i<column;i++)
	{
		for(h=0;h<k;h++)		
		{
			printf("%f ",pointToCenterDistance[i][h]);
		}
		printf("\n");
	}

	return 0;
}

double countDistance(double point[],double center[])
{
	int i;
	double toCountDistance = 0;
	for(i=0;i<4;i++)
		toCountDistance += pow((point[i] - center[i]),2);
	return toCountDistance;
}
