#include<stdio.h>
#include<stdlib.h>
#include<dir.h>
#include<string.h>
using namespace std;
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
char QT_setup_path[]="C:\\Qt\\";
char QT_ver[]="5.4";
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
int main(int argc,char *argv[]){
    if(argc<2){
        puts("need a input file.");
        return 0;
    }
    int len=strlen(argv[1]);
    int addlen=0;
    for(int i=0;i<len;++i){
        if(argv[1][i]=='\\')    ++addlen;
    }
    char filepath[len+1+addlen]={};
    char filename[len+1+addlen]={};
    int f=0,t=0;
    for(int i=0,nowpath=0,nowname=0;i<len;++i){
        if(argv[1][i]=='\\'){
            t++;
            if(t==addlen){
                f=1;
            }
            filepath[nowpath++]='\\';
        }
        else{
            if(!f){
                filepath[nowpath++]=argv[1][i];
            }
            else{
                filename[nowname++]=argv[1][i];
            }
        }
    }
    // make .bat file
    FILE* fbat=fopen("tmp.bat","w");
    fprintf(fbat,"set PATH=%s%s\\mingw491_32\\bin;%sTools\\mingw491_32\\bin;%%PATH%%\n",QT_setup_path,QT_ver,QT_setup_path);
    fprintf(fbat,"cd /D %s\n",filepath);
    fprintf(fbat,"%s%s\\mingw491_32\\bin\\windeployqt %s\n",QT_setup_path,QT_ver,filename);
    fclose(fbat);
    //
    char sys[len+addlen+50]={"cd "};
    strcat(sys,filepath);
    system("tmp.bat");
    remove("tmp.bat");
    return 0;
}
