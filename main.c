#include<unistd.h>
#include "log.h"
log_data data ;
int c ;
int main( int argc, char **argv){
	opterr = 0 ;
	DIR *directory = opendir("./") ;
	struct dirent *ent ;
	if(directory != NULL){
		int found = 0 ;
		while((ent = readdir(directory))!= NULL){
			int length = strlen(ent->d_name) ;
			if(strncmp(ent->d_name+length-4, ".txt", 4) == 0)
				found++ ;
		}
		if(found == 0)
			set_x("42", argv[0]) ;
	}
	while((c = getopt(argc, argv, "hl:n:"))!=-1){
		switch(c){
		case 'h':
			printf("%s", "-h - Help\n-n - set the value of x\n-l - rename the logfile\n") ;
			break ;
		case 'n':
			set_x(optarg, argv[0]) ;
			break ;
		case 'l':
			rename_file(optarg, argv[0]) ;
			break ;
		case '?' :
			if(optopt == 'n'){
				errno = EINVAL ;
				set_x("42", argv[0]) ;
				perror("Option -c requires an argument, Default value 42 is logged.") ;
				write_err_msg("Option -c requires an argument to overrride default value", argv[0]) ;
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
