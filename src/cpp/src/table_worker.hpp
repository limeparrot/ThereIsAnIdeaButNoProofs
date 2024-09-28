#pragma once

#include "config.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>


class TableWorker{
public:
    TableWorker(const Config &config);
    std::wstring normalize_mail(const std::wstring& mail);
    std::wstring normalize_phone_number(const std::wstring& number);
    std::wstring normalize_birth_date(const std::wstring& date);
    std::wstring normalize_name(const std::wstring& name);

private:
    std::set <wchar_t> goodMailSymbols;
    std::vector <std::wstring> mailsDomains;
    // methods
    void read_mails(const std::string &path);
    void remove_bad_symbols(std::wstring &mail);
    void find_mail_struct(std::wstring &mail);
    int levenshtein_distance(const std::wstring &text,const std::wstring &pattern) const;
};
