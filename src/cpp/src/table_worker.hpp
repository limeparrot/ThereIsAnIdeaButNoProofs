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
    TableWorker(const Config &config);
    std::vector <std::wstring> get_normalized_mails(const std::string &tableName,
                                      const std::string &columnName);
    std::vector <std::wstring> get_normalized_phone_numbers(const std::string &tableName,
                                                            const std::string &columnName);
    std::vector <std::wstring> get_normalized_birth_dates(const std::string &tableName,
                                           const std::string &columnName);
    std::vector <std::wstring> get_normalized_names(const std::string &tableName,
                                     const std::string &columnName);
    std::vector <TableDataset1Data> get_dataset1(const std::string &tableName);

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
