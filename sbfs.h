#include <stdint.h>
#ifndef __SBFS_H__
#define __SBFS_H__


typedef struct SBFS_HEADER {
	
	uint8_t drive_number;
	uint8_t blocksize;  

}__attribute__((packed)) sbfs_h;

#endif
