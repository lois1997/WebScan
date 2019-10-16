#include <stdio.h>
#include <string.h>
#include "helpcmd.h"
#include "printfcmd.h"

int executeMapping(char *url,char *lang,char *port){
	char *cmp = "null";
	if(strcmp(url,cmp) == 0 && strcmp(lang,cmp) == 0 && strcmp(port,cmp) == 0)
		printHelp();
	
}
int executeScan(char *url,char *lang,char *port) {
	printf("the url is %s\n", url);
	printf("the lang is %s\n", lang);
	printf("the port is %s\n", port);
	return 0;
}

