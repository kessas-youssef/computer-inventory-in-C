typedef struct computer
{
    char* brandName;
    char* name;
    char* reference;
}computer;


void addBrand(void);
void deleteBrand(void);
void addComputer(void);
void updateQuantity(char* brandName);
int logIn(void);
void showComputers(void);
void searchComputer(void);

void addBrand(void) {

    printf("\nEnter new Brand's name : ");
    char* newBrand=getStr(LOWER);//converts to lowercase
    

    FILE* testPtr=fopen(newBrand,"r");

    if(testPtr)
    {
        printf("\nERROR: Existing brand !\n");
        fclose(testPtr);
    }   
    else
    {
        testPtr=fopen(newBrand,"w+");
        printf("\n--- The brand \"%s\" has been created successfully ---\n",newBrand);
        fprintf(testPtr,"%s | Quantity : 0 .\n",newBrand);
        fclose(testPtr);
    }
    free(newBrand);
}

void deleteBrand(void) {
    
    printf("\nEnter a Brand to delete : ");
    char* toDeleteBrand=getStr(LOWER);//converts to lower since all created brands are lowercase

    FILE* testPtr=fopen(toDeleteBrand,"r");

    if(testPtr)
    {
        printf("\nAre you sure ? [y/n] ");
        char confirm=charGet();
        switch (confirm)
        {
        case 'y':
        case 'Y':
            remove(toDeleteBrand);
            break;

        case 'n':
        case 'N':
            fclose(testPtr);
            return;

        default:
            fclose(testPtr);
            printf("\nDeleting \"%s\" has been cancelled please next time choose [y/n]\n\n",toDeleteBrand);
        }
    }   
    else
    {
        printf("--- The brand \"%s\" does not exist ---",toDeleteBrand);
    }
    free(toDeleteBrand);
}

void addComputer(void)
{
    computer* newComputer=(computer*)malloc(sizeof(computer));
    
    printf("Computer Brand :");
    newComputer->brandName=getStr(LOWER);//Input brand Name

    FILE* brandFile=fopen(newComputer->brandName,"r");//check if the brand exists

    if(brandFile)//it exists
    {
        int itemNumber = lineCount(brandFile)-1;//lineCount()-1 = rank of added item (-1 for 1st line brand infos)
        
        fclose(brandFile);
        brandFile=fopen(newComputer->brandName,"a");//reopen append mode to add content

        printf("Computer name : ");
        newComputer->name=getStr(LOWER);

        printf("Reference :");
        newComputer->reference=getStr(LOWER);

        //Append computer infos into the file
        fprintf(brandFile,"%d- %s | %s |\n",itemNumber,newComputer->name,newComputer->reference);
        fclose(brandFile);//done

        printf("\n||==||Computer \"%s\" succesfully created||==||\n",newComputer->name);
        updateQuantity(newComputer->brandName);//update brands quantity

        //free Palestine !
        free(newComputer->brandName);
        free(newComputer->name);
        free(newComputer->reference);

    }
    else
    {
        printf("\nThe Brand \"%s\" does not exist please add it first\n",newComputer->brandName);
    }
    free(newComputer);
}

void updateQuantity(char* brandName)
{
    FILE* updateFile=fopen("updateFileName","w");//New File to copy into
    FILE* srcFile=fopen(brandName,"r");//Source brand file to copy from

    char c=fgetc(srcFile);

    do //copy form source to new from char 0 until ':' (just before the quantity value)
    {
    fprintf(updateFile,"%c",c);
    }
    while((c=fgetc(srcFile)) != ':');

    fprintf(updateFile,": %d .",lineCount(srcFile)-2);//print new value (lineCount explained in line 95)
    rewind(srcFile);//lineCount() took the pointer to the EOF so rewind it back to continue copying 

    while ((c=fgetc(srcFile)) != '.')
    {
        //loop to jump to second line of source file and copy Items
    }
    

    while ((c=fgetc(srcFile)) != EOF)//copy source items to new File
    {
        fprintf(updateFile,"%c",c);
    }

    fclose(updateFile);
    fclose(srcFile);

    remove(brandName);//remove old source file
    rename("updateFileName",brandName);// rename the new File to the actual brand name 
}

int logIn(void)
{
    char *userName;
    char *password;
    
    printf("\n\n*******************************************************|| ETS. Kessas & Bendahmane Storage system ||*******************************************************\n\n\n");
    printf("|*|               Please log-in\n\n");

    printf("Username : ");
    userName=getStr(NONE);

    printf("\nPassword : ");
    password=getStr(SECRET);

    if(!strcmp("kessas",userName) && !strcmp("bendahmane",password))
        return 1;
    
    else
    {
        printf("\n\n\t\t\t\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("\t\t\t\tWRONG INFORMATIONS ! PLEASE RETRY CORRECTLY.");
        printf("\n\t\t\t\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
        return 0;
    }
    free(userName);
    free(password);
}

void showComputers(void)
{
    printf("Please introduce brand name:\n");
    char *brandName=getStr(NONE);
    
    FILE* brandFile=fopen(brandName,"r");
    
    if(brandFile)
    {
        char c;
        printf("\n\n\t\t\t\t================== ALL \"%s\" units : ==================\n\n",brandName);
        while((c=fgetc(brandFile)) != EOF)
            printf("%c",c);
            fclose(brandFile);
    }
    else 
        printf("\t\t ERROR: The brand \"%s\" does not exist ! Please retry correctly.\n\n",brandName);
    free(brandName);
}

void searchComputer(void)
{
    printf("Please introduce brand name:\n");
    char *brandName=getStr(NONE);
    printf("Please introduce computer name:\n");
    char *computerName=getStr(LOWER);
    printf("\n\t");
    
    FILE* brandFile=fopen(brandName,"r");

    if(brandFile)
    {
        char searchedItem[100];
        int i=0;
        while(fscanf(brandFile,"%s",searchedItem) != EOF)
        {
            if(!strcmp(searchedItem,computerName))
            {
                do
                {
                    printf("%s ",searchedItem);
                    i++;
                }
                while(i<5 && (fscanf(brandFile,"%s",searchedItem) != EOF));
                printf("\n\n");
                return;
            }
            else
                continue;
        }
        printf("\n\t\t\"%s\" does not exist in the System !",computerName);
    }
    else 
        printf("\n\n\t\t Brand \"%s\" does not exist !\n\n",brandName);
    
    free(brandName);
    free(computerName);
}