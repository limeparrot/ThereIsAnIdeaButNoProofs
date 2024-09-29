#ifdef _WIN32
#include <windows.h>
#endif
#include <clocale>
#include "config.hpp"
#include <thread>
#include "table_worker.hpp"
#include "internal_structs.h"
#include "csv_worker.h"

void clear_dataset1(const Config &config){
    TableWorker tableWorker(config);
    const std::string tableDataset1 = "table_dataset1";
    auto csv = config.get<std::string>("files","csv1","text.txt");
    if (!file_exists(csv)){
        write_dataset12(csv,"uid","full_name","email","address","sex","birthdate","phone");
    }
    std::vector <TableDataset1Data> data = tableWorker.get_normalazied_dataset1(tableDataset1);
    for (const auto& [uid,fullName,email,address,sex,birthdate,phone] : data){
        write_dataset12(csv,uid,fullName,email,address,sex,birthdate,phone);
    }
}

void clear_datataset2(const Config &config){
    TableWorker tableWorker(config);
    const std::string tableDataset2 = "table_dataset2";
    std::vector <TableDataset2Data> data = tableWorker.get_normalalized_dataset2(tableDataset2);
    auto csv = config.get<std::string>("files","csv2","text.txt");
    if (!file_exists(csv)){
        write_dataset12(csv,"uid","first_name","middle_name","last_name","birthdate","phone","address");
    }
    for (const auto& [uid,first_name,middle_name,last_name,birthdate,phone,address] : data){
        write_dataset12(csv,uid,first_name,middle_name,last_name,birthdate,phone,address);
    }
}

void clear_dataset3(const Config &config){
    TableWorker tableWorker(config);
    const std::string tableDataset3 = "table_dataset3";
    auto csv = config.get<std::string>("files","csv3","text.txt");
    if (!file_exists(csv)){
        write_dataset3(csv,"uid","name","email","birthdate","sex");
    }
    std::vector <TableDataset3Data> data = tableWorker.get_normalazied_dataset3(tableDataset3);
    for (const auto& [uid,name,email,birthdate,sex] : data){
        write_dataset3(csv,uid,name,email,birthdate,sex);
    }
}

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
    double start = clock();
    Config config(argv[1]);
    std::thread threadDataset1(clear_dataset1,config);
    std::thread threadDataset2(clear_datataset2,config);
    std::thread threadDataset3(clear_dataset3,config);
    threadDataset1.join();
    threadDataset2.join();
    threadDataset3.join();
    printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
