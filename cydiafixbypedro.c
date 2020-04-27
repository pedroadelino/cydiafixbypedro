//Cydia Fix
//For white screen problem only
//by Pedro Adelino
//Nara Logic 2020
//www.bypedro.eu

//Version
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION 0.1
#define VERSION_REVISION 1
//#define VERSION STRINGIZE(VERSION_MAJOR) "." STRINGIZE(VERSION_MINOR)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>      /* needed to use pid_t, etc. */
#include <sys/wait.h>       /* needed to use wait() */  
//double app_version = VERSION;
const char *app_version = "0.1";
//int println;
int main(int argc, char **argv)
{
    //int ret;
	//println("Cydia Repos v." + app_version);
    printf("\033[1;34m"); // Blue color
    printf("Cydia Fix v%s\n", app_version);
    printf("For white screen problem only.\n");
	printf("By Pedro Adelino.\n");
    printf("www.bypedro.eu\n");
    //The following example searches for the location of the command
    //among the directories specified by the PATH environment variable.
    //ret = execlp("ls", "ls", "-l", (char *)NULL);
    int commandnr;
    int errors=0;
    FILE *file;
    for(commandnr=1;commandnr<=2;commandnr++){
        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            printf("\033[1;31m"); // Red color
            printf("A fork error has occurred. Please try again!\n");
            printf("\033[0m"); // Reset color
            exit(-1);
        }
        else 
        if (pid == 0) /* We are in the child. */
        {
            if (commandnr == 1){
            //Command1
            //printf("Command1\n");
            
            //printf("I am the child, about to call ls using execlp.\n");
            //char *command = ;

            if((file = fopen("/private/var/mobile/Library/Cydia/metadata.cb0","r"))!=NULL)
            {
                // file exists
                fclose(file);
                printf("\033[1;32m"); // Green color
                printf("Found Metadata!\n");
                printf("\033[0m"); // Reset color
                //check backup
                if((file = fopen("/private/var/mobile/Library/Cydia/metadata.cb0.backup","r"))!=NULL)
                {
                    // file exists
                    fclose(file);
                    printf("\033[1;33m"); // Yellow color
                    printf("Found Metadata backup! Performing fix...\n");
                    printf("\033[0m"); // Reset color
                    execlp("rm", "rm", "/private/var/mobile/Library/Cydia/metadata.cb0" , NULL);
                    printf("\033[1;31m"); // Red color
                    printf("Error deleting Metadata!\n");
                    printf("\033[0m"); // Reset color
                    errors++;
                }
                else
                {
                    //change name, create backup
                    printf("\033[1;33m"); // Yellow color
                    printf("Backing up...\n");
                    printf("\033[0m"); // Reset color
                    execlp("mv", "mv", "/private/var/mobile/Library/Cydia/metadata.cb0", "/private/var/mobile/Library/Cydia/metadata.cb0.backup" , NULL);
                    printf("\033[1;31m"); // Red color
                    printf("Error creating Metadata backup!\n");
                    printf("\033[0m"); // Reset color
                    errors++;
                }
            }
            else
            {
                //Metadata not found, no memory leak since 'file' == NULL
                printf("\033[1;33m"); // Yellow color
                printf("Metadata not found! No changes performed.\n");
                printf("\033[0m"); // Reset color
            }

            //If execlp() is successful, we should not reach this next line.
            //printf("The call to execlp() was not successful.\n");
            //printf("\033[1;31m"); // Red color
            //printf("Failed executing command 1.\n");
            //printf("\033[0m"); // Reset color
            //errors++;
            exit(127);
            }
            else
            if (commandnr == 2){
                //Command2
                //printf("Command2\n");
                //char *command = ;
                execlp("ls" , "ls" , "/private/var/mobile/Library/Cydia/", NULL);
                /*  If execlp() is successful, we should not reach this next line. */
                //printf("The call to execlp() was not successful.\n");
                printf("\033[1;31m"); // Red color
                printf("Failed executing command 2.\n");
                printf("\033[0m"); // Reset color
                errors++;
                exit(127);
            }
        }
        else  /* We are in the parent. */
        {
            //Command executed
            //pid = 0;
            wait(0);               /* Wait for the child to terminate. */
            //Go to the next command or exit
        }
    } //Loop
    if (errors == 0) {
        printf("\033[1;32m"); // Green color
        printf("Please restart Cydia.\n");
        printf("All done. Have fun!\n");
        printf("\033[0m"); // Reset color
    }
    else {
        printf("\033[1;31m"); // Red color
        printf("Cannot complete fix! Please try again!\n");
        printf("\033[0m"); // Reset color
    }
    //printf("I am the parent.  The child just ended.  I will now exit.\n");
    exit(0);
    return(0); 
}