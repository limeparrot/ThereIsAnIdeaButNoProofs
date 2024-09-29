#pragma once

#include "config.hpp"
#include "clickhouse/client.h"
#include "internal_structs.h"

using namespace clickhouse;

class ClickhouseManager{
public:
    ClickhouseManager();
    static std::vector <std::wstring> get_one_string_column(const Config &config,
                                          const std::string &tableName,
                                          const std::string &columnName);
    static std::vector <TableDataset1Data> get_dataset1(const Config& config,
                                                  const std::string &tableName);
    static std::vector <TableDataset2Data> get_dataset2(const Config &config,
                                                        const std::string &tableName);
    static std::vector <TableDataset3Data> get_dataset3(const Config &config,
                                                        const std::string &tableName);

};
