#include<unistd.h>
#include<errno.h>
#include "log.h"
log_data data ;
int c ;
int main( int argc, char **argv){
	opterr = 0 ;
	while((c = getopt(argc, argv, "hl:n:"))!=-1){
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
				write_err_msg("Option -c requires an argument", argv[0]) ;
			}
			else if(optopt == 'l'){
				errno = EINVAL ;
				perror("Option -l requires an argument.") ;
				write_err_msg("Option -l requires an argument", argv[0]) ;
			}
			break ;
		}
	}
	return 0 ;
}
