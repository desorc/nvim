
#include <cstdint>
#include <string>

#ifndef PARSE_DIR
#define PARSE_DIR

// Status
#define DIR_SEARCH_SUCCESSFUL 0
#define DIR_SEARCH_ERROR 1
#define DIR_SEARCH_NONE 2

struct parsedir {
  std::string dir_my;
  std::string dir_search;

  uint8_t status_search;
  std::string file_name;
  std::string file_dir;
};

/* void dir_cut_identical(std::string* in_out_str, size_t pos_end); */

class ParseDir {
private:
  parsedir fd_dir;

  void dir_set_correct_data(std::string* in_out_str);

  uint8_t search_file(const char* path, const char* search_name);
  uint8_t search_file_recrucive(std::string* out_string, const std::string& path, const char* search_name);

  void parse_command(std::string command);

public:
  ParseDir(std::string path, std::string file_name);
  ~ParseDir();

  uint8_t search(std::string path, std::string file_name);
  static size_t dir_cut_end(std::string* in_out_str);

  const parsedir get_parsedir();
  static std::string get_dir_current();
};

#endif /* ifndef PARSE_DIR */
