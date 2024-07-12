#include "lib/parse-dir/parse_dir.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>


#include "search/search.h"
#include "nlohmann/json.hpp"
#include "lib/parse-dir/parse_dir.h"

using namespace std;
using namespace nlohmann;

int main(int argc, char *argv[])
{
  if(argc < 2)
    return 1;

  uint8_t run = 0;
  json command;
  ParseDir *makedir;
  if(search__make(command, &makedir, "") != SEARCH_MAKE_SUCCESSFUL){
    cout << "error search .make.json";
    delete makedir;
    return 1;
  }

#define COMMAND_EXE 0x08
#define COMMAND_AUTOCONF 0x04
#define COMMAND_CONFIGURE 0x02
#define COMMAND_MAKE 0x01

  if(!strcmp(argv[1], "autoconf"))
    run = COMMAND_AUTOCONF | COMMAND_CONFIGURE | COMMAND_MAKE;
  else if(!strcmp(argv[1], "configure"))
    run = COMMAND_CONFIGURE | COMMAND_MAKE;
  else if(!strcmp(argv[1], "make"))
    run = COMMAND_MAKE;
  else if(!strcmp(argv[1], "exe"))
    run = COMMAND_EXE;

  if((run & COMMAND_AUTOCONF) == COMMAND_AUTOCONF)
    run_autoconf(command, makedir);
  if((run & COMMAND_CONFIGURE) == COMMAND_CONFIGURE)
    run_configure(command, makedir);
  if((run & COMMAND_MAKE) == COMMAND_MAKE)
    run_make(command, makedir);
  if((run & COMMAND_EXE) == COMMAND_EXE)
    run_exe(command, makedir);

  delete makedir;
  return 0;
}
