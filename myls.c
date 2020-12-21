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

//Some of the codesnippets were borrowed from
//Attribution link: https://latesthackingnews.com/2017/03/22/c-program-implement-ls-command/
void removequotes(char * in2,char * withoutquotes,int off);
void checkerrno(char * msg);
int sort(const struct dirent **r2,const struct dirent **r1);
int min(int a ,int b);
char withoutquotes[400];

int main(int argc,char **argv){
	//printf("1 %d\n",EXIT_FAILURE);
    //printf("1 %s\n",argv[0]);

    char in2[MAX_RANGE_IN];
    strcpy(in2,argv[0]);    
    //perror("str ");
	char * p=strtok(argv[0]," ");
    p=strtok(NULL," ");
    //printf("a3:%s",p);


	struct dirent **record;
	//printf("2");
	int n;
	if(p==NULL || strcmp(p,"./")==0 || strcmp(p,".")==0){//no options
      
        errno=-100;
        //xxxxxxxxxxxxxborrowedxxxxxxxxxxx
        n=scandir(".",&record,NULL,sort);
        
        checkerrno("ls ");
        
        while (n-->0 && n>1) { 
              
            printf("%s ",record[n]->d_name);
                
            //printf("%c\n",record[n]->d_type); 
            //printf("%d\n",record[n]->d_reclen);  
            free(record[n]);
        } 
        free(record);
          //xxxxxxxxxxxxxborrowedxxxxxxxxxxx
        return 0;
    }
    removequotes( in2, withoutquotes,strlen("ls "));
     if(strcmp(p,"-m")==0){
        //printf("mmm\n");
        p=strtok(NULL," ");

        
        errno=-100;
        if(p==NULL){
            n=scandir(".",&record,NULL,sort);
        }
        else{
             //printf("in2%s",  in2);
            removequotes( in2, withoutquotes,strlen("ls "));
            //printf("with%s",withoutquotes);
            n=scandir(withoutquotes,&record,NULL,sort); 
        }
        checkerrno("ls ");
        
        while (n-->0 && n>1) { 
              
            printf("%s, ",record[n]->d_name);
                
            //printf("%c\n",record[n]->d_type); 
            //printf("%d\n",record[n]->d_reclen);  
            free(record[n]);
        } 
        free(record);
        
        
    }
    else if(strcmp(p,"-i")==0){
          //printf("mmm\n");
        p=strtok(NULL," ");

        
        errno=-100;
        if(p==NULL){
            n=scandir(".",&record,NULL,sort);
        }
        else{
            removequotes( in2, withoutquotes,strlen("ls "));
            n=scandir(withoutquotes,&record,NULL,sort); 
        }
        checkerrno("ls ");
        
        while (n-->0 && n>1) { 
              
            printf("%ld ",record[n]->d_ino); 
            printf("%s ",record[n]->d_name);
                
            //printf("%c\n",record[n]->d_type); 
            //printf("%d\n",record[n]->d_reclen);  
            free(record[n]);
        } 
        free(record);
        
    }
    else if(p[0]=='-'){
         printf("Invalid option\n");
    }
    else{
        if(strcmp(withoutquotes,"~")==0){
            errno=-100;
               
            n=scandir("/home",&record,NULL,sort);
                
            checkerrno("ls ");
        
            while (n-->0 && n>1) { 
              
                printf("%s ",record[n]->d_name);
                
                //printf("%c\n",record[n]->d_type); 
                //printf("%d\n",record[n]->d_reclen);  
                free(record[n]);
            } 
            free(record);
            //printf("Error in input command\n");

        }
        else if(strcmp(withoutquotes,"..")==0){
            errno=-100;
               
            n=scandir("..",&record,NULL,sort);
                
            checkerrno("ls ");
        
            while (n-->0 && n>1) { 
              
                printf("%s ",record[n]->d_name);
                
                //printf("%c\n",record[n]->d_type); 
                //printf("%d\n",record[n]->d_reclen);  
                free(record[n]);
            } 
            free(record);
            //printf("Error in input command\n");

        }
        else{
            errno=-100;
               
            n=scandir(withoutquotes,&record,NULL,sort);
                
            checkerrno("ls ");
        
            while (n-->0 && n>1) { 
              
                printf("%s ",record[n]->d_name);
                
                //printf("%c\n",record[n]->d_type); 
                //printf("%d\n",record[n]->d_reclen);  
                free(record[n]);
            } 
            free(record);
            printf("ls :Invalid input\n");
        }
    }
 	
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
                if(in2[p]=='-' && (in2[p+1]=='L' || in2[p+1]=='P'|| in2[p+1]=='n' || in2[p+1]=='e' || in2[p+1]=='s'|| in2[p+1]=='r'||in2[p+1]=='m'||in2[p+1]=='i')){
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

int sort(const struct dirent **r2,const struct dirent **r1){
    if( strcmp((*r1)->d_name,"..")==0 ||  strcmp((*r1)->d_name,".")==0 ){
        return 1;
    }
     if( strcmp((*r2)->d_name,"..")==0 ||  strcmp((*r2)->d_name,".")==0 ){
        return -1;
    }

    
    int l1=strlen((*r1)->d_name);
    int l2=strlen((*r2)->d_name);
    int l3=min(l1,l2);
    for(int i=0;i<l3;i++){
        if((*r1)->d_name[i]!=(*r2)->d_name[i]  )
            return   (*r1)->d_name[i]- (*r2)->d_name[i];


    } 

    return l1-l2;



}

int min(int a ,int b){
    if(a<b)
        return a;
    return b;

}