#include<stdlib.h>
#include "log.h"
char *message ;
char *filename = "logfile.txt" ;
int x = 42 ;
FILE *file ;
typedef struct list{
	log_data item ;
	struct list *next ;
}log_list ;
static log_list root ;
static log_list *tailptr = &root ;
int addmsg(log_data data){
	log_list new_log ;
	new_log.item = data ;
	new_log.next = NULL ;
	tailptr->next = &new_log ;
	tailptr = tailptr->next ;
	return 0 ;
}
char *getlog(void){
	message = (char *)malloc(sizeof(char)*100) ;
	strcpy(message, get_time(tailptr->item.time)) ;
	strcat(message, tailptr->item.data_message) ;
	return message ;
}
int savelog(char *file_name){
	file = fopen(file_name, "a+") ;
	fprintf(file, "%s\n", getlog()) ;
	fclose(file) ;
	return 0 ;
}
void set_x(char* value, char* buggy_code){
	char temp[100] ;
	x = atoi(value) ;
	log_data data ;
	strcpy(temp, buggy_code) ;
	strcat(temp, ": ") ;
	strcat(temp, get_time()) ;
	strcat(temp, ":x = ") ;
	strcat(temp, value) ;
	strcat(temp, "\n") ;
	data.data_message = temp ;
	data.time = time(NULL) ;
	addmsg(data) ;
	savelog(filename) ;
}
int rename_file(char *re_name, char *code_file){
	log_data data ;
	DIR *directory = opendir("./") ;
	struct dirent *ent ;
	if(directory != NULL){
		while((ent = readdir(directory))!=NULL){
			int length = strlen(ent->d_name) ;
			if(strncmp(ent->d_name+length-4, ".txt", 4) == 0){
				filename = ent->d_name ;
			}
		}
	}
	if(strncmp(re_name+strlen(re_name)-4, ".txt", 4)!=0){
		write_err_msg((char *)"Enter filename with extension .txt", code_file);
		errno = EINVAL ;
		perror("Enter filename with extension .txt") ;
		return 1 ;
	}
	data.data_message = (rename(filename, re_name) == 0)?" File name changed":" Error :File Does not exist" ;
	data.time = time(NULL) ;
	filename = re_name ;
	addmsg(data) ;
	savelog(filename) ;
	return 0 ;
}
void write_err_msg(char* msg, char *buggy_code){
	log_data data ;
	char temp[100] ;
	strcpy(temp, buggy_code) ;
	strcat(temp, ": ") ;
	strcat(temp, get_time()) ;
	strcat(temp, ": Error :") ;
	strcat(temp, msg) ;
	data.data_message = temp ;
	data.time = time(NULL) ;
	addmsg(data) ;
	savelog(filename) ;
}
char *get_time(time_t now){
	struct tm *timeinfo ;
	char *temp;
	time( &now ) ;
	timeinfo = localtime( &now ) ;
	temp = asctime(timeinfo) ;
	temp[strlen(temp)-2] = '\0' ;
	return temp ;
}
