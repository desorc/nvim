#include <string>
#include "nlohmann/json.hpp"
#include "lib/parse-dir/parse_dir.h"

#define SEARCH_MAKE_SUCCESSFUL 0
#define SEARCH_MAKE_ERROR 1

struct search_files{
  std::string configure_ac;
  std::string configure;
};

void run__make(std::string command);
uint8_t search__make(nlohmann::json& js, ParseDir** makedir_out, std::string path);

void run_autoconf(nlohmann::json &command, ParseDir* makedir);
void run_configure(nlohmann::json &command, ParseDir* makedir);
void run_make(nlohmann::json &command, ParseDir* makedir);
void run_exe(nlohmann::json &command, ParseDir* makedir);
