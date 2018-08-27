#ifndef __MKUFS_H__
#define __MKUfs_H__

struct fs_option {
	
	char *matcher;
	uint16_t ufs_fstype;
	uint16_t ufs_fsversion;

};

enum opt_boot {
	NOTSET = 0,
	NOBOOT,
	CUSTOM_BOOTSECTOR,
	UFSBOOT,
};



#endif
