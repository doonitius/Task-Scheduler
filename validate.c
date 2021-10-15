 /********************************************************
  *validate.c
	*
	* This program is to validate the date and time
	*
	*  PM2.5 schedule project
	*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
	*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
	*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
	*  Thanatip 			Lertboonchu (Preem)       62070503425
	********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"validate.h"

/*
 * check day/month/year function
 */
int checkday(int dd, int mm, int yyyy)
{
	int result; /* return value */
  time_t t=time(NULL);
  struct tm tm = *localtime(&t);
  
    if((dd >= tm.tm_mday && mm == tm.tm_mon+1 && yyyy == tm.tm_year+1900) ||
       (dd <= 31 && mm <= 12 && mm > tm.tm_mon+1 && yyyy == tm.tm_year+1900) ||
       (dd <= 31 && mm <= 12 && mm >= 1 && yyyy > tm.tm_year+1900))
    {
        if((dd >= 1 && dd <= 31) &&
           (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
        {
            result = 1;
        }
        else if((dd >= 1 && dd <= 30) &&
                (mm == 4 || mm == 6 || mm == 9 || mm == 11))
        {
            result = 1;
        }
        else if((mm == 2) && (yyyy %4==0) && (dd>=1 && dd<=29))
        {
            result = 1;
        }
            else if((mm == 2) && (yyyy %4!=0) && (dd>=1 && dd<=28))
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

/* 
 * date and time validating function 
 */
int validateDateTime(char checkDateTime[])
{
    int i = 0;                      /* counting loop */
    int result,status = 0;          /* boolean value */
    int yyyy,mm,dd;                 /* date and time variable */
    int len = strlen(checkDateTime); /*length of date and time */
	  int resultlast = 1;
    time_t t=time(NULL);
    struct tm tm = *localtime(&t);

            sscanf(checkDateTime,"%d-%d-%d",&dd,&mm,&yyyy);
            if(yyyy >= tm.tm_year+1900 && yyyy <= tm.tm_year+2000)
            {
                if((yyyy == tm.tm_year+1900 && mm >= tm.tm_mon+1)||
                   (yyyy > tm.tm_year+1900 && mm >=1 && mm <=12))
                {
                    status = checkday(dd,mm,yyyy);
                    if(status == 1)
                    {
                        resultlast = 0;
                    }
                    else
                    {
                        printf("\tNot valid - illegal day or must be in the future\n\n");
                    }
                }
                else
                {
                    printf("\tNot valid - illegal month or must be in the future\n\n");
                }
            }
            else
            {
								printf("%d\n",tm.tm_year+1900 );
                printf("\tNot valid - illegal year or must be in the future or year is out of range\n\n");
            }

		return resultlast;
}

#ifdef DEBUG
int main()
{
  char date[128];
	char input[128];
  
  while(1)
  {
	printf("date :" );
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",date);
	int ok = validateDateTime(date);
	if(ok == 0)
		printf("date ok\n");
  }
}
#endif
