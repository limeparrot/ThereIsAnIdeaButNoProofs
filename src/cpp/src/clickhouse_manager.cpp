//
// Created by Sarmat on 28.09.2024.
//

#include "clickhouse_manager.hpp"

ClickhouseManager::ClickhouseManager() {}

std::vector<std::wstring>
ClickhouseManager::get_string(const Config &config, const std::string &tableName, const std::string &columnName) {
    std::string address = config.get<std::string>("host","address","test.txt");
    std::string login = config.get<std::string>("host","login","test.txt");
    std::string password = config.get<std::string>("host","password","test.txt");
    std::vector <std::wstring> result;
    Client client(ClientOptions().SetHost(address).SetPort(9000).SetUser(login).SetPassword(password));
    client.Select("SELECT * FROM table_dataset1 LIMIT 10", [] (const Block &block){
        for (int i = 0;i < block.GetRowCount();i++){
            std::wstring wasMail(block[2]->As<ColumnString>()->At(i).begin(),block[2]->As<ColumnString>()->At(i).end());
        }
    });
}