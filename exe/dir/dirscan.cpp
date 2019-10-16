/*
*        工具名称：目录扫描器（mulusm.exe）
*                作者：飞仔
*                  QQ: 841116165
*                网站：[url]www.zixue7.com[/url]
*                时间：2014/3/18
*        使用命令：mulusm.exe -h [url]www.zixue7.com/admin/[/url] -f outfile
*/
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <curl/curl.h>
#include "concol.h"

#pragma comment(lib, "curllib.lib")

#define                PATHFILE        "zixue7.dat"


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
        char *p = (char *)ptr;
        if(*(p+9)=='2' && *(p+10)=='0' && *(p+11)=='0')
        {
                fputs(" style='color:red;' ", (FILE*)stream);
                setcolor(green,black);
        }
        return size*nmemb;
}

void useage()
{
        setcolor(yellow, black);
        printf( "╔══════════════════════════════╗\n"
                "║               网站目录扫描工具(mulusm.exe)                 ║\n"
                "╠══════════════════════════════╣\n"
                "║              与众不同的是，支持https访问的网站             ║\n"
                "╠══════════════════════════════╣\n"
                "║作者:飞仔  QQ:841116165 免费的黑阔自学论坛 [url]www.zixue7.com[/url]   ║\n"
                "╠══════════════════════════════╣\n"
                "║ 用法:mulusm.exe -h [url]www.baidu.com:80/admin/[/url] -f zixue7.html  ║\n"
                "╠══════════════════════════════╣\n"
                "║     -h:表示网站地址                                        ║\n"
                "║        如果端口默认不是80就修改冒号后面的数字(默认可不写)  ║\n"
                "║     -f:表示扫描结果放到什么文件，默认  域名.html           ║\n"
                "╚══════════════════════════════╝\n");
        setcolor(white,black);
        Sleep(10000);
}

int main(int argc, char **argv)
{
        char temp[1000]="",ch[2]="", url[1000]="", host[500]="", root[200]="", outfile[200]="", port[6]="";
        FILE *fr,*fw;
        //        struct socket_in addr;
        int i=0;
        CURL *curl;
        CURLcode res;

        //如果没有命令行参数少于3个退出
        if(argc<3)
        {
                useage();
                return 0;
        }

        //分析命令行参数
        for(i=0; i<argc; i++)
        {
                //获取主机地址
                if(strcmp(argv[i],"-h") == 0)
                {
                        strcpy_s(host, argv[++i]);
                }



                //获取输出文件
                if(strcmp(argv[i],"-f") == 0)
                {
                        strcpy_s(outfile, argv[++i]);
                }
        }

        if(!strlen(outfile))
        {
                strcpy_s(outfile,host);
                strcat_s(outfile,".html");
        }



        fr = fopen(PATHFILE, "r");
        if(!fr)
        {
                printf("%s 文件打开失败!请检查是否存在!!", PATHFILE);
                return -1;
        }

        fw = fopen(outfile, "w");
        if(!fw)
        {
                printf("%s 文件打开失败!请检查是否存在!!", outfile);
                return -1;
        }

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if(!curl)
        {
                printf("curl init failed");
                return 0;
        }

        fputs("<p style='font-size:24px;line-height:50px;color:red;'>黑阔交流论坛 <a target='_blank' style='font-size:24px;line-height:50px;color:green;' href='http://wwww.zixue7.com'>自学去 [url]www.zixue7.com[/url]</a></p>\n", fw);
        fputs("<p style='color:red;'>以下为扫描结果，红色为存在</p>\n", fw);
        while(!feof(fr))
        {



                ch[0] = fgetc(fr);

                //如果不是换行，就继续获取，直到一行结束
                if(ch[0]!='\n')
                {
                        strcat_s(temp,ch);
                        continue;
                }

                memset(url, 0, 1000);
                strcat_s(url,host);
                strcat_s(url,temp);


                curl_easy_setopt(curl, CURLOPT_URL, url);

                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fw);

                curl_easy_setopt(curl, CURLOPT_REFERER, url);

                curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 20000);

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

                curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

                fputs("<a ", fw);
                setcolor(gray,black);
                res = curl_easy_perform(curl);

                if(res != CURLE_OK)
                {
                        fprintf(stderr, "curl_easy_perform() failed:%d\n", curl_easy_strerror(res));
                        break;
                }
                fputs(" href='http://", fw);
                fputs(url, fw);
                fputs("'>", fw);
                fputs(url, fw);
                fputs("</a><br />\n",fw);
                printf("\n%s",url);

                setcolor(white, black);

                //请空缓冲区
                memset(temp, 0, 1000);
        }

        curl_easy_cleanup(curl);
        fputs("<p style='font-size:24px;line-height:50px;color:red;'>黑阔交流论坛 <a target='_blank' style='font-size:24px;line-height:50px;color:blue;' href='http://wwww.zixue7.com'>自学去 [url]www.zixue7.com[/url]</a></p>\n", fw);

        fclose(fr);
        fclose(fw);
        return 0;
}
