#pragma once

#include "config.hpp"
#include "clickhouse/client.h"

using namespace clickhouse;

class ClickhouseManager{
public:
    ClickhouseManager();
    std::vector <std::wstring> get_string(const Config &config,
                                          const std::string &tableName,
                                          const std::string &columnName);
    std::vector <clickhouse::ColumnUUID> get_uuid(const Config &config,
                                                  const std::string &tableName,
                                                  const std::string &columnName);

private:

};
