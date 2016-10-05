
#include <iostream>

int parseComand(char* str_command , int * argc, char*** argv)
{
    int count = 1;
    char* command_dup = strdup(str_command);
    char* match = strtok(command_dup, " " );

    while (match != NULL)
    {
        count++;
        match = strtok(NULL, " ");
    }

    *argv = (char**)malloc( sizeof(char *)*(count+1));

    (*argv)[count] = 0 ;
    if(count > 1)
    {
        int i = 0 ;
        command_dup = strdup(str_command);
        match = strtok(command_dup, " " );
        do{
            (* argv)[i++]=strdup(match);
            match = strtok(NULL, " ");
        } while (match!=NULL);

    }
    *argc = count;
    return 1;
}

int main()
{
    int argc = 0;
    char **argv = NULL;
    char *str = ( char*)"./ dxpc -d 8";

    parseComand(str, &argc, &argv);
    printf( "argc = %d, argv[1] = %s\n" , argc, argv[2]);

    return true;
}