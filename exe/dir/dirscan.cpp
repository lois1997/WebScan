/*
*        �������ƣ�Ŀ¼ɨ������mulusm.exe��
*                ���ߣ�����
*                  QQ: 841116165
*                ��վ��[url]www.zixue7.com[/url]
*                ʱ�䣺2014/3/18
*        ʹ�����mulusm.exe -h [url]www.zixue7.com/admin/[/url] -f outfile
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
        printf( "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n"
                "�U               ��վĿ¼ɨ�蹤��(mulusm.exe)                 �U\n"
                "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n"
                "�U              ���ڲ�ͬ���ǣ�֧��https���ʵ���վ             �U\n"
                "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n"
                "�U����:����  QQ:841116165 ��ѵĺ�����ѧ��̳ [url]www.zixue7.com[/url]   �U\n"
                "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n"
                "�U �÷�:mulusm.exe -h [url]www.baidu.com:80/admin/[/url] -f zixue7.html  �U\n"
                "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n"
                "�U     -h:��ʾ��վ��ַ                                        �U\n"
                "�U        ����˿�Ĭ�ϲ���80���޸�ð�ź��������(Ĭ�Ͽɲ�д)  �U\n"
                "�U     -f:��ʾɨ�����ŵ�ʲô�ļ���Ĭ��  ����.html           �U\n"
                "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
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

        //���û�������в�������3���˳�
        if(argc<3)
        {
                useage();
                return 0;
        }

        //���������в���
        for(i=0; i<argc; i++)
        {
                //��ȡ������ַ
                if(strcmp(argv[i],"-h") == 0)
                {
                        strcpy_s(host, argv[++i]);
                }



                //��ȡ����ļ�
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
                printf("%s �ļ���ʧ��!�����Ƿ����!!", PATHFILE);
                return -1;
        }

        fw = fopen(outfile, "w");
        if(!fw)
        {
                printf("%s �ļ���ʧ��!�����Ƿ����!!", outfile);
                return -1;
        }

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if(!curl)
        {
                printf("curl init failed");
                return 0;
        }

        fputs("<p style='font-size:24px;line-height:50px;color:red;'>����������̳ <a target='_blank' style='font-size:24px;line-height:50px;color:green;' href='http://wwww.zixue7.com'>��ѧȥ [url]www.zixue7.com[/url]</a></p>\n", fw);
        fputs("<p style='color:red;'>����Ϊɨ��������ɫΪ����</p>\n", fw);
        while(!feof(fr))
        {



                ch[0] = fgetc(fr);

                //������ǻ��У��ͼ�����ȡ��ֱ��һ�н���
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

                //��ջ�����
                memset(temp, 0, 1000);
        }

        curl_easy_cleanup(curl);
        fputs("<p style='font-size:24px;line-height:50px;color:red;'>����������̳ <a target='_blank' style='font-size:24px;line-height:50px;color:blue;' href='http://wwww.zixue7.com'>��ѧȥ [url]www.zixue7.com[/url]</a></p>\n", fw);

        fclose(fr);
        fclose(fw);
        return 0;
}
