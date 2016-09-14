#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
extern int x ; //Global x value.
extern FILE *file ;
extern char *filename ;
typedef struct logging_message_structure{
	time_t time ;
	char *data_message ;
}log_data ;
int addmsg( log_data data ) ;
void clearlog( void ) ;
char *getlog( void ) ;
int log_( char *filename ) ;
void set_x(char* value) ;
void rename_file(char* name) ;
void write_err_msg(char* msg) ;
char *get_time() ;

