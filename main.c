#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include <termios.h>
#include <unistd.h>
#include"helpFunctions.h"
#include"computerInventoryFunctions.h"


int main(int argc, char const *argv[])
{
    int logging=0;
    while (!logging)
    {
        logging=logIn();
    }

    while(1) {

    printf("\n\n\t\t\t\tWELCOME !\n Please choose an action :\n\n");
    printf("\t1. Add a new Brand\n\t2. Delete a brand\n\t3. Add a new Computer\n\t4. Show Items by Brand\n\t5. Search an Item\n\t6. Exit\n\n");
    printf("=======>  ");

    

    switch (charGet())
        {

    case '1':
        printf("\n\n");
        addBrand();
        break;

    case '2':
        printf("\n\n");
        deleteBrand();
        break;

    case '3':
        printf("\n\n");
        addComputer();
        break;

    case '4':
        printf("\n\n");
        showComputers();
        break;

    case '5':
        printf("\n\n");
        searchComputer();
        break;

    case '6':
        printf("\n\n");
        return 0;

    default:
        break;
        }
    }
    return 0;
}