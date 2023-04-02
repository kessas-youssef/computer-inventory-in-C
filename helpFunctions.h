void strtoUpper(char* string); //MUST INCLUDE string.h & ctype.h
char* getStr(char* charLevel); //MUST INCLUDE string.h & ctype.h & stdlib.h
char charGet(void); //MUST INCLUDE stdio.h
int lineCount(FILE *file);  //MUST INCLUDE stdio.h
int getch(void); //MUST INCLUDE termios.h & unistd.h & stdio.h
char* fgetStr(FILE* srcFile, char* string); //MUST INCLUDE string.h & stdlib.h

#define LOWER "lower"
#define UPPER "upper"
#define NONE "keep"
#define SECRET "secret"

/* As follows :
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include <termios.h>
#include <unistd.h>
#include"helpFunctions.h"
#include"computerInventoryFunctions.h" 
*/


void strtoUpper(char* string) //MUST INCLUDE string.h & ctype.h
{   //Convert string to upper case
    int i=0, length=strlen(string);

    for ( i = 0; i < length; i++)
    {
        string[i]=toupper(string[i]);
    }
}

char* getStr(char* charLevel) //MUST INCLUDE string.h & ctype.h & stdlib.h & termios.h & unistd.h & stdio.h
{   // Read string from user and avoid trailing '\n'
    //converts it to lowerCase
    //malloc and realloc to avoid using unecessary space with arrays like: array[100];
    char *input=(char*)malloc(sizeof(char));
    int count=0, length=5; 
    char c;

    if(!strcmp("secret",charLevel))
    {
        for (count = 0 ; (c=getch()) != '\n'; count++)
        {
            if(count == length)
            input = realloc(input, (length += 3)*sizeof(char));
        
            input[count]= c;
            printf("*");
        }
    }

    else 
        for (count = 0 ; (c=getchar()) != '\n'; count++)
        {
            if(count == length)
            input = realloc(input, (length += 3)*sizeof(char));
            
            if(!strcmp("lower",charLevel))
            {
                input[count] = tolower(c);
            }
            else if(!strcmp("upper",charLevel))
                input[count] = toupper(c);
            else if(!strcmp("keep",charLevel))
                input[count] = c;
            
        }

    if(count==length)
        input=realloc(input,sizeof(char));

    input[count]='\0';

    return input; //MUST FREE WHEN DONE USING IT !!
}

char charGet(void) //MUST INCLUDE stdio.h
{   //Read character from user without trailing '\n'
    char input, temp;
    input=getchar();
    temp=getchar();
    return input;
}

int lineCount(FILE *file) //MUST INCLUDE stdio.h
{ 
    int i=0,c;
    
    do
    {
        if(( (c=fgetc(file))==EOF) && (ftell(file)==0) )
        {
            return 0;
        }
        
        if(c == '\n' || c== EOF)
        i++;
    }
    while(c != EOF);
        return i;
}

/* reads from keypress, doesn't echo */
int getch(void)//MUST INCLUDE termios.h & unistd.h
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

char* fgetStr(FILE* srcFile, char* string)
{
    string=(char*)malloc(sizeof(char));
    int count,c,length=5;

    for (count = 0 ; (c=fgetc(srcFile)) != '\n'; count++)
        {
            if(count == length)
            string = realloc(string, (length += 3)*sizeof(char));

            string[count] = c;            
        }
        if(count==length)
            string=realloc(string,sizeof(char));

        string[count]='\0';

        return string; //MUST FREE WHEN DONE USING IT !!
}