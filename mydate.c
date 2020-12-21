#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_RANGE_IN 200
//date 
//date -u
//date -r a1.c

void removequotes(char * in2,char * withoutquotes,int off);
void checkerrno(char * msg);
char withoutquotes[400];

int main(int argc,char **argv){
			char in2[MAX_RANGE_IN];
			//int len=strlen(argv[0]);	
			//printf("argv[0]:%s\n",argv[0]);
			
			
			strcpy(in2,argv[0]);	
			char* words=strtok(argv[0]," ");

			//printf("arc:%d\n",argc);
			
			words=strtok(NULL," ");
			if(words==NULL){
				time_t t;
				errno=-100;
				time(&t);
				checkerrno("date ");
				char *timebuf;//[200];
				errno=-100;
				timebuf=ctime(&t);
				checkerrno("date ");
				int size=strlen(timebuf);
				//printf("%d",size);
				char year[5];year[0]=timebuf[size-5];year[1]=timebuf[size-4];year[2]=timebuf[size-3];year[3]=timebuf[size-2];year[4]='\0';
				timebuf[size-5]='I';
				timebuf[size-4]='S';
				timebuf[size-3]='T';
				timebuf[size-2]='\0';
				printf("%s %s\n",timebuf,year);
			}
			else if(strcmp(words,"-u")==0){
				words=strtok(NULL," ");
				
					time_t t;
				errno=-100;
				time(&t);
				checkerrno("date ");
				char *timebuf;//[200];
				errno=-100;
				struct tm *ptm=gmtime(&t);
				checkerrno("date ");
				errno=-100;
				timebuf=asctime(ptm);
				checkerrno("date ");
				int size=strlen(timebuf);
				//printf("%d",size);
				char year[5];year[0]=timebuf[size-5];year[1]=timebuf[size-4];year[2]=timebuf[size-3];year[3]=timebuf[size-2];year[4]='\0';
				timebuf[size-5]='U';
				timebuf[size-4]='T';
				timebuf[size-3]='C';
				timebuf[size-2]='\0';
				printf("%s %s\n",timebuf,year);

			}
			else if(strcmp(words,"-r")==0){
				//printf("in2:%s\n",in2);
				removequotes( in2, withoutquotes,strlen("date "));
				words=strtok(NULL," ");
				if(NULL==words){
					printf("%s\n","date :Give file path");
					exit(EXIT_FAILURE);
				}
				struct stat attrib;
    			errno=-100;
    			//printf("withoutquotes:%s\n",withoutquotes);
    			stat(withoutquotes, &attrib);
    			checkerrno("date ");
    			//printf("File doesnt exist\n");

    			//}
    			//else{
    			char *timebuf;
    			//char time[50];
    			//strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib.st_mtime));
    			//printf();
    			//printf ("%s\n", time);
    			errno=-100;
    			timebuf=asctime(localtime(&attrib.st_mtime));
				checkerrno("date ");
				int size=strlen(timebuf);
				//printf("%d",size);
				char year[5];year[0]=timebuf[size-5];year[1]=timebuf[size-4];year[2]=timebuf[size-3];year[3]=timebuf[size-2];year[4]='\0';
				timebuf[size-5]='I';
				timebuf[size-4]='S';
				timebuf[size-3]='T';
				timebuf[size-2]='\0';
				printf("%s %s\n",timebuf,year);
				

			}
			else if (words[0]=='-'){
				printf("Invalid option\n");
				exit(0);

			}
			else{
				printf("Error in input date command\n");
				exit(0);
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
				if(in2[p]=='-' && (in2[p+1]=='L' || in2[p+1]=='P'|| in2[p+1]=='n' || in2[p+1]=='e' || in2[p+1]=='s'|| in2[p+1]=='r')){
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
