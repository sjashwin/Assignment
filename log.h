#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
extern int x ; //Global x value.
extern FILE *file ;
extern char *filename, *code_file ;
typedef struct logging_message_structure{
	time_t time ;
	char *data_message ;
}log_data ;
int addmsg( log_data data ) ;
void clearlog( void ) ;
char *getlog( void ) ;
void set_x(char* value) ;
int rename_file(char* name, char *code_file) ;
void write_err_msg(char* msg, char *buggy_code) ;
char *get_time() ;

