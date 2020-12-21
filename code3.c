#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_RANGE_IN 200
void enableescape(char* a,char * des);
int lines(char * name);
int min(int a ,int b);
int updatehistory(char * in);
void removequotes(char * in2,char * withoutquotes,int off);
int readlast(char *in);
int rev(char * src,char * des);
int append(char* des, char *src);
int rem(char *des);
int mychdir(char * logicalbuf);
void checkerrno(char *msg);
void create();void destroy(int num);
void echocheck(char * words);
int checkenter(char * in);
void clear(char *b,int len);
char des[200],his[200],logicalbuf[400],withoutquotes[400],hisl[200],path[200],paths[5][200],hisname[]="historyl.txt";
char filenames[][200]={"myrm3","mydate","mycat","myls","mymkdir2"};


int main(){
	const ssize_t WORDS2SIZE=400;
	getcwd(logicalbuf,400);
	pid_t pid;
	int len;
	char s[100],in[MAX_RANGE_IN],exitcode[20],in2[MAX_RANGE_IN],in3[MAX_RANGE_IN],in4[MAX_RANGE_IN];
	int realexitcode=0;
	create();//int fopen("historyl.txt","r+");

	while(1){
		fgets(in, MAX_RANGE_IN-1, stdin);
		if(checkenter(in))
			continue;
		//======================update in ,removed \n from in ,in2
		strcpy(in2,in); 
		strcpy(in3,in2);
		char * first=strtok(in3," ");
		if(strcmp(first,"!!\n")==0){
			//printf("rl\n");			
			readlast(in);
		}
		else{
			updatehistory(in);
		}

		len=strlen(in);	
		in[len-1]='\0';
		strcpy(in2,in);	
		char* words=strtok(in," ");
		//============================
		//=====================internal command===============
		if(strcmp(words,"exit")==0){// exit number 
			
			 
			words=strtok(NULL," ");
			if(words==NULL){
				break;
			}
			if(strcmp(words,"--help")==0){
				printf("exit: exit [n]\r\n Exit the shell.\r\n\r\nExits the shell with a status of N.  If N is omitted, the exit status is that of the last command executed.\n");
				continue;
			}
			sprintf(exitcode,"%d",atoi(words));
			if(strcmp(words,exitcode)==0){
				realexitcode=atoi(words);
				break;
			}
			else{
				printf("exit: unknown %s\n",words);
			}
			

			
		}
		
		else if(strcmp(words,"cd")==0){
			int u;
		
			words=strtok(NULL," ");
			//printf("words:%s",words);
			if(NULL==words){
				u=mychdir("/home");
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,"/home");
						continue;

			}
				//printf("words:%s",words);
			if(strcmp(words,"/")==0){
				u=mychdir("/");
					//printf("%d\n",u);
					if(u==0){
						clear(logicalbuf,400);
						logicalbuf[0]='/';
							

						continue;
					}

			}
			
			removequotes( in2, withoutquotes,strlen("cd "));
			
			
			if(strcmp(words,"./")==0){
				//
			}
			else if(strcmp(words,"-L")==0){
				//words=strtok(NULL," ");
					words=strtok(NULL," ");
			if(NULL==words){
				u=mychdir("/home");
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,"/home");
						continue;

			}
				if(strcmp(withoutquotes,"..")==0){
					rem(logicalbuf);
					u=mychdir(logicalbuf);
				}
				else if(strcmp(withoutquotes,"~")==0){
				 	u=mychdir("/home");
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,"/home");
					
				}
				else{	
					u=mychdir(withoutquotes);
					if(u==0)
						append(logicalbuf,withoutquotes);
				}
			}
			else if(strcmp(words,"-P")==0){
					words=strtok(NULL," ");
			if(NULL==words){
				u=mychdir("/home");
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,"/home");
						continue;

			}
				 if(strcmp(withoutquotes,"..")==0){
				 	u=mychdir(withoutquotes);
				 	if(u==0)
						append(logicalbuf,getcwd(s,200));
					
				}
				else if(strcmp(withoutquotes,"~")==0){
				 	u=mychdir("/home");
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,"/home");
					
				}
				else{
					//printf("words1:%s\n",withoutquotes);
					u=mychdir(withoutquotes);
					if(u==0)
						append(logicalbuf,getcwd(s,200));
				}
			}
			else if(words[0]=='-'){
				printf("invalid option\n");

			}
			else{
				 if(strcmp(withoutquotes,"~")==0){
				 	u=mychdir("/home");
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,"/home");
					
				}
				 else if(strcmp(withoutquotes,"..")==0){
				 	rem(logicalbuf);
				 	//printf("logicalbuf%s\n",logicalbuf);
					u=mychdir(logicalbuf);
					
				}
				else{
					//printf("last:%s\n",withoutquotes);
					u=mychdir(withoutquotes);
					//printf("%d\n",u);
					if(u==0)
						append(logicalbuf,withoutquotes);
				}
			}
		}
		else if(strcmp(words,"pwd")==0){
			words=strtok(NULL," ");
			if(words==NULL){
				printf("%s\n",logicalbuf);
			}
			else if(strcmp(words,"-L")==0){
				printf("%s\n",logicalbuf);

			}
			else if(strcmp(words,"-P")==0){
				errno=-100;
				printf("%s\n",getcwd(s,200));
				checkerrno("pwd ");
				
			}
			else if(words[0]=='-' && strlen(words)==2){
				printf("Invalid option \n");

			}
			else{
				printf("inconsistent arguments\n");

			}
		}
		else if(strcmp(words,"echo")==0){//
			
			words=strtok(NULL," ");

			removequotes( in2, withoutquotes,strlen("echo "));
			echocheck(words);
			if(words==NULL)
			{

				printf("\n");	
			}
			 else if(strcmp(words,"-n")==0){
				//printf("33:\n");
					words=strtok(NULL," ");
					echocheck(words);
				printf("%s",withoutquotes);		
			
			}
			else if(strcmp(words,"-e")==0){
					words=strtok(NULL," ");
					echocheck(words);
					enableescape(withoutquotes,des);
					//printf("len:%ld",strlen(des));
					//strcpy(a,words);
					printf(des);
					//printf("%s ",words);
					printf("\n");
					//int len2=strlen(words);
				
				
			}
			else if(words[0]=='-' && strlen(words)==2){
				printf("Invalid option \n");

			}
			else{
				//printf("11:\n");
				printf(withoutquotes);
				//printf("%s ",words);
				printf("\n");
			}
		}
		else if(strcmp(words,"history")==0){
			//history 5 will give last 5 entries
			//!! gives last entered command in this shell (on line 25)
			int howmany=1000;
			//printf("asdfds\n");
			words=strtok(NULL," ");
			//printf("words:%s\n",words);
			
			 if(words!=NULL && strcmp(words,"-s")==0){
					removequotes( in2, withoutquotes,strlen("history "));
					int len=strlen(withoutquotes);
					withoutquotes[len]='\n';
					withoutquotes[len+1]='\0';
					//printf("withoutquotes:%s\n",withoutquotes);
					updatehistory(withoutquotes);

			}
			else if(words!=NULL && strcmp(words,"-w")==0){
					destroy(1);

			}
			else if(words!=NULL && words[0]=='-'){
					printf("Invalid option \n");

			}
			else{
				if(words!=NULL){
					howmany=atoi(words);
				}
				//printf("howmany:%d\n",howmany);
				FILE * u;
				int co=1;
				errno=-100;
				//u=fopen("/home/utkrishtsikka/.bash_history","r");
				u=fopen(path,"r");
				checkerrno("history ");
				//int len=lines("/home/utkrishtsikka/.bash_history");
				int len=lines(path);
				//printf("len:%d\n",len);
				for(int i=0;i<(len-howmany);i++){
					fgets(his,199,u);
					co+=1;
				}
				for(int i=0;i<min(howmany,len);i++){
					fgets(his,199,u);
					printf("%d  %s",co,his);
					co+=1;
				}
				fclose(u);
			}
		}
		//=====================external command===============
		else if(strcmp(words,"date")==0){
			pid=fork();
			if(pid<0){
				fprintf(stderr,"Fork Failed");

			}
			else if(pid==0){
				
					execl(paths[1],in2,NULL);//"/home/utkrishtsikka/Documents/myddrive/c_c++/mycmd/mydate",in2,NULL);
				}
			else{
				//printf("waiting\n");
				//wait(NULL);
				wait(&realexitcode);
				checkerrno("shell: ");
				//shouldexit(realexitcode);
			
				//printf("child com\n");
				//printf("%d\n",realexitcode);

			}
		}
		else if(strcmp(words,"rm")==0){
			pid=fork();
			if(pid<0){
				fprintf(stderr,"Fork Failed");

			}
			else if(pid==0){
				
					execl(paths[0],in2,NULL);//"/home/utkrishtsikka/Documents/myddrive/c_c++/mycmd/myrm3",in2,NULL);
				}

			
			else{
				//printf("waiting\n");
				//wait(NULL);
				wait(&realexitcode);
				checkerrno("shell: ");
				//shouldexit(realexitcode);
			
				//printf("child com\n");
				//printf("%d\n",realexitcode);
			}
		}
		else if(strcmp(words,"mkdir")==0){
			pid=fork();
			if(pid<0){
				fprintf(stderr,"Fork Failed");

			}
			else if(pid==0){
				
					execl(paths[4],in2,NULL);//"/home/utkrishtsikka/Documents/myddrive/c_c++/mycmd/mymkdir2",in2,NULL);
				}

			
			else{
				
				wait(&realexitcode);
				checkerrno("shell: ");
				//shouldexit(realexitcode);
				

			}
		}
		else if(strcmp(words,"ls")==0){
			//printf("asdq%d\n",EXIT_FAILURE);
			pid=fork();
			if(pid<0){
				fprintf(stderr,"Fork Failed");

			}
			else if(pid==0){
				
					execl(paths[3],in2,NULL);//"/home/utkrishtsikka/Documents/myddrive/c_c++/mycmd/myls",in2,NULL);
				}

			
			else{
				
				wait(&realexitcode);
				checkerrno("shell: ");
				//shouldexit(realexitcode);
			
				

			}
		}
		else if(strcmp(words,"cat")==0){
			pid=fork();
			if(pid<0){
				fprintf(stderr,"Fork Failed");

			}
			else if(pid==0){
				
					execl(paths[2],in2,NULL);//"/home/utkrishtsikka/Documents/myddrive/c_c++/mycmd/mycat",in2,NULL);
				}

			
			else{
				wait(&realexitcode);
				checkerrno("shell: ");
				//shouldexit(realexitcode);
			


			}
		}
		else{
			//printf("words:%s\n",words);
			//printf("in:%s\n",in);
			printf("Unknown command\n");
		}


	}
	destroy(0);
	return realexitcode;
}


int lines(char * name){
	FILE *w;
	errno=-100;
	w=fopen(name,"r");
	checkerrno("history:error in no. of lines count ");
	
	char ch;
	int co=0;
	for(ch=getc(w);ch!=EOF;ch=getc(w)){
		if(ch=='\n'){
			co+=1;
		}
	}
	fclose(w);
	return co;
}

void enableescape(char * a,char * des){

	int len=strlen(a);
	int desj=0,i=0;
	for( i=0,desj=0;i<len;i++,desj++){
		if(a[i]=='\\'){
			switch(a[i+1]){
				case '\\':

				break;
				case 'a':
				des[desj]='\a';
				i++;
				break;
				case 'b':
				des[desj]='\b';
				i++;
				break;
				case 'e':
				des[desj]='\e';
				i++;
				break;
				case 'f':
				des[desj]='\f';
				i++;
				break;
				case 'n':
				des[desj]='\n';
				i++;
				break;
				case 'r':
				des[desj]='\r';
				i++;
				break;
				case 't':
				des[desj]='\t';
				i++;
				break;
				case 'v':
				des[desj]='\v';
				i++;
				break;



			}

		}
		else{
			des[desj]=a[i];
		}

	}
	des[desj]='\0';
}

int min(int a ,int b){
	if(a<b)
		return a;
	return b;

}

int updatehistory(char * in){
	errno=-100;
	FILE *u=fopen(path,"a");
	checkerrno("history updation ");
	fprintf(u, "%s", in); 
	fclose(u);
}

int rev(char * src,char * des){
	int len=strlen(src);
	//printf("len:%d",len);
	//printf("src:%s",src);
	int p=0;
	for(int i=len-1;i>=0;p++,i--){
		des[p]=src[i];
	}
	des[p]='\0';
}

int readlast(char  * in){
	int p=1;
	errno=-100;
	FILE *u=fopen(path,"r");
	checkerrno("history ");
	fseek(u,-1,SEEK_END);
	char c[0];
	//char* in=(char *)malloc(100*sizeof(char));
	int co=0;
	fseek(u,-2,SEEK_CUR);
	c[0]=(char)fgetc(u);
	while(1){
		c[0]=(char)fgetc(u);
		if(c[0]=='\n')
			break;
		in[p]=c[0];p++;
		fseek(u,-2,SEEK_CUR);
		co+=1;
	}
	in[0]='\n';
	in[p]='\0';
	//printf("co:%d\n",co);
	char *des=(char*)malloc(sizeof(char)*100);
	rev(in,des);
	strcpy(in,des);
	printf("%s",in);
	fclose(u);
}
int append(char* des, char *src){
	int l=strlen(des);
	if(src[0]=='/' && src[1]=='h' && src[2]=='o' && src[3]=='m' && src[4]=='e')
	{	
		des[l]='/';
		des[l+1]='\0';
		strcpy(des,src);
		return 0;
	}
	if(l==1 && des[0]=='/'){
		des[0]='\0';

	}
	int u=strlen(src);
	des[l]='/';
	l+=1;
	for(int i=0;i<u;i++,l++){
		des[l]=src[i];
	}
	des[l]='\0';
	return 0;
}

int rem(char *des){
	int l=strlen(des);
	while(des[l]!='/'){
		des[l]='\0';
		l--;
	}
	des[l]='\0';
	if(l==0){
		des[l]='/';
		des[l+1]='\0';
	}

	return 0;
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
int mychdir(char * logicalbuf){
	errno=-100;
	int u=chdir(logicalbuf);
	if(errno!=-100)
		{
			printf("%s\n",strerror(errno));
		//exit(EXIT_FAILURE);
	}
	return u;

}

void checkerrno(char *msg){
					if(errno!=-100)
				{
					//printf("%s\n",strerror(errno));
					perror(msg);
					//exit(EXIT_FAILURE);
				}
}
/*void shouldexit(int realexitcode){//a=1 then exit
	//printf("about to\n");
	//printf("%d\n",realexitcode);
	//printf("%d\n",EXIT_FAILURE);
				if(realexitcode==256){

					//printf("exiting\n");
					exit(EXIT_FAILURE);
				}

				
}*/
void echocheck(char * words){

if(words!=NULL && words[0]=='>')
			{
				printf("%s\n","Redirection Functionality not supported");		
				//exit(EXIT_FAILURE);
			}
	}

int checkenter(char * in){
	if(in[0]=='\n'){
		printf("%s\n","Specify an argument");
		return 1;
	}
	return 0;
}

void clear(char *b,int len){
	for(int i=0;i<len;i++)
		b[i]='\0';
}

void create(){
	getcwd(path,200);
	
	int l=strlen(path);
	path[l]='/';
	l+=1;
	int p=0;

	while(hisname[p]!='\0'){
		path[l]=hisname[p];
		l++;p++;

	}
	path[l]='\0';

	for(int i=0;i<5;i++){
		getcwd(paths[i],200);
		int l=strlen(paths[i]);
		paths[i][l]='/';
		l+=1;
		int p=0;

		while(hisname[p]!='\0'){
			paths[i][l]=filenames[i][p];
			l++;p++;

		}
		paths[i][l]='\0';
		//printf("paths:%s\n",paths[i]);
	}




	//printf("path:%s\n",path);
	FILE *u=fopen(path,"w+");
	if(u==NULL){
		printf("error u create\n");


	}
	FILE *u2=fopen("/home/utkrishtsikka/.bash_history","r");
	if(u2==NULL){
		printf("error u2 create\n");


	}
	while(fgets(hisl,199,u2)!=NULL){
		fprintf(u,"%s",hisl);

	}
	fclose(u);
	fclose(u2);
}

void destroy(int num){
	FILE *u=fopen(path,"r");
	if(u==NULL){
		printf("error u destroy\n");

	}
	FILE *u2=fopen("/home/utkrishtsikka/.bash_history","w");
	if(u2==NULL){
		printf("error u2 destroy\n");


	}
	while(fgets(hisl,199,u)){
		fprintf(u2,"%s",hisl);

	}
	fclose(u);
	fclose(u2);
	//printf("path:%s",path);
	if(num==0)
	remove(path);
}

	