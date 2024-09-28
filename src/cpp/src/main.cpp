#ifdef _WIN32
#include <windows.h>
#endif
#include <clocale>

#include "clickhouse_manager.hpp"
#include "config.hpp"

int main(int argc, const char **argv) {
#ifdef _WIN32
  system("chcp 65001");
#else
  setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
  if (argc != 2) {
    std::printf("Usage: %s <config_file_name>", argv[0]);
    return 0;
  }
  Config config(argv[1]);
  ClickhouseManager manager(config);
  manager.run();
  return 0;
}