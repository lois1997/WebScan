#include <stdio.h>
#include <string.h>
int executeScan(char *url,char *lang,char *port) {
	printf("the url is %s\n", url);
	printf("the lang is %s\n", lang);
	printf("the port is %s\n", port);
	return 0;
}

char *url = "http"; 
char *lang = "asp";
char *port = "sensitive";

int main(){
	executeScan(url,lang,port);
}
