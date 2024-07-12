#include "search/search.h"
#include "lib/parse-dir/parse_dir.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

void _run_exe(std::string command){
  const size_t buf_size = 2048;
  char buf[buf_size+1];
  FILE* file = popen(command.c_str(), "r");
  if(!file){
    perror("popen");
    return;
  }
  while(fgets(buf, buf_size, file) != NULL){
    std::cout << buf;
  }
  pclose(file);
}

void run__make(std::string command){
  const size_t buf_size = 2048;
  char buf[buf_size+1];
  FILE* file = popen(command.c_str(), "r");
  if(!file){
    perror("popen");
    return;
  }
  while(fgets(buf, buf_size, file) != NULL){
    std::cout << buf;
  }
  pclose(file);
}

std::string parse_json(const nlohmann::json& js, std::string str_parse){
  if(js.contains(str_parse)){
    return js[str_parse];
  }
  return std::string("");
}

uint8_t parse__make(nlohmann::json& command, const std::string &str){
  try {
    command = nlohmann::json::parse(str);
  }catch(...) {
    std::cout << "error format json\n";
    return SEARCH_MAKE_ERROR;
  }
  return SEARCH_MAKE_SUCCESSFUL;
}

uint8_t search__make(nlohmann::json& command, ParseDir** makedir_out, std::string path){
  size_t buf_size = 2048;
  char buf[buf_size];
  (*makedir_out) = new ParseDir(path, ".make.json");
  const parsedir parse_s = (*makedir_out)->get_parsedir();

  if(parse_s.status_search != DIR_SEARCH_SUCCESSFUL)
    return SEARCH_MAKE_ERROR;

  std::string str = parse_s.file_dir + std::string("/") + parse_s.file_name;
  FILE* file = fopen(str.c_str(), "r");

  if(!file)
    return SEARCH_MAKE_ERROR;

  size_t size = fread(buf, 1, buf_size, file);
  str = std::string(buf, size);

  if(parse__make(command, str) != SEARCH_MAKE_SUCCESSFUL)
    return SEARCH_MAKE_ERROR;
  return SEARCH_MAKE_SUCCESSFUL;
}

void run_autoconf(nlohmann::json &command, ParseDir* makedir){
  std::string run = parse_json(command, std::string("autoconf"));
  if(!run.length())
    return;
  run = std::string("cd ") + makedir->get_parsedir().file_dir + std::string(" && ") + run;
  run__make(run);
}

void run_type(nlohmann::json &command, ParseDir* makedir, std::string type_path, std::string type){
  std::string path_to = parse_json(command, type_path);
  std::string run = parse_json(command, type);
  if(!run.length())
    return;

  std::string file_dir = makedir->get_parsedir().file_dir;
  size_t file_dir_len = file_dir.length();

  if(!path_to.length() || path_to[0] != '/'){
    if(file_dir[file_dir_len-1] != '/')
      path_to = makedir->get_parsedir().file_dir + std::string("/") + path_to;
    else
      path_to = makedir->get_parsedir().file_dir + path_to;
  }

  struct stat st;
  if(stat(path_to.c_str(), &st) < 0)
    mkdir(path_to.c_str(), 0700);
  run = std::string("cd ") + path_to + std::string(" && ") + run;
  run__make(run);
}

void run_configure(nlohmann::json &command, ParseDir* makedir){
  run_type(command, makedir, std::string("configure_path"), std::string("configure"));
}

void run_make(nlohmann::json &command, ParseDir* makedir){
  run_type(command, makedir, std::string("make_path"), std::string("make"));
}

void run_exe(nlohmann::json &command, ParseDir* makedir){
  run_type(command, makedir, std::string("exe_path"), std::string("exe"));
}
