
#ifndef __UFS_H__
#define __UFS_H__

#include <stdint.h>

// Unified Filesystems 

typedef struct UFS_HEADER {

	uint32_t FS_TYPE;		// Filesystem Type
	uint32_t FS_VERSION;	// Filesystem Version
	uint64_t MAX_BYTES;		// Maximal Bytes on the disk if to large use 0x0 
	uint64_t LBA_FSH;		// Address of the Filesystem Header
	uint64_t LBA_B_FSH;		// Address of the Backup Filesystem Header
	uint64_t LBA_EB;		// Address of the Extended Bootsector
	uint64_t LBA_B_EB;		// Address of the Backup Extended Bootsector
	uint64_t CHECKSUM;		// Checksum xor all of the above

}__attribute__((packed)) ufs_h;

typedef enum fs_type {
	
	NONE = 0,
	SBFS
	
} fs_type;

#endif
