#ifndef READDATA_H
#define READDATA_H

/*******************************************************
*readData.h
*
* Declarations for the function in readData.c
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/

PROJECT_T * sendProject();

void freeData();
/*
 * Function that add vertex
 */
void goAddVertex(char * key,char * data,int vertexEstimate);

/*
 * Function that read data and store it to variable
 * if longest = 1 -> multiply -1 to estimate time
 * else do nothing
 */
int ReadDataTxt(char filename[],int longest);

#endif
