/*******************************************************
*dueDate.c
*
* 55
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"validate.h"
#include"dueDate.h"
static int dayInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int dd,mm,yyyy;
unsigned short daycounter = 0;;
int estimate =0 ;
int isLeap(int year)
{
    return ((year % 4 ==0 && year % 100 != 0) || year % 400 == 0);
}

/*
 * Function for count day in month
 */
void nextDay()
{
    dd += 1;
    daycounter++;
    if(dd > dayInMonth[mm])
    {
        dd = 1;
        mm += 1;
        if(mm > 12)
        {
            mm = 1;
            yyyy += 1;
            if(isLeap(yyyy))
            {
                dayInMonth[2] = 29;
            }
            else
            {
                dayInMonth[2] = 28;
            }
        }
    }
}

/*
 * Function for skip day
 */
void skipDays(int days)
{
    for(int i = 0;i<days;i++)
    {
        nextDay();
    }
}

/* schedule due date */
/* arg is date in form dd-mm-yyyy
 * and estimate time
 */
char * dueDate(char * startdate,int estimate)
{
      sscanf(startdate,"%d-%d-%d",&dd,&mm,&yyyy);
      skipDays(estimate);
      daycounter = 0;
      char * date = malloc(10);
      sprintf(date,"%d-%d-%d",dd,mm,yyyy);
      return date;
}

#ifdef DEBUG2
int main()
{
	  char * startdate = "18-05-2020";
    char finalDate[32];

		printf("debugging due date %s\n",startdate );
    strcpy(finalDate,dueDate(startdate,45));
    printf("due date is %s\n",finalDate);
    //free(finalDate);
}
#endif
