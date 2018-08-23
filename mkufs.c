#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>


char *USE = "This is just a Test usage statement\nDon't use this software when this is printed !!!";

enum opt_boot {
	NOTSET = 0,
	NOBOOT = 1,
	UFSBOOT = 2
};

enum fs_type {
	NOFS = 0,
	SBFS
};


static struct option long_opts[] = {
	
	{"fs", required_argument, NULL, 'f'}, // Specifies fs type
	{"filesystem", required_argument, NULL, 'f'},
	
	{"bs", required_argument, NULL, 'b'}, // Specifies a bootsector file
	{"bootsector", required_argument, NULL, 'b'},

	{"ufsbl", no_argument, NULL, 'u'}, // Specifies that we should provide bootloader for the user
	{"ufsbootloader", no_argument, NULL, 'u'},

	{"noboot", no_argument, NULL, 'n'}, // Specifies no boot Signature and jmp $ 

	{"output", required_argument, NULL, 'o'}, // Specifies the output file

	{NULL, 0, NULL, 0}
};

static const char opt_string[] = "o:f:b:nu";

void usage();



int main(int argc, char **argv){
	
	int i;
	enum opt_boot optboot = NOTSET;
	enum fs_type fstype = NOFS;
	FILE *fdfsout, fdbootsector;
	struct stat stats;
	char *fsout = NULL, *bootsector = NULL, opt;
	
	opt ;
	
	while ((opt = getopt_long(argc, argv, opt_string, long_opts, NULL ) )!= -1){
		printf("opt:%c\n",opt);	
		switch(opt){
			case 'o':

				if (fsout == NULL){
					fsout = optarg;
				}else{
					error(0, 0, "You cant specify two output files at the same time");
					usage();
				}
				break;

			case 'b':

				if (bootsector == NULL && optboot == NOTSET){
					bootsector = optarg;
				}else{
					error(0, 0, "You cant specify two output files at the same time");
					usage();	
				}
				break;

			case 'f':

				if (fstype == NOFS){
					fstype = SBFS;
				}else{
					error(0, 0, "You cant specify two filesystemtypes at the same time");
					usage();
				}
				break;

			case 'u':

				if (optboot == NOTSET && bootsector == NULL){
					optboot = UFSBOOT;
				}else{
					error(0, 0,"You cant sepecify two bootloaders at the same time");
					usage();
				}
				break;
			
			case 'n':
				
				if (optboot == NOTSET && bootsector == NULL){
					optboot = NOBOOT;
				}else{
					error(0, 0,"You cant sepecify two bootloaders at the same time");
					usage();
				}
				break;	
			
			default:
				
				error(0, 0, "Does not support option <%c,%d>",opt,opt);
				usage();
		}
	}



	fdfsout = fopen(fsout,"rw");
	
	if (fdfsout == NULL){
		error(0,errno,"Cannot open File, %s",fsout);
		usage();
	}
	
	if (fstat(fileno(fdfsout), &stats) < 0){
		error(0,errno,"fstat() failed");
		usage();
		}



	fclose(fdfsout);


}


void usage(){
	printf("%s\n",USE);
	exit(-1);
}
