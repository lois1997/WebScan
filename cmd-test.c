#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[]){
    char *optstr = "s:p:m:k:b:l:uv";
    struct option opts[] = {
        {"server", 1, NULL, 's'},
        {"port", 1, NULL, 'p'},
        {"method", 1, NULL, 'm'},
        {"passwd", 1, NULL, 'k'},
        {"bind", 1, NULL, 'b'},
        {"listen", 1, NULL, 'l'},
        {"udp", 0, NULL, 'u'},
        {"version", 0, NULL, 'v'},
        {0, 0, 0, 0},
    };
    int opt;
    while((opt = getopt_long(argc, argv, optstr, opts, NULL)) != -1){
        switch(opt){
            case 'v':
                printf("version 2.3.0\n");
                return 0;
            case 's':
                printf("server: %s\n", optarg);
                break;
            case 'p':
                printf("port: %s\n", optarg);
                break;
            case 'm':
                printf("method: %s\n", optarg);
                break;
            case 'k':
                printf("passwd: %s\n", optarg);
                break;
            case 'b':
                printf("bind: %s\n", optarg);
                break;
            case 'l':
                printf("listen: %s\n", optarg);
                break;
            case 'u':
                printf("enable udp\n");
                break;
            case '?':
                if(strchr(optstr, optopt) == NULL){
                    fprintf(stderr, "unknown option '-%c'\n", optopt);
                }else{
                    fprintf(stderr, "option requires an argument '-%c'\n", optopt);
                }
                return 1;
        }
    }
    return 0;
}
