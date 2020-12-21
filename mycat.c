#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#define MAX_RANGE_IN 200
void checkerrno(char * msg);
void removequotes(char * in2,char * withoutquotes,int off);
//-n    number all output lines
//-E  display $ at end of each line
//for 1 file
//done
char withoutquotes[400];
int main(int argc,char **argv){
    char in2[MAX_RANGE_IN];
            //int len=strlen(argv[0]);  
            //printf("argv[0]:%s\n",argv[0]);
            
            
    strcpy(in2,argv[0]);    



    char *p=strtok(argv[0]," ");
    //printf("%s\n",p);
    p=strtok(NULL," ");
    char s[200];
    FILE *u;
     int len;
    if(p==NULL){
        printf("cat :Invalid input\n");
        exit(0);

    }
    else if(strcmp(p,"-E")==0){
        removequotes( in2, withoutquotes,strlen("cat "));
        //printf("withoutquotes:%s\n",withoutquotes);
        p=strtok(NULL," ");
        if(p==NULL){
            printf("cat :Invalid input\n");
            exit(0);

        }
        errno=-100;
        u=fopen(withoutquotes,"r");
        if(u==NULL){
            checkerrno("cat ");
        }
        errno=-100;
        while(fgets(s,199,u)!=NULL){
            checkerrno("cat ");
            len=strlen(s);
            s[len-1]='$';
            s[len]='\n';
            s[len+1]='\0';
            printf("%s",s);
            
            //printf("%s",s);
        }
        fclose(u);

    }
    else if(strcmp(p,"-n")==0){
        removequotes( in2, withoutquotes,strlen("cat "));
         //printf("withoutquotes:%s\n",withoutquotes);
        int co=1;
        p=strtok(NULL," ");
        if(p==NULL){
             printf("cat :Invalid input\n");
             exit(0);

         }
        errno=-100;
        u=fopen(withoutquotes,"r");
        if(u==NULL){
            checkerrno("cat ");
        }
        errno=-100;
        while(fgets(s,199,u)!=NULL){
            checkerrno("cat ");
            printf("    %d  %s",co,s);
            co+=1;
            //printf("%s",s);
        }
        fclose(u);
        
    }
    else if (p[0]=='-'){
        printf("cat :Invalid option\n");
        exit(0);

    }
    else{
            removequotes( in2, withoutquotes,strlen("cat "));        
            errno=-100;
            u=fopen(withoutquotes,"r");
            if(u==NULL){
                checkerrno("cat ");
            }
            errno=-100;
            while(fgets(s,199,u)!=NULL){
                checkerrno("cat ");
                printf("%s",s);
                
                //printf("%s",s);
            }
            fclose(u);
        

    }


  
    //printf("%d", num);    
    return 0;
}

void checkerrno(char *msg){
                if(errno!=-100)
                {
                    //printf("%s\n",strerror(errno));
                    perror(msg);
                    exit(EXIT_FAILURE);
                }
}
void removequotes(char * in2,char * withoutquotes,int off){
                int p=0;
                p+=off;
                if(strlen(in2)<off){
                    return ;
                }
                while(in2[p]==' '){
                    p+=1;
                }
                if(in2[p]=='-' && (in2[p+1]=='L' || in2[p+1]=='P'|| in2[p+1]=='n' || in2[p+1]=='e' || in2[p+1]=='s'|| in2[p+1]=='r' || in2[p+1]=='E')){
                    p+=3;
                }
                while(in2[p]==' '){
                    p+=1;
                }
                int i=0;
                while(in2[p]!='\0'){
                    if(in2[p]!='\"'){
                    
                        withoutquotes[i]=in2[p];
                        i+=1;
                    }
                    p+=1;
                }   
                withoutquotes[i]='\0';          

}