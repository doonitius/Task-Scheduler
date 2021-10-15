#ifndef ABSTRACTNETWORK2_H
#define ABSTRACTNETWORK2_H
/*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*/
/* List items for the adjacency list.
 * Each one represents an edge leading to an existing vertex
 */
typedef struct _adjacent
	{
    void * pVertex;           /* pointer to the VERTEX_T this
                               * item refers to.
                               */
    unsigned int duration;      /* weight of this edge */
    struct _adjacent * next;  /* next item in the ajacency list */
	}ADJACENT_T;

/* List items for the main vertex list.*/
typedef struct _vertex
	{
  char * key;               /* key for this vertex */
  char * data;              /* ancillary data for this vertex */
	unsigned int esTime;
	char startDate[32];
	char endDate[32];
  int color;                /* used to mark nodes as visited */
  int dValue;               /* sum of weights for longest path so far to this vertex */
    struct _vertex * parent;  /* pointer to parent found in Dijkstra's algorithm */
    struct _vertex * next;    /* next vertex in the list */
	struct _vertex * fromVtx;
    ADJACENT_T * adjacentHead;    /* pointer to the head of the
		               * adjacent vertices list
                               */
    ADJACENT_T * adjacentTail;    /* pointer to the tail of the
			       * adjacent vertices list
                               */
	}VERTEX_T;

	/* List of edge for project */
typedef struct _edge
	{
    char * key1;
	char * key2;
	int weight;
    struct _edge * next;
		struct _edge * prev;
		} EDGE_T;

typedef struct _depro
	{
	   char * name;
	   struct _depro * next;
	} DEPRO_T;

VERTEX_T * listHead();

VERTEX_T * listTopo();

/*
 * Function to check amount of task
 */
int checkTask ();

/*
 * Function to add edge into a queue (end of the list)
 */
void forEdge (char * keystring1, char * keystring2, int weight);

/* Function to add project into a queue */
void namePro (char * name);

/* Function to print name of the project */
void printName (FILE * pName);

/* traverse to re-order the vertex
* in topological sorting
*/
int toposort();

/* find the longest path
* using shortest path algorithm but
* the weight is negative
* so the leastest path is the longest path
* when we multiple it by -1
*/
int printLongestPath();

/* connect the vertex that has no
* out-dependency to END
* and connect each that has no
* incoming-dependency to Start*/
int startEnd();

/* Execute a depth first search from a single vertex,
 * calling the function (*vFunction) on the lowest level
 * vertex we visit, and coloring it black.
 * Arguments
 *    pVertex    -  starting vertex for traversal
 */
void traverseDepthFirst(VERTEX_T* pVertex, void (*vFunction)(VERTEX_T*));

/* stack vertex that has been traversed */
void stackTopo(VERTEX_T * pVertex);

/* keep topological sorted vertex to pointer */
void orderTopo(VERTEX_T * pNewVtx);

/** Finds the vertex that holds the passed key
 * (if any) and returns a pointer to that vertex.
 *
 *@param key    -  Key we are looking for
 *@param pPred  -  used to return the predecessor if any
 *@return pointer to the vertex structure if one is found
 */
VERTEX_T * findVertexByKey(char* key, VERTEX_T** pPred);

/** Free the adjacencyList for a vertex
 *
 * @param  pVertex  Vertex whose edges we want to delete
 */
void freeAdjacencyList(VERTEX_T *pVertex);

/** Check if there is already an edge between
 * two vertices. We do not want to add a duplicate.
 * @param pFrom Start point of edge
 * @param pTo   End point of edge
 * @return 1 if an edge already exists, 0 if it does not
 */
int edgeExists(VERTEX_T* pFrom, VERTEX_T* pTo);

/** Color all vertices to the passed color.
 *  @param  A color constant
 */
void colorAll(int color);

/**  Function to print the information about a vertex
 * @param pVertex Vertex we want to print
 */
void printTask ();

/** Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph();

/*
 * Function use to remove edge out of the graph
 */
int removeEdge(char* key1, char* key2);

/*
 * Function use to remove all info that is involves to the
 * task that we remove.
 */
void removeReferences(VERTEX_T * pTarget);

/** Execute a breadth first traversal from a vertex,
	 * calling the passed function (*vFunction) on each vertex
	 * as we visit it and color it black.
	 * @param pVertex  Starting vertex for traversal
	 */
void traverseBreadthFirst(VERTEX_T * pVertex);

/*
 * Function  use to print all the dependency
 */
void eDepen ();

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
int addVertex(char* key, char* pdata, int weight);

/** Remove a vertex from the graph.
 * @param  key  Key value or label for the vertex to remove
 * @return a pointer to the data stored at that
 * vertex, or NULL if the vertex could not be
 * found.
 */
void removeVertex(char* key);

/* Function use to print all the dependency and call
 * function to store edge.
 */
void keepEdge (char* key1, char* key2, int check);

/** Add an edge between two vertices
 * @param   key1  Key for the first vertex in the edge
 * @param   key2  Key for the second vertex
 * @param   weight Weight for this edge
 * @return  1 if successful, 0 if failed due to
 * memory allocation error, or if either vertex
 * is not found. Returns -1 if an edge already
 * exists in this direction.
 */
int addEdge(char* key1, char* key2);

/*
 * function use to change the task key when we remove the task
 */
void changeKey ();

/*
 *Function use to print task to the file project
 */
void printtasktofile(FILE * pIn);

/*
 * Function use to print dependecy into the file when we
 * search the project.
 */
void printE (FILE * pIn);

/*
	 * Function that print the dependeny of the project when we
	 * add the project.
	  */
void printedgetofile(FILE * pIn);

#endif
