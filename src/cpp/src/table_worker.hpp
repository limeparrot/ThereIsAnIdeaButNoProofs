#pragma once

#include "config.hpp"

#include <string>

class TableWorker{
  public:
    TableWorker(const Config&);
    std::wstring normalize_mail(const std::wstring& mail);
    std::wstring normalize_phone_number(const std::wstring& number);
    std::wstring normalize_birth_date(const std::wstring& date);
    std::wstring normalize_name(const std::wstring& name);
};
