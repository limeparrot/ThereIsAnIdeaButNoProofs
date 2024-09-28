#ifdef _WIN32
#include <windows.h>
#endif
#include <clocale>
#include "clickhouse_manager.hpp"
#include "config.hpp"
#include "table_worker.hpp"

int main(int argc, const char **argv) {
#ifdef _WIN32
  system("chcp 65001");
#else
  setlocale(LC_ALL, "ru_RU.UTF-8");
#endif+
    if (argc != 2) {
        std::printf("Usage: %s <config_file_name>", argv[0]);
        return 0;
    }
    Config config(argv[1]);
    TableWorker tableWorker(config);
    const std::string table = "table_dataset1",emailName = "email";
    std::vector <std::wstring> clearMails = tableWorker.get_normalized_mails(table,emailName);
    for (const auto& mail : clearMails){
        std::wcout << mail << "\n";
    }
   // ClickhouseManager manager(config);
    //manager.run();
    //std::cout << config.get<int>("a", "a", 0) << '\n';
    return 0;
}
