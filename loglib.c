#include<string.h>
#include<stdlib.h>
#include "log.h"
char *message ;
char *filename="logfile.txt" ;
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
	fprintf(file, "%s", getlog()) ;
	fclose(file) ;
	return 0 ;
}
void set_x(char* value){
	char temp[100] ;
	x = atoi(value) ;
	log_data data ;
	strcpy(temp, get_time()) ;
	strcat(temp, "x = ") ;
	strcat(temp, value) ;
	strcat(temp, "\n") ;
	data.data_message = temp ;
	data.time = time(NULL) ;
	addmsg(data) ;
	savelog(filename) ;
}
void rename_file(char *re_name){
	log_data data ;
	data.data_message = (rename(filename, re_name) == 0)?"File name changed":"File Does not exist" ;
	data.time = time(NULL) ;
	filename = re_name ;
	addmsg(data) ;
	savelog(filename) ;
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
	time( &now ) ;
	timeinfo = localtime( &now ) ;
	return asctime(timeinfo) ;
}
