#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int opt = 0;
int start_daemon = 0;
int daemon_time = 0;
int interval = 0;
char *command = "";
char working_dir[1024];

void getworkingdir ();
void daemonize ();
void parseargs (int argc, char **argv);

#define HELP \
" \n \
daemon-maker (dm) is a program designed to make daemon creation super easy. \n \
 \n \
Simply pass a command to the `dm` execuatble with the `-c` flag, set an interval \n \
using the `-i` flag, and set a time limit using the `-t` flag. #boom. \n \
\n \
options: \n \
-h [y/n] : Show this help message, then exit \n \
-c [command] : Shell command to daemonize (in quotes) \n \
-i [time In seconds] : the interval to execute the daemon at. \n \
-t [time In seconds] : the amout of time to keep the daemon running for. \n \
 \n \
"

int main (int argc, char **argv)
{
    parseargs(argc, argv);
               
    getworkingdir();

    daemonize();
                
    return EXIT_SUCCESS;    
}

void getworkingdir ()
{
    char *res = getcwd(working_dir, sizeof(working_dir));
    if(res == NULL)
        exit(EXIT_FAILURE);
    printf("working dir set to: %s\n", working_dir);
}

void daemonize ()
{
    pid_t pid, sid;

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);

    sid = setsid();
    if (sid < 0)
        exit(EXIT_FAILURE);

    //fclose(stdin);
    //fclose(stdout);
    //fclose(stderr);

    time_t start;
    time_t curr; 
   
    time(&start); 

    while(1)
    {
        system(command);

        curr = time(&curr);
        int time = (long) difftime(curr, start);
        if(time > daemon_time)
            break;

        sleep(interval);
    }

    exit(EXIT_SUCCESS);

}

void parseargs (int argc, char **argv)
{
    char *str = NULL;

    while ((opt = getopt(argc, argv, "i:c:t:h:")) != -1)
    {
        switch (opt) {
            case 'h':
                if(*optarg == 'y') {
                    printf(HELP);
                    exit(EXIT_SUCCESS);
                }
                break;

            case 'c':
                command = malloc(strlen(optarg)+1);
                strcpy(command, optarg);
                printf("c:%s\n", optarg);
                break;
            
            case 'i':
                printf("i:%s\n", optarg);
                str = malloc(strlen(optarg)+1);
                strcpy(str, optarg);
                interval = atoi(str);
                break;
            
            case 't':
                printf("t:%s\n", optarg);
                str = malloc(strlen(optarg)+1);
                strcpy(str, optarg);
                daemon_time = atoi(str);
                break;
            
            default:
                printf("invalid argument\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
}
