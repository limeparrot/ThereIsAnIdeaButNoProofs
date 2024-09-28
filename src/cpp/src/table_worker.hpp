#pragma once

#include "config.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "clickhouse_manager.hpp"

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

private:
    std::set <wchar_t> goodMailSymbols;
    std::vector <std::wstring> mailsDomains;
    Config config;
    // methods
    void read_mails(const std::string &path);
    void remove_bad_symbols(std::wstring &mail);
    void find_mail_struct(std::wstring &mail);
    int levenshtein_distance(const std::wstring &text,const std::wstring &pattern) const;
};
