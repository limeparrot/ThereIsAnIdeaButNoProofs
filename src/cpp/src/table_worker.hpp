#pragma once

#include "config.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "clickhouse_manager.hpp"
#include "internal_structs.h"

class TableWorker{
public:
    explicit TableWorker(const Config &config);
    std::vector <TableDataset1Data> get_normalazied_dataset1(const std::string &tableName);
    std::vector <TableDataset2Data> get_normalalized_dataset2(const std::string &tableName);
    std::vector <TableDataset3Data> get_normalazied_dataset3(const std::string &tableName);

private:
    std::set <wchar_t> goodMailSymbols;
    std::vector <std::wstring> mailsDomains;
    Config config;
    int maxMailLen;
    // methods
    void read_mails(const std::string &path);
    void remove_bad_symbols(std::wstring &mail);
    void find_mail_struct(std::wstring &mail);
    static void normalize_name(std::wstring &name);
    static void normalize_phone(std::wstring &phone);
    void normalize_mail(std::wstring &mail);
    int levenshtein_distance(const std::wstring &text,const std::wstring &pattern) const;
};
