./file -h - is help.
./file -n x - will set the value of x.
./file -l - will rename the logfile.txt or any existing .txt file.

-n without an argument will log 42 as a default value but still show and error:
	missing argument.

-l without an argument will show an error : missing argument.
-l argument without .txt extension will show an error: to enter the argument
	with a .txt extension.

-h data will not be logged but will print the data in the terminal console.

logging format : 
	bugg_code: time: error: error message.

Only one file with .txt extension should exist in the curretn directory.

use make to compile the c programs and generate an executable.
make clean will remove the executable and files with extension .txt if any 
exist.
