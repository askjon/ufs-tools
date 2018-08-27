#include <unistd.h>
#include <getopt.h>
#include <stdint.h>

#include "mkufs.h"

const char *USE = 
    "mkufs -o [Outputfile] -f [Filesystem Name] [Inputfiles] \n"
        "\t\t-o, --output [Outputfile]\n"
        "\t\t-f, --fs, --filesystem [sbfs,no other atm]\n"
        "\t\t-b, --bs, --bootsector [Path to Bootsector]\n"
        "\t\t-u, --ufsbl, --ufsbootloader\n"
        "\t\t-n, --noboot\n";



const struct option long_opts[] = {

    {"fs", required_argument, NULL, 'f'}, // Specifies fs type
    {"filesystem", required_argument, NULL, 'f'},

    {"bs", required_argument, NULL, 'b'}, // Specifies a bootsector file
    {"bootsector", required_argument, NULL, 'b'},

    {"ufsbl", no_argument, NULL, 'u'}, // Specifies that we should provide bootloader for the user
    {"ufsbootloader", no_argument, NULL, 'u'},

    {"noboot", no_argument, NULL, 'n'}, // Specifies no boot Signature and jmp $ 

    {"output", required_argument, NULL, 'o'}, // Specifies the output file

	{"kernel", required_argument, NULL, 'k'},

	{NULL, 0, NULL, 0}
};

const char opt_string[] = "o:f:b:k:nu";

const uint8_t noboot[] = {0xeb,0xfe,0x90,0x90,0x90,0x90,0x90,0x90};


