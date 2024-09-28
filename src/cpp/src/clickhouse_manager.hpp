#pragma once

#include "config.hpp"
#include "clickhouse/client.h"
#include "internal_structs.h"

using namespace clickhouse;

class ClickhouseManager{
public:
    ClickhouseManager();
    static std::vector <std::wstring> get_string(const Config &config,
                                          const std::string &tableName,
                                          const std::string &columnName);
    static std::vector <TableDataset1Data> get_all_from1(const Config& config,
                                                  const std::string &tableName);

private:
    static void insert_new_data1(const Config& config, const std::vector<TableDataset1Data> &data);
};
