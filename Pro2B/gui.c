#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <fcntl.h>


int find_pid ( char* ProcName, int* Mypid)  
{  
        struct dirent   *d;  
        int             pid,plen;  
        char            *s;  
  		DIR             *dir;  

        *Mypid=0;
        plen = strlen(ProcName);  
   
        dir = opendir("/proc");  
        if (!dir)  
        {  
                printf("/proc open fails");  
                return -1;  
        }  
  
        /* search the directory. */  
        while ((d = readdir(dir)) != NULL) {  
  
                char exe [PATH_MAX+1];  
                char path[PATH_MAX+1];  
                int len;  
                int namelen;  
 
                if ((pid = atoi(d->d_name)) == 0)       continue;   
                if ((len = readlink(exe, path, PATH_MAX)) < 0)   continue;  
                path[len] = '\0';  
                s = strrchr(path, '/'); 
                if(s == NULL) continue;  
                s++;  
  				namelen = strlen(s);
                if(namelen < plen)     continue;  
                if(!strncmp(ProcName, s, namelen)) {  
                    if(s[namelen] == ' ' || s[namelen] == '\0')
                        *Mypid=*Mypid*10+pid;
                }  
        }  
        closedir(dir);  
        return  0;  
}  

int main(){
    int fd,Mypid;
    char file[20],str[50],sen[20];
    find_pid("block",&Mypid);
    sprintf(file,"/proc/%d/ctx",Mypid);
	sprintf(sen,"The pid of block is %d",Mypid);
    initscr();
    noecho();
	curs_set(0);
	keypad(stdscr,TRUE);

	while (1){
		fd=open(file,O_RDONLY);
		if (fd==0){
			printf("error to open: %s\n",file);
			exit(EXIT_FAILURE);
		}
		read(fd,(void *)str,sizeof(str));
		close(fd);
		mvprintw(LINES/2,(COLS-strlen(str))/2,str);
		mvprintw(LINES/2+1,(COLS-strlen(sen))/2,sen);
		refresh();

	}
    endwin();

    return 0;
}
