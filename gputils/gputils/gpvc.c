/* Displays contents of ".COD" files
   Copyright (C) 2001, 2002, 2003, 2004, 2005
   Scott Dattalo

    Copyright (C) 2016 Molnar Karoly <molnarkaroly@users.sf.net>

This file is part of gputils.

gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "stdhdr.h"

#include "libgputils.h"
#include "gpvc.h"
#include "dump.h"
#include "block.h"

FILE         *codefile;
char         *source_file_names[MAX_SOURCE_FILES];
DirBlockInfo *main_dir = NULL;

static char filename[BUFFER_LENGTH];

#define GET_OPTIONS         "adhlmrsv"

/* Used: adhlmrsv */
static struct option longopts[] =
{
  { "all",       no_argument, NULL, 'a' },
  { "directory", no_argument, NULL, 'd' },
  { "help",      no_argument, NULL, 'h' },
  { "listing",   no_argument, NULL, 'l' },
  { "message",   no_argument, NULL, 'm' },
  { "rom",       no_argument, NULL, 'r' },
  { "symbols",   no_argument, NULL, 's' },
  { "version",   no_argument, NULL, 'v' },
  { NULL,        no_argument, NULL, '\0'}
};

/*------------------------------------------------------------------------------------------------*/

static void
_show_usage(void)
{
  printf("Usage: gpvc [options] file\n");
  printf("Options: [defaults in brackets after descriptions]\n");
  printf("  -a, --all          Display all information in .cod file.\n");
  printf("  -d, --directory    Display directory header.\n");
  printf("  -l, --listing      Display source listing.\n");
  printf("  -m, --message      Display debug message area.\n");
  printf("  -h, --help         Show this usage message.\n");
  printf("  -r, --rom          Display rom.\n");
  printf("  -s, --symbols      Display symbols.\n");
  printf("  -v, --version      Show version.\n\n");
  printf("Report bugs to:\n");
  printf("%s\n", PACKAGE_BUGREPORT);
  exit(0);
}

/*------------------------------------------------------------------------------------------------*/

int
main(int argc, char *argv[])
{
  int              c;
  gp_boolean       usage = false;
  int              display_flags;

  char             temp_buf[12];
  char            *processor_name;
  pic_processor_t  processor_info;
  proc_class_t     processor_class;

  gp_init();

#define DISPLAY_NOTHING 0
#define DISPLAY_DIR     1
#define DISPLAY_SYM     2
#define DISPLAY_ROM     4
#define DISPLAY_SRC     8
#define DISPLAY_MESS    16
#define DISPLAY_ALL     0xff

  display_flags = DISPLAY_NOTHING;
  while ((c = getopt_long(argc, argv, GET_OPTIONS, longopts, NULL)) != EOF) {
    switch (c) {
    case '?':
    case 'h':
      usage = true;
      break;

    case 'a':
      display_flags = DISPLAY_ALL;
      break;

    case 'd':
      display_flags |= DISPLAY_DIR;
      break;

    case 's':
      display_flags |= DISPLAY_SYM;
      break;

    case 'r':
      display_flags |= DISPLAY_ROM;
      break;

    case 'l':
      display_flags |= DISPLAY_SRC;
      break;

    case 'm':
      display_flags |= DISPLAY_MESS;
      break;

    case 'v':
      fprintf(stderr, "%s\n", GPVC_VERSION_STRING);
      exit(0);
    }

    if (usage) {
      break;
    }
  }

  if ((optind + 1) == argc) {
    strncpy(filename, argv[optind], sizeof(filename));
  }
  else {
    usage = 1;
  }

  if (display_flags == DISPLAY_NOTHING) {
    display_flags = DISPLAY_ALL;
  }

  if (usage) {
    _show_usage();
  }

  codefile = fopen(filename,"rb");
  if (codefile == NULL) {
    perror(filename);
    exit(1);
  }

  /* Start off by reading the directory block */
  main_dir = read_directory();

  /* Determine if byte address and org are different */
  processor_name = substr(temp_buf,
                          sizeof(temp_buf),
                          &main_dir->dir[COD_DIR_PROCESSOR],
                          8);

  processor_info = gp_find_processor(processor_name);
  processor_class = gp_processor_class(processor_info);

  if (display_flags & DISPLAY_DIR) {
    dump_directory_blocks();
  }

  if (display_flags & DISPLAY_ROM) {
    dump_code(processor_class);
  }

  if (display_flags & DISPLAY_SYM) {
    dump_symbols();
    dump_lsymbols();
    dump_local_vars(processor_class);
  }

  dump_source_files();

  if (display_flags & DISPLAY_SRC) {
    dump_line_symbols();
  }

  if (display_flags & DISPLAY_MESS) {
    dump_message_area();
  }

  return EXIT_SUCCESS;
}
