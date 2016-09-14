#include<string.h>
#include<stdlib.h>
#include "log.h"
char *message, *filename ;
int x ;
FILE *file ;
typedef struct list{
	log_data item ;
	struct list *next ;
}log_list ;
static log_list root ;
static log_list *headptr = &root ;
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
void set_x(char* value){
	char temp[100] ;
	x = atoi(value) ;
	log_data data ;
	strcpy(temp, "\nx = ") ;
	strcat(temp, value) ;
	data.data_message = temp ;
	data.time = time(NULL) ;
	addmsg(data) ;
	savelog(filename) ;
}
void rename_file(char *re_name){
	printf("%d", rename(filename, re_name)) ;
	filename = re_name ;
	log_data data ;
	data.data_message = "file name changed" ;
	data.time = time(NULL) ;
	addmsg(data) ;
	savelog(filename) ;
}
void write_err_msg(char* msg){
	log_data data ;
	char temp[100] ;
	strcpy(temp, "\nError Message : ");
	strcat(temp, msg) ;
	printf("%s", get_time()) ;
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
