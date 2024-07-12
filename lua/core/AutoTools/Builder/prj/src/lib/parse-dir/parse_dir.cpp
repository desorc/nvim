
#include "lib/parse-dir/parse_dir.h"
#include <string>
#include <cstring>
#include <cstdint>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/limits.h>

void dir_cut_identical(std::string* in_out_str, size_t pos_end){
  pos_end--;
  while(pos_end > 0){
    if((*in_out_str)[pos_end] != '/')
      break;
    pos_end--;
  }
  in_out_str->resize(pos_end+1);
}

void ParseDir::dir_set_correct_data(std::string* in_out_str){
  if((*in_out_str)[0] != '/'){
    *in_out_str = fd_dir.dir_my + std::string("/") + *in_out_str;
  }
}

uint8_t ParseDir::search_file(const char* path, const char* search_name)
{
  struct dirent* dir;
  DIR* d;
  d = opendir(path);
  if (!d) {
    perror("opendir");
    return DIR_SEARCH_ERROR;
  }

  while (1) {
    dir = readdir(d);
    if (!dir)
      break;
    if (dir->d_type == DT_REG && !strcmp(dir->d_name, search_name)) {
      closedir(d);
      return DIR_SEARCH_SUCCESSFUL;
    }
  }

  closedir(d);
  return DIR_SEARCH_NONE;
}

size_t ParseDir::dir_cut_end(std::string* in_out_str){
  size_t pos = in_out_str->rfind("/");
  dir_cut_identical(in_out_str, pos);
  return pos;
}

uint8_t ParseDir::search_file_recrucive(std::string* out_string, const std::string &path, const char* search_name){
  uint8_t ret;
  *out_string = path;
  while (1) {
    ret = search_file(out_string->c_str(), search_name);
    if (ret == DIR_SEARCH_ERROR) {
      goto ret_none;
    } else if (ret == DIR_SEARCH_SUCCESSFUL)
      goto ret_suces;

    if(!dir_cut_end(out_string))
      goto ret_none;
  }

ret_none:
  ret = DIR_SEARCH_NONE;
  *out_string = std::string("");

ret_suces:
  return ret;
}


ParseDir::ParseDir(std::string path, std::string file_name)
{
  fd_dir.dir_my = get_dir_current();
  search(path, file_name);
}

ParseDir::~ParseDir()
{
}

uint8_t ParseDir::search(std::string path, std::string file_name)
{
  fd_dir.dir_search = path;
  fd_dir.file_name = file_name;

  dir_set_correct_data(&fd_dir.dir_search);
  uint8_t ret = search_file_recrucive(&fd_dir.file_dir, fd_dir.dir_search, fd_dir.file_name.c_str());
  fd_dir.status_search = ret;

  return ret;
}



const parsedir ParseDir::get_parsedir(){
  return fd_dir;
}

std::string ParseDir::get_dir_current(){
  char buf[PATH_MAX];
  if(!getcwd(buf, PATH_MAX)){
    perror("getcwd");
    exit(1);
  }
  return std::string(buf);
}
