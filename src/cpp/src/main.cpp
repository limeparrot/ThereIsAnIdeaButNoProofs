#ifdef _WIN32
#include <windows.h>
#endif
#include <clocale>
#include "config.hpp"
#include <thread>
#include "table_worker.hpp"
#include "internal_structs.h"

void clear_dataset1(const Config &config){
    TableWorker tableWorker(config);
    const std::string tableDataset1 = "table_dataset1";
    const std::string emailColumn = "email";
    const std::string phoneColumn = "phone";
    const std::string FIOColumn = "full_name";
    std::vector <TableDataset1Data> data = tableWorker.get_dataset1(tableDataset1);
    std::cout << (int)data.size() << "\n";
    //std::vector <std::wstring> clearMails = tableWorker.get_normalized_mails(tableDataset1,emailColumn);
    //std::vector <std::wstring> clearPhoneNumbers = tableWorker.get_normalized_phone_numbers(tableDataset1,phoneColumn);
    //std::vector <std::wstring> clearFIO = tableWorker.get_normalized_names(tableDataset1,FIOColumn);
    //std::cout << (int)clearMails.size() << ' ' << (int)clearPhoneNumbers.size() << ' ' << (int)clearFIO.size() << "\n";
    //std::vector <std::wstring> clearAllData =
}

void clear_datataset2(const Config &config){
    TableWorker tableWorker(config);
    const std::string tableDataset2 = "table_dataset2";
    const std::string firstNameColumn = "first_name";
    const std::string middleNameColumn = "middle_name";
    const std::string lastNameColumn = "last_name";
    const std::string phoneColumn = "phone";
    std::vector <std::wstring> clearFirstName = tableWorker.get_normalized_names(tableDataset2,firstNameColumn);
    std::vector <std::wstring> clearMiddleName = tableWorker.get_normalized_names(tableDataset2,middleNameColumn);
    std::vector <std::wstring> clearLastName = tableWorker.get_normalized_names(tableDataset2,lastNameColumn);
    std::vector <std::wstring> clearPhoneNumber = tableWorker.get_normalized_phone_numbers(tableDataset2,phoneColumn);
}

void clear_dataset3(const Config &config){
    TableWorker tableWorker(config);
    const std::string tableDataset3 = "table_dataset3";
    const std::string nameColumn = "name";
    const std::string emailColumn = "email";
    std::vector <std::wstring> clearName = tableWorker.get_normalized_names(tableDataset3,nameColumn);
    std::vector <std::wstring> clearEmail = tableWorker.get_normalized_mails(tableDataset3,emailColumn);
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
    std::wstring pizdec = L"лалал";
    //using convert_typeX = std::codecvt_utf8<wchar_t>;
    double start = clock();
    Config config(argv[1]);
    std::thread threadDataset1(clear_dataset1,config);
    //std::thread threadDataset2(clear_datataset2,config);
    //std::thread threadDataset3(clear_dataset3,config);
    threadDataset1.join();
    //threadDataset2.join();
    //threadDataset3.join();
    printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
