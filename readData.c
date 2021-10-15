/*******************************************************
*readData.c
*
* read data from text file and store it to variable
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"add.h"
#include"abstractNetwork2.h"
PROJECT_T * project = NULL;
int vertexCount = 0;

PROJECT_T * sendProject()
{
  return project;
}

void freeData()
{
  PROJECT_T * del = project;
  free(del);
  del = NULL;
}
/*
 * Function that add vertex for
 */
void goAddVertex(char * key,char * data,int vertexEstimate)
{
	int bOk = addVertex(key,data,vertexEstimate);
	if(bOk == 1)
	{
		vertexCount++;
	}
	else
	{
		printf("vertex error\n");
		exit(0);
	}
}

/*
 * Function that read data and store it to variable
 * if longest = 1 -> multiply -1 to estimate time
 * else do nothing
 */
int ReadDataTxt(char filename[],int longest)
{
  FILE * pIn = NULL;	/*pointer use to open file*/
  char task[128];			/*stored task*/
  char input[128];		/*stored line*/
  char key[128];			/*stored task code*/
  char description[128];	/*stored task description*/
	char key1[128];					/*First task code*/
	char key2[128];					/*second task code*/
	char edge[128];					/*stored 'edge'*/
	int duration = 0;				/*stored duration of dependency*/
  int estimate = 0;				/*stored estimatie time of task*/
  
  pIn = fopen(filename,"r");
  if(pIn == NULL)
  {
    printf("file %s\n",filename);
    printf("cannot open file\n");
    exit(0);
  }
	project = (PROJECT_T*) calloc(1,sizeof(PROJECT_T));
  if(project == NULL)
  {
    printf("allocate error\n");
    exit(0);
  }
  memset(input,0,sizeof(input));
  fgets(input,sizeof(input),pIn);
  sscanf(input,"%s",project->name);
  fgets(input,sizeof(input),pIn);
  sscanf(input,"%s",project->description);
  fgets(input,sizeof(input),pIn);
  sscanf(input,"%s",project->startDate);
  memset(input,0,sizeof(input));
  while(fgets(input,sizeof(input),pIn) != NULL)
  {
    if(strncmp(input,"TASK",4) == 0)
    {
      sscanf(input,"%s %s %s %d",task,key,description,&estimate);
			if(longest == 1)
      {
				estimate = estimate*-1;
			}
			goAddVertex(key,description,estimate);
    }
		else if(strncmp(input,"EDGE",4) == 0)
		{
			sscanf(input,"%s %s %s %d",edge,key1,key2,&duration);
			int retval = addEdge(key1,key2);
			if(retval == 1)
			{
				keepEdge(key1,key2,retval);
			}
			else
			{
				printf("edge error\n");
			}
		}
    else
    {
      memset(input,0,sizeof(input));
      continue;
    }
    memset(input,0,sizeof(input));
  }
fclose(pIn);
}
#ifdef DEBUG4
int main()
{
  char filename[128];
  char input[128];
  printf("filename ");
  fgets(input,sizeof(input),stdin);
  sscanf(input,"%s",filename);
  ReadDataTxt(filename,0);
}
#endif
