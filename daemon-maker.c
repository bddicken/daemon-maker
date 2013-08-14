#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int opt = 0;
int start_daemon = 0;
int interval = 0;
char *input_file_name = "";
char *output_file_name = "";

void parseargs (int argc, char **argv);

#define HELP \
" \n \
daemon-maker (dm) is a program designed to make daemon creation super easy. \n \
 \n \
First, you must create a file with a series of bash commands (relative to \n \
the root directory). Then, run dm and pass the file name using the `-i` \n \
option. Set the interval you want the deamon to be executed at (in seconds) \n \
using the -t option. \n \
\n \
options: \n \
-h [y/n] : Show this help message, then exit \n \
-i [input file] : The input file with a series of bash commands. \n \
-o [output file] : The name of the ouput daemon executable. \n \
-t [time In seconds] : the interval to execute the daemon at. \n \
-s [y/n] : If `y`, the daemon immediately begins exection after creation \n \
 \n \
"

int main (int argc, char **argv)
{
    parseargs(argc, argv);
                
    return EXIT_SUCCESS;    
}

void parseargs (int argc, char **argv)
{
    char *str = NULL;

    while ((opt = getopt(argc, argv, "t:s:i:h:o:")) != -1)
    {
        switch (opt) {
            case 'h':
                if(*optarg == 'y') {
                    printf(HELP);
                    exit(EXIT_SUCCESS);
                }
                break;

            case 'i':
                input_file_name = malloc(strlen(optarg)+1);
                strcpy(input_file_name, optarg);
                printf("i:%s\n", optarg);
                break;
            
            case 'o':
                output_file_name = malloc(strlen(optarg)+1);
                strcpy(output_file_name, optarg);
                printf("o:%s\n", optarg);
                break;
            
            case 't':
                printf("t:%s\n", optarg);
                str = malloc(strlen(optarg)+1);
                strcpy(str, optarg);
                interval = atoi(str);
                break;
            
            case 's':
                printf("s:%s\n", optarg);
                str = malloc(strlen(optarg)+1);
                strcpy(str, optarg);
                start_daemon = atoi(str);
                break;
            
            default:
                printf("nada\n");
                break;
        }
    }
}
