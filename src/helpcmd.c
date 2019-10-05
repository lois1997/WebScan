#include <stdio.h>

int printHelp() {
	FILE *fp;
	int c;
	// ATTENTION: this dir different from helpcmd.h
	fp = fopen("../data/help.txt","r");
	if(fp == NULL) {
		perror("open error");
		return(-1);
	}
	while(1) {
		c = fgetc(fp);
		if( feof(fp) ) {
			break ;
		}
		printf("%c", c);
	}
	fclose(fp);
	return(0);
}

int main(){
	printHelp();
}
