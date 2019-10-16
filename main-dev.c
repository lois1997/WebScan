#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "src\hello.h"
#include "src\helpcmd.h"
#include "src\printfcmd.h"
/*
Option struct:
name    long parameter name,e.g."help"
has_arg  if need parameter£¬0 no param£¬1 has param£¬2 optional param
flag    result of long param£¬if flag is NULL£¬getopt_long() will return its short param,e.g.'h'; if flag is not NULL£¬getopt_long() will return 0
val     short parameter name,e.g.'h'
*/
struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

/*
Arguments:
url    target website
lang   which language the website based on
port   target ports
*/
char *url = "null"; 
char *lang = "null";
char *port = "null";

int executeMapping(char *url,char *lang,char *port){
	char *cmp = "null";
	if(strcmp(url,cmp) == 0 && strcmp(lang,cmp) == 0 && strcmp(port,cmp) == 0)
		printHelp();
	else
		executeScan();
}

int executeScan(char *url,char *lang,char *port) {
	printf("the url is %s\n", url);
	printf("the lang is %s\n", lang);
	printf("the port is %s\n", port);
	return 0;
}

int main(int argc, char *argv[]){
	// print welcome content
	printBanner();
	// short param
    char *optstr = "u:l:p:hv";    
    // long param
	struct option opts[] = {
        {"url", 1, NULL, 'u'},
        {"lang", 1, NULL, 'l'},
        {"port", 1, NULL, 'p'},
        {"help", 0, NULL, 'h'},
        {"version", 0, NULL, 'v'},
        {0, 0, 0, 0},
    };
    int opt;
    while((opt = getopt_long(argc, argv, optstr, opts, NULL)) != -1){
        switch(opt){
        	case 'u':
        		// set scan target
                url = optarg;
            case 'l':
            	// set dev-language of target website
                lang = optarg;
                break;
			case 'p':
				// set scan ports
                port = optarg;
                break;
			case 'h':
				// print help message
				// helpcmd.h 
				printHelp();
                return 0;
			case 'v':
                printf("version 0.0.0\n");
                return 0;      
			case '?':
                if(strchr(optstr, optopt) == NULL){
                    fprintf(stderr, "unknown option '-%c'\n", optopt);
                }else{
                    fprintf(stderr, "option requires an argument '-%c'\n", optopt);
                }
                return 1;
        }
    }
    executeMapping(url,lang,port);
    return 0;
}
