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
    std::stringstream ss;
    ss << "SELECT " << columnName << " FROM " << tableName << " LIMIT 100";
    std::string queryStr = ss.str();
    std::vector <std::wstring> mailsList;
    Client client(ClientOptions().SetHost(address).SetPort(9000).SetUser(login).SetPassword(password));
    client.Select(queryStr, [&] (const Block &block){
        for (int i = 0;i < block.GetRowCount();i++){
            std::wstring haveMail(block[0]->As<ColumnString>()->At(i).begin(),block[0]->As<ColumnString>()->At(i).end());
            mailsList.push_back(haveMail);
        }
    });
    return mailsList;
}