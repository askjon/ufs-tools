#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>


#include "ufs.h"
#include "sbfs.h"
#include "mkufs.h"
#include "usage.h"
#include "constant.h"







int main(int argc, char **argv){
	
	int i;
	uint8_t buffer[MAX_BUFFER];
	size_t read = 0;
	enum opt_boot boot = NOTSET;
	enum fs_type fstype = NONE;
	FILE *fdfsout, *fdbootsector, *fdkernelimage;
	struct stat stats;
	char *fsout = NULL, *bootsector = NULL, *filesystem = NULL, *kernel = NULL, opt;
	
	
	while ((opt = getopt_long(argc, argv, opt_string, long_opts, NULL ) )!= -1){	
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

				if (boot == NOTSET){
					boot = CUSTOM_BOOTSECTOR;
					bootsector = optarg;
					
				}else{
					error(0, 0, "You cant specify two output files at the same time");
					usage();	
				}
				break;

			case 'f':

				if (filesystem == NULL){
					filesystem = optarg;
				}else{
					error(0, 0, "You cant specify two filesystemtypes at the same time");
					usage();
				}
				break;

			case 'u':

				if (boot == NOTSET){
					boot = UFSBOOT;
				}else{
					error(0, 0,"You cant sepecify two bootloaders at the same time");
					usage();
				}
				break;
			
			case 'n':
				
				if (boot == NOTSET){
					boot = NOBOOT;
				}else{
					error(0, 0,"You cant sepecify two bootloaders at the same time");
					usage();
				}
				break;	
			case 'k':
				
				if (kernel == NULL){
					kernel = optarg;
				}else {
					error(0, 0, "You cant specify two kernels");
					usage();
				}
				break;

			case '?':
				printf("What happened ? %s\n",optarg);
				usage();
				

			default:
				
				error(0, 0, "Does not support option <%c,%d>",opt,opt);
				usage();
		}
	}

	while (optind < argc){
		if (fsout == NULL){
			fsout = argv[optind];
		}else if (kernel == NULL){
			kernel = argv[optind];
		}else {
			usage();	
		}
		optind++;
	}

	printf("You are creating a filesystem with the following Parameters:\n");
	printf("Filesystem:<%s>\nBoot Behavior:<%d>\nKernel:<%s>\nInto the file:<%s>\n",filesystem,boot,kernel,fsout);

	
	if (boot == NOTSET)
		boot = NOBOOT;
	if (fsout == NULL)
		usage();
	if (kernel == NULL)
		usage();
	if (bootsector == NULL && boot != NOBOOT)
		usage();
		


	fdfsout = fopen(fsout,"w");
	if (fdfsout == NULL){
		error(0,errno,"Cannot open File, %s",fsout);
		usage();
	}
	
	
	if (boot == NOBOOT){
		fwrite(&noboot,1,8,fdfsout);
		
	}else if(boot == CUSTOM_BOOTSECTOR){
		
		fdbootsector = fopen(bootsector,"r");
		if (fdbootsector == NULL){
			error(0, errno,"Cannot open File, %s",bootsector);
			usage();
		}
		while (!feof(fdbootsector)){
			
			read = fread(buffer, 1, MAX_BUFFER -1, fdbootsector);
			fwrite(buffer, 1, read, fdfsout);

		}
		fclose(fdbootsector);
		
	}else{
		usage();	
	}



	fclose(fdfsout);
 

}

