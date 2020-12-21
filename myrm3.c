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
//rm
//rm -i asks for confirmation
//rm -v verbose

void checkerrno(char * msg);
void extr(int p,int p2, char * buf);
void f();
int j=0;
char withoutquotes[400],tok[400];
void clear();
int bit[2];//bit[0] i   bit[1] v

int main(int argc,char **argv){
	bit[0]=0;bit[1]=0;
	int len=strlen(argv[0]);
	if(len<=3){//"rm \0"
		printf("rm: Invalid instruction\n");
		exit(0);
	}

	for(int i=3;i<=(len-2);i++){
		if(argv[0][i]=='-'){
			if(argv[0][i+2]==' ' && argv[0][i-1]==' '){
				if(argv[0][i+1]=='i'){
					bit[0]=1;
					//break;
				}
				else if(argv[0][i+1]=='v'){
					bit[1]=1;
					//break;
				}
				else{

					printf("Invalid option\n");
					exit(0);
				}

			}
			else{
					printf("Invalid option\n");
					exit(0);

			}
		}
	}
	//printf("bit0:%d\n",bit[0]);
	//printf("bit1:%d\n",bit[1]);
	int p=2,p2=0;
	while(argv[0][p]!='\0'){
		//printf("p:%d\n",p);
		//printf("p2:%d\n",p);
		if(argv[0][p]!=' '){
			clear();
			//printf("t1\n");
			if (argv[0][p]=='/')
					{
						tok[j]='/';
						j++;
					}
			while(1){
				//printf("yo:p:%d\n",p);
				//printf("yo:p2:%d\n",p);
				if(argv[0][p]=='\"'){
					//printf("t3\n");
					p2=p+1;
					while(argv[0][p2]!='\"' && argv[0][p2]!='\0'){
						p2+=1;
					}
					extr(p,p2,argv[0]);
					if(argv[0][p2]=='\0')
					{
						printf("rm: double quote missing\n");
						exit(0);
					}
					if(argv[0][p2+1]==' '){
						//printf("ddd1111\n");
						break;
					}
					else if(argv[0][p2+1]=='/'){
						if(argv[0][p2+2]==' ' || argv[0][p2+2]=='\0'){
							//printf("ddd4444\n");
							break;
						}
						else{
							//printf("ddd333\n");
							p=p2+1;
							p2+=1;
							continue;

						}
					}
					else if(argv[0][p2+1]=='\0'){
						//printf("dd888\n");
						break;
					}
					else{//incorrect
						printf("rm: Invalid instruction\n");
						exit(0);
						
					}
				}
				else{
					
					//printf("t4\n");
					p2=p+1;
				
					while(argv[0][p2]!=' ' && argv[0][p2]!='\0' && argv[0][p2]!='/'){
						//printf("p222:%d\n",p2);
						p2+=1;
					}
					if(argv[0][p]=='/')
						extr(p,p2,argv[0]);
					else
						extr(p-1,p2,argv[0]);
					if(argv[0][p2]=='\0'){
						//printf("rrr4444\n");
						break;
					}
					if(argv[0][p2]==' '){
						//printf("rr11111\n");
						break;
					}
					if(argv[0][p2]=='/'){	
						if(argv[0][p2+1]==' ' || argv[0][p2+1]=='\0'){
							//printf("rr3333\n");
							break;
						}
						p=p2+1;
						p2+=1;
						//printf("p222:%d\n",p2);
					}
					//printf("q222:%d\n",p2);

				}

			}
			//p-=1;
			//printf("t5\n");
			//extr(p,p2,argv[0]);
			//printf("t6\n");
			f();
			//printf("t7\n");			
			if(argv[0][p2]=='\0')
				break;
			p=p2+1;
			p2+=1;
			//printf("t8\n");
		}
		else{
			//printf("t2\n");
			p+=1;

		}


	}
    //printf("outtttttt\n"); 	
return 0;
}
void extr(int p,int p2, char * buf){// extracts b/w p+1 and p2-1
	//printf("p:%d\n",p);
	//printf("p2:%d\n",p2);
	//printf("t888888\n");
	//printf("%s\n",buf);
	//printf("t999999999\n");
	

	
	for(int i=p+1;i<p2;i++,j++){
		tok[j]=buf[i];
	}
	tok[j]='/';
	j+=1;
	tok[j]='\0';
	//printf("33333\n");
	//printf("%s\n",tok);
	//printf("11111111\n");
}
void clear(){
for(int i=0;i<400;i++){
		tok[i]='\0';
	}
j=0;
}
void f(){
	tok[j-1]='\0';
	if(strlen(tok)>=2 && tok[0]=='-') 
		return ;
	if(bit[0]==1){
		//printf("1%s\n",tok);
		char yes='n';
		printf("rm: remove regular file '%s'?\n",tok);
		scanf("%c",&yes);
		char r;
		scanf("%c",&r);
		if(yes=='y')
		{	//printf("yesss\n");
			errno=-100;
			if(remove(tok)!=0){
				checkerrno("rm ");
				
			}
		}
	}
	else if(bit[1]==1){//v
		//printf("2%s\n",tok);
		if(remove(tok)!=0){
			checkerrno("rm ");
		}
		else{
			printf("removed '%s'\n",tok);

		}


	}
	else{
		//printf("3%s\n",tok);
		if(remove(tok)!=0) checkerrno("rm ");

	}


}

void checkerrno(char *msg){//
                if(errno!=-100)
                {
                    //printf("%s\n",strerror(errno));
                    perror(msg);
                   
                    	exit(EXIT_FAILURE);
                   
                    	//exit(EXIT_FAILURE);
                }
}
