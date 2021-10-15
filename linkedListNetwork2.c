/**
 *  linkedListNetwork.c
 *
 *  Implements an abstractNetwork using adjacency lists (linked lists).
 *  This is a structure with two levels of list. There is a master
 *  list of vertices, linked in series. Each vertex points to a subsidiary
 *  linked list with references to all the other vertices to which it
 *  is connected.
 *
 *  Each vertex has an integer weight and a pointer to a parent vertex
 *  which can be used for route finding and spanning tree algorithms
 *
 *  Key values are strings and are copied when vertices are inserted into
 *  the graph. Every vertex has a void* pointer to ancillary data which
 *  is simply stored.
 *
 *  Created by Sally Goldin, 1 February 2012 for CPE 113
 *  Modified 18 March 2013 to improve naming.
 *  Modified 20 April 2018 to use JavaDoc keywords in comments
 *  Modified with permission by Jatnipat on 15 April 2020
 *
 *  Added a new structure for edge and function to store an edge in
 *  queue ,also add function printtask plus the function to check for loop
 *  of and dependency. Last two function to print task and edge to file project
 * * edit by DOON 02-05-2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractNetwork2.h"
#include "abstractQueue.h"
#include "abstractStack.h"
#define WHITE 0
#define GRAY  1
#define BLACK 2
#define HUGEVALUE 99999

char* colorName[] = {"WHITE", "GRAY", "BLACK"};

VERTEX_T * vListHead = NULL;  /* head of the vertex list */
VERTEX_T * vListTail = NULL;  /* tail of the vertex list */

VERTEX_T * vListHeadTopo = NULL; /* head of the vertex list after topological sorting */
VERTEX_T * vListTailTopo = NULL; /* tail of the vertex list after topological sorting */

EDGE_T * eHead = NULL;	/* head of edges list */
EDGE_T * eTail = NULL;	/* tail of edges list */

VERTEX_T * vertices = NULL; /* vertex of longest path */

DEPRO_T * dHead = NULL;
DEPRO_T * dTail = NULL;

VERTEX_T * listHead()
{
	return vListHead;
}

VERTEX_T * listTopo()
{
	return vListHeadTopo;
}

/*
 * Function to check amount of task
 */
int checkTask ()
	{
	int check = 0;
	VERTEX_T * current = vListHead;
	while (current != NULL)
		{
		check++;
		current = current->next;
		}
	return check;
	}

/*
 * Function to add edge into a queue (end of the list)
 */
void forEdge (char * keystring1, char * keystring2, int weight)
	{
	EDGE_T * pNewE = (EDGE_T *) calloc(1,sizeof(EDGE_T));
  char * key1 = NULL;
  char * key2 = NULL;
  key1 = strdup(keystring1);
  key2 = strdup(keystring2);
  if ((pNewE == NULL) || (key1 == NULL) || (key2 == NULL))
    {
    printf("Error exit!\n");
    exit(10);
    }
	pNewE->key1 = key1;
	pNewE->key2 = key2;
	pNewE->weight = weight;
  	if (eHead == NULL)  /* first vertex */
 		{
     	eHead = pNewE;
     	}
  	else
     	{
     	eTail->next = pNewE;
     	}
  	eTail = pNewE;
	}

/* Function to add project into a queue */
void namePro (char * name)
	{
	DEPRO_T * pNew = (DEPRO_T *) calloc(1,sizeof(DEPRO_T));
	pNew->name = name;
  	if (dHead == NULL)  /* first vertex */
		{
     	dHead = pNew;
     	}
  	else
 		{
 		dTail->next = pNew;
     	}
  	dTail = pNew;
	}

/* Function to print name of the project */
void printName (FILE * pName)
	{
	DEPRO_T * dCurrent = dHead;
	while (dCurrent != NULL)
		{
		fprintf(pName,"%s\n",dCurrent->name);
		free(dCurrent);
		dCurrent = dCurrent->next;
		}
	dHead = NULL;
	dTail = NULL;
	}



/* traverse to re-order the vertex
* in topological sorting
*/
int toposort()
{
	VERTEX_T* pVertex = vListHead;
   if (pVertex == NULL)
      {
      printf("The graph is empty\n");
      }
   else
      {
      colorAll(WHITE);
      while (pVertex != NULL)
      {
	 if (pVertex->color == WHITE)
	    {
	    pVertex->color = GRAY;
            traverseDepthFirst(pVertex,&stackTopo);
	    }
         pVertex = pVertex->next;
	 }
      }
      while(stackSize() > 0)
      {
      	VERTEX_T * pCurrent = pop();
      	orderTopo(pCurrent);
      }
}

/* find the longest path
* using shortest path algorithm but
* the weight is negative
* so the leastest path is the longest path
* when we multiple it by -1
*/
int printLongestPath()
{
   VERTEX_T * currentVtx = NULL; /* pointer to hold dequeued vertices */
   int i;
   int currentIndex;
   int weight;
   queueClear();
   colorAll(WHITE);
   VERTEX_T * pCurrent = vListHeadTopo;
   while(pCurrent != NULL)
   {
   		if(strcmp(pCurrent->key,"start") == 0)
   		{
   			pCurrent->dValue = 0;
   			enqueue(pCurrent);
   			pCurrent=pCurrent->next;
   			continue;
   		}
   		pCurrent->dValue = HUGEVALUE;
   		enqueue(pCurrent);
   		pCurrent=pCurrent->next;
   }
    currentVtx = dequeue();
    while(currentVtx != NULL)
    {
      	currentVtx->color = BLACK;
      	ADJACENT_T * pRef = currentVtx->adjacentHead;
       while(pRef != NULL)
       {
       		weight = pRef->duration;
       		vertices = (VERTEX_T*) pRef->pVertex;
       	if(vertices->color == WHITE && (currentVtx->dValue + weight)<(vertices->dValue))
       	{
       		vertices->dValue = currentVtx->dValue + weight;
       		vertices->parent = currentVtx;
       	}
       	pRef = pRef->next;
       }
    currentVtx = dequeue();
    }
    char * end = "end";
    VERTEX_T * dummy;
    vertices = findVertexByKey(end,&dummy);
    return vertices->dValue*-1;
}

/* connect the vertex that has no
* out-dependency to END
* and connect each that has no
* incoming-dependency to Start*/
int startEnd()
{
	VERTEX_T * pCurrent = vListHead;
	VERTEX_T * pCurrent2 = vListHead;
	char * start = "start";
	char * end = "end";
	int retval = 0;
	int incomeEdgeCount = 0;
	while(pCurrent != NULL)
	{
		if(pCurrent->adjacentHead == NULL && (strcmp(pCurrent->key,start) != 0
			&& strcmp(pCurrent->key,end) != 0))
		{
			retval = addEdge(pCurrent->key,end);
			if(retval == 1)
			{
				keepEdge(pCurrent->key,end,retval);
			}
			else
			{
				printf("edge error\n");
			}

		}
		pCurrent = pCurrent->next;
	}
	while(pCurrent2 != NULL)
	{
		incomeEdgeCount = 0;
		EDGE_T * pEdge = eHead;
		while(pEdge != NULL)
		{
			if(strcmp(pEdge->key2,pCurrent2->key) == 0 && (strcmp(pCurrent2->key,start) != 0
			&& strcmp(pCurrent2->key,end) != 0))
			{
				incomeEdgeCount++;
			}
			pEdge = pEdge->next;
		}
		if(incomeEdgeCount == 0 && (strcmp(pCurrent2->key,start) != 0
			&& strcmp(pCurrent2->key,end) != 0))
		{
			retval = addEdge(start,pCurrent2->key);
			if(retval == 1)
			{
				keepEdge(start,pCurrent2->key,retval);
			}
			else
			{
				printf("edge error\n");
			}
		}
		//printf("pass %s\n",pCurrent->key);
		pCurrent2 = pCurrent2->next;
	}
}
/* Execute a depth first search from a single vertex,
 * calling the function (*vFunction) on the lowest level
 * vertex we visit, and coloring it black.
 * Arguments
 *    pVertex    -  starting vertex for traversal
 */
void traverseDepthFirst(VERTEX_T* pVertex, void (*vFunction)(VERTEX_T*))
{
    VERTEX_T * pAdjacent = NULL;
    ADJACENT_T* pRef = pVertex->adjacentHead;
    while (pRef != NULL)
       {
       pAdjacent = (VERTEX_T*) pRef->pVertex;
       if (pAdjacent->color == WHITE)
	   {
	   pAdjacent->color = GRAY;
           traverseDepthFirst(pAdjacent,vFunction);
           }
       pRef = pRef->next;
       } /* end while queue has data */
    /* when we return from the bottom, call the
     * function and color this node black.
     */
    (*vFunction)(pVertex);
    pVertex->color = BLACK;
}

/* stack vertex that has been traversed */
void stackTopo(VERTEX_T * pVertex)
{
	int bOk = push(pVertex);
	if(bOk == 0)
	{
		printf("push error\n");
	}
}

/* keep topological sorted vertex to pointer */
void orderTopo(VERTEX_T * pNewVtx)
{
	if (vListHeadTopo == NULL)  /* first vertex */
	{
		vListHeadTopo = pNewVtx;
	}
	else
	{
		vListTailTopo->next = pNewVtx;
	}
	vListTailTopo = pNewVtx;
}

/** Finds the vertex that holds the passed key
 * (if any) and returns a pointer to that vertex.
 *
 *@param key    -  Key we are looking for
 *@param pPred  -  used to return the predecessor if any
 *@return pointer to the vertex structure if one is found
 */
VERTEX_T * findVertexByKey(char* key, VERTEX_T** pPred)
{
    VERTEX_T * pFoundVtx = NULL;
    VERTEX_T * pCurVertex = vListHead;
    *pPred = NULL;
    /* while there are vertices left and we haven't found
     * the one we want.
     */
    while ((pCurVertex != NULL) && (pFoundVtx == NULL))
       {
       if (strcmp(pCurVertex->key,key) == 0)
          {
	  pFoundVtx = pCurVertex;
	  }
       else
          {
	  *pPred = pCurVertex;
          pCurVertex = pCurVertex->next;
          }
       }
    return pFoundVtx;
}

/** Free the adjacencyList for a vertex
 *
 * @param  pVertex  Vertex whose edges we want to delete
 */
void freeAdjacencyList(VERTEX_T *pVertex)
	{
	ADJACENT_T * pCurRef = pVertex->adjacentHead;
	while (pCurRef != NULL)
		{
		ADJACENT_T * pDelRef = pCurRef;
		pCurRef = pCurRef->next;
		free(pDelRef);
		}
	pVertex->adjacentHead = NULL;
	pVertex->adjacentTail = NULL;
	}
/** Check if there is already an edge between
 * two vertices. We do not want to add a duplicate.
 * @param pFrom Start point of edge
 * @param pTo   End point of edge
 * @return 1 if an edge already exists, 0 if it does not
 */
int edgeExists(VERTEX_T* pFrom, VERTEX_T* pTo)
{
    int bEdgeExists = 0;
    ADJACENT_T * pCurRef = pFrom->adjacentHead;
    while ((pCurRef != NULL) && (!bEdgeExists))
       {
       if (pCurRef->pVertex == pTo)
          {
	  bEdgeExists = 1;  /* the 'To' vertex is already in the
                             * 'From' vertex's adjacency list */
          }
       else
          {
	  pCurRef = pCurRef->next;
          }
       }
    return bEdgeExists;
}

/** Color all vertices to the passed color.
 *  @param  A color constant
 */
void colorAll(int color)
{
    VERTEX_T* pVertex = vListHead;
    while (pVertex != NULL)
       {
       pVertex->color = color;
       pVertex = pVertex->next;
       }
}

/**  Function to print the information about a vertex
 * @param pVertex Vertex we want to print
 */
void printTask ()
	{
	VERTEX_T * current = vListHead;

  printf("\n\n---Print Task-----------------------\n\n");

	while (current != NULL)
		{
		printf("== Task key |%s| - description |%s| - estimatedtime |%d|\n",current->key, (char*) current->data, current->esTime);
		current = current->next;
		}
  
    printf("\n-----------------------------------\n\n");
	}

/** Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph()
	{
    VERTEX_T * pCurVertex = vListHead;
    while (pCurVertex != NULL)
   		{
       	freeAdjacencyList(pCurVertex);
		VERTEX_T * pDelVtx = pCurVertex;
		pCurVertex = pCurVertex->next;
		free(pDelVtx->key);
		free(pDelVtx);
		}
	vListHead = NULL;
    vListTail = NULL;

  EDGE_T * eCur = eHead;
  while(eCur != NULL)
  {
    free(eCur);
    eCur = eCur->next;
  }
  eHead = NULL;
  eTail = NULL;
  vListHeadTopo = NULL;
  vListTailTopo = NULL;
  vertices = NULL;
	}
/*
 * Function use to remove edge out of the graph
 */
int removeEdge(char* key1, char* key2)
	{
	int bOk = 1;
	VERTEX_T * pDummy = NULL;
	VERTEX_T * pFromVtx = findVertexByKey(key1,&pDummy);
	VERTEX_T * pToVtx = findVertexByKey(key2,&pDummy);
	if ((pFromVtx == NULL) || (pToVtx == NULL))
		{
		bOk = 0;
		}
	else if (!edgeExists(pFromVtx,pToVtx))
		{
		bOk = 0;
		}
	else
		{
		ADJACENT_T* pAdjacent = pFromVtx->adjacentHead;
		ADJACENT_T* pPrevAdjacent = NULL;
		while (pAdjacent != NULL)
			{
			if (pAdjacent->pVertex == pToVtx)  /* if this edge involves the target*/
				{
				if (pPrevAdjacent != NULL)
					{
					pPrevAdjacent->next = pAdjacent->next;
					}
				else
					{
					pFromVtx->adjacentHead = pAdjacent->next;
					}
             	if (pAdjacent == pFromVtx->adjacentTail)
	        		{
					pFromVtx->adjacentTail = NULL;
					}
	     		free(pAdjacent);
	     		break;
	    	 	}
			else
     			{
	     		pPrevAdjacent = pAdjacent;
	     		pAdjacent = pAdjacent->next;
	     		}
	  		}
		}
	return bOk;
	}
/*
 * Function use to remove all info that is involves to the
 * task that we remove.
 */
void removeReferences(VERTEX_T * pTarget)
		{
		VERTEX_T * pCurrentVtx = vListHead;
		while (pCurrentVtx != NULL)
			{
	      	if (pCurrentVtx != pTarget)
				{
				ADJACENT_T* pAdjacent = pCurrentVtx->adjacentHead;
				ADJACENT_T* pPrevAdjacent = NULL;
				while (pAdjacent != NULL)
		    		{
		    		if (pAdjacent->pVertex == pTarget)  /* if this edge involves the target*/
		       			{
		       			if (pPrevAdjacent != NULL)
		          			{
			  				pPrevAdjacent->next = pAdjacent->next;
		          			}
	       				else
		          			{
			  				pCurrentVtx->adjacentHead = pAdjacent->next;
		          			}
						if (pAdjacent == pCurrentVtx->adjacentTail)
		          			{
			 	 			pCurrentVtx->adjacentTail = NULL;
			  				}
						free(pAdjacent);
						pAdjacent = NULL;
						break;    /* can only show up once in the adjacency list*/
		       			}
	        		else
		       			{
						pPrevAdjacent = pAdjacent;
						pAdjacent = pAdjacent->next;
		       			}
	    			}
		 		}
	      	pCurrentVtx = pCurrentVtx->next;
			}
		}
	/** Execute a breadth first traversal from a vertex,
	 * calling the passed function (*vFunction) on each vertex
	 * as we visit it and color it black.
	 * @param pVertex  Starting vertex for traversal
	 */
void traverseBreadthFirst(VERTEX_T * pVertex)
	{
    VERTEX_T * pCurrent = NULL;
    VERTEX_T * pAdjacent = NULL;
    queueClear();
    colorAll(WHITE);
    pVertex->color = GRAY;
    enqueue(pVertex);
	while (queueSize() > 0)
		{
		pCurrent = (VERTEX_T*) dequeue();
		if (pCurrent->color != BLACK)
			{
			pCurrent->color = BLACK;
			ADJACENT_T* pRef = pCurrent->adjacentHead;
	  		while (pRef != NULL)
				{
				pAdjacent = (VERTEX_T*) pRef->pVertex;
				if (pAdjacent->color == WHITE)
					{
					pAdjacent->color = GRAY;
					enqueue(pAdjacent);
					}
	     		pRef = pRef->next;
				}
	  		}
		} /* end while queue has data */
	}
/*
 * Function  use to print all the dependency
 */
void eDepen ()
	{
	VERTEX_T * current = vListHead;
	ADJACENT_T * adCur = NULL;
	VERTEX_T * adTo = NULL;

	while (current != NULL)
		{
		adCur = current->adjacentHead;
		while(adCur != NULL)
			{
			adTo = adCur->pVertex;
			printf("\tEDGE From|%s|to|%s| estimatetime|%d|\n",current->key,adTo->key,current->esTime);
			adCur = adCur->next;
			}
		current = current->next;
		}
	}


/** Add a vertex into the graph.
 * @param  key   Key value or label for the  vertex
 * @param  pData Additional information that can be associated with the vertex.
 * @return  1 unless there is an error, in which case
 * it returns a 0. An error could mean a memory allocation
 * error or running out of space, depending on how the
 * graph is implemented. Returns -1 if the caller tries
 * to add a vertex with a key that matches a vertex
 * already in the graph.
 */
int addVertex(char* key, char* pdata, int weight)
	{
	int bOk = 1;
	VERTEX_T * pPred;
	VERTEX_T * pFound = findVertexByKey(key, &pPred);
	if (pFound != NULL)  /* key is already in the graph */
		{
		bOk = -1;
		}
	else
		{
		VERTEX_T * pNewVtx = (VERTEX_T *) calloc(1,sizeof(VERTEX_T));
		char * pKeyval = strdup(key);
		char * data = strdup(pdata);
		if ((pNewVtx == NULL) || (pKeyval == NULL) || (data == NULL))
			{
			bOk = 0;  /* allocation error */
			}
		else
	      	{
			pNewVtx->key = pKeyval;
		  	pNewVtx->data = data;
			pNewVtx->esTime = weight;
			if (vListHead == NULL)  /* first vertex */
				{
				vListHead = pNewVtx;
				}
			else
		 		{
				vListTail->next = pNewVtx;
				}
			vListTail = pNewVtx;
		  	}
	   }
	return bOk;
	}
/** Remove a vertex from the graph.
 * @param  key  Key value or label for the vertex to remove
 * @return a pointer to the data stored at that
 * vertex, or NULL if the vertex could not be
 * found.
 */
void removeVertex(char * key)
	{
	VERTEX_T * pPredVtx = NULL;
	VERTEX_T * pRemoveVtx = findVertexByKey(key,&pPredVtx);

	if (pRemoveVtx != NULL)
		{
		removeReferences(pRemoveVtx);
		freeAdjacencyList(pRemoveVtx);
		if (pPredVtx != NULL)
			{
			pPredVtx->next = pRemoveVtx->next;
			}
      	else /* if there is no predecessor that means this was the head */
			{
			vListHead = pRemoveVtx->next;
			}
      	if (pRemoveVtx == vListTail)
			{
			vListTail = pPredVtx;
			}
		free(pRemoveVtx->key);
		free(pRemoveVtx);
		}
	}

/* Function use to print all the dependency and call
 * function to store edge.
 */
void keepEdge (char* key1, char* key2, int check)
		{
		VERTEX_T * pDummy = NULL;
		VERTEX_T * pFromVtx = findVertexByKey(key1,&pDummy);

		if (check != 1)
			{
			printf("EDGE %s %s %d\n",key1,key2,pFromVtx->esTime);
			}
		forEdge(key1,key2,pFromVtx->esTime);
		}

/** Add an edge between two vertices
 * @param   key1  Key for the first vertex in the edge
 * @param   key2  Key for the second vertex
 * @param   weight Weight for this edge
 * @return  1 if successful, 0 if failed due to
 * memory allocation error, or if either vertex
 * is not found. Returns -1 if an edge already
 * exists in this direction.
 */
int addEdge(char* key1, char* key2)
	{
    int bOk = 1, check = -1;
    VERTEX_T * pDummy = NULL;
    VERTEX_T * pFromVtx = findVertexByKey(key1,&pDummy);
    VERTEX_T * pToVtx = findVertexByKey(key2,&pDummy);
    if ((pFromVtx == NULL) || (pToVtx == NULL))
		{
       	bOk = 0;
       	}
	else if (edgeExists(pFromVtx,pToVtx))
       {
       bOk = -1;
       }
    else
       	{
       	ADJACENT_T * pNewRef = (ADJACENT_T*) calloc(1,sizeof(ADJACENT_T));
       	if (pNewRef == NULL)
      		{
  		bOk = 0;
          	}
       	else
          	{
			pNewRef->pVertex = pToVtx;
			pNewRef->duration = pFromVtx->esTime;
	  		if (pFromVtx->adjacentTail != NULL)
          		{
	      		pFromVtx->adjacentTail->next = pNewRef;
	      		}
      		else
	      		{
     		 	pFromVtx->adjacentHead = pNewRef;
	      		}
	  		pFromVtx->adjacentTail = pNewRef;
			traverseBreadthFirst(pToVtx);
			if (pFromVtx->color == 2)
				{
				bOk = 2;
				}
      		}
		}

	return bOk;
	}
/*
 * function use to change the task key when we remove the task
 */
void changeKey ()
	{
	VERTEX_T * current = vListHead;
	int count = 0;
	int	check = 1;
	char keystring[128];
	char * key = NULL;

	while (current != NULL)
		{
		sscanf(current->key,"%d",&count);
		if (check != count)
			{
			sprintf(keystring,"%d",check);
			key = strdup(keystring);
			if (key == NULL)
				{
				printf("Allocate error exit!\n");
				exit(0);
				}
			current->key = key;
			}
		check++;
		current = current->next;
		}
	}
/*
 *Function use to print task to the file project
 */
void printtasktofile(FILE * pIn)
{
VERTEX_T * current = vListHead;
	while(current != NULL)
		{
		fprintf(pIn,"TASK %s %s %d\n",current->key,current->data,current->esTime);
		current = current->next;
		}
}
/*
 * Function use to print dependecy into the file when we
 * search the project.
 */
void printE (FILE * pIn)
	{
	VERTEX_T * current = vListHead;
	ADJACENT_T * adCur = NULL;
	VERTEX_T * adTo = NULL;
	while (current != NULL)
		{
		adCur = current->adjacentHead;
		while(adCur != NULL)
			{
			adTo = adCur->pVertex;
			fprintf(pIn,"EDGE %s %s %d\n",current->key,adTo->key,current->esTime);
			adCur = adCur->next;
			}
		current = current->next;
		}
	}
	/*
	 * Function that print the dependeny of the project when we
	 * add the project.
	  */
void printedgetofile(FILE * pIn)
{
	EDGE_T * eCurrent = eHead;
	while (eCurrent != NULL)
		{
		fprintf(pIn,"EDGE %s %s %d\n",eCurrent->key1,eCurrent->key2,eCurrent->weight);
		free(eCurrent);
		eCurrent = eCurrent->next;
		}
  eHead = NULL;
  eTail = NULL;
}
