#include<unistd.h>
#include<errno.h>
#include "log.h"
log_data data ;
char *filename = "logfile.txt" ; //default file name.
int c ;
int main( int argc, char **argv){
	opterr = 0 ;
	while((c = getopt(argc, argv, "thn:x:"))!=-1){
		switch(c){
		case 'h':
			printf("%s", "-h - Help\n-n - set the value of x\n-l - rename the logfile\n") ;
			break ;
		case 'n':
			set_x(optarg) ;
			break ;
		case 'l':
			rename_file(optarg) ;
			break ;
		case '?' :
			if(optopt == 'n'){
				errno = EINVAL ;
				perror("Option -c requires an argument.") ;
				write_err_msg("Option -c requires an argument") ;
			}
			else if(optopt == 'l'){
				errno = EINVAL ;
				perror("Option -l requires an argument.") ;
				write_err_msg("Option -l requires an argument") ;
			}
			break ;
		}
	}
	return 0 ;
}
