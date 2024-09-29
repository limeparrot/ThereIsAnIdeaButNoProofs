//
// Created by Sarmat on 28.09.2024.
//

#include "clickhouse_manager.hpp"

ClickhouseManager::ClickhouseManager() {}

std::vector<std::wstring>
ClickhouseManager::get_one_string_column(const Config &config, const std::string &tableName,
                                         const std::string &columnName) {
    auto address = config.get<std::string>("host","address","test.txt");
    auto login = config.get<std::string>("host","login","test.txt");
    auto password = config.get<std::string>("host","password","test.txt");
    std::vector <std::wstring> result;
    std::stringstream ss;
    ss << "SELECT " << columnName << " FROM " << tableName;
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

std::vector<TableDataset1Data> ClickhouseManager::get_dataset1(const Config &config, const std::string &tableName) {
    auto hostAddress = config.get<std::string>("host","address","test.txt");
    auto login = config.get<std::string>("host","login","test.txt");
    auto password = config.get<std::string>("host","password","test.txt");
    std::stringstream ss;
    ss << "SELECT * FROM " << tableName;
    std::string queryStr = ss.str();
    Client client(ClientOptions().SetHost(hostAddress).SetPort(9000).SetUser(login).SetPassword(password));
    std::vector <TableDataset1Data> data;
    client.Select(queryStr, [&](const Block &block) {
        for (int i = 0; i < block.GetRowCount(); i++) {
            auto uid = block[0]->As<ColumnUUID>()->At(i);
            std::wstring haveFIO(block[1]->As<ColumnString>()->At(i).begin(),
                                 block[1]->As<ColumnString>()->At(i).end());
            std::wstring haveMail(block[2]->As<ColumnString>()->At(i).begin(),
                                  block[2]->As<ColumnString>()->At(i).end());
            std::wstring address(block[3]->As<ColumnString>()->At(i).begin(),
                                 block[3]->As<ColumnString>()->At(i).end());
            std::wstring sex(block[4]->As<ColumnString>()->At(i).begin(),
                             block[4]->As<ColumnString>()->At(i).end());
            std::wstring birthdate(block[5]->As<ColumnString>()->At(i).begin(),
                                   block[5]->As<ColumnString>()->At(i).end());
            std::wstring phone(block[6]->As<ColumnString>()->At(i).begin(),
                               block[6]->As<ColumnString>()->At(i).end());
            data.emplace_back(uid, haveFIO, haveMail, address, sex, birthdate, phone);
        }
    });
    return data;
}

std::vector <TableDataset2Data> ClickhouseManager::get_dataset2(const Config &config, const std::string &tableName) {
    auto hostAddress = config.get<std::string>("host","address","test.txt");
    auto login = config.get<std::string>("host","login","test.txt");
    auto password = config.get<std::string>("host","password","test.txt");
    std::stringstream ss;
    ss << "SELECT * FROM " << tableName;
    std::string queryStr = ss.str();
    Client client(ClientOptions().SetHost(hostAddress).SetPort(9000).SetUser(login).SetPassword(password));
    std::vector <TableDataset2Data> data;
    client.Select(queryStr, [&](const Block &block) {
        for (int i = 0; i < block.GetRowCount(); i++) {
            auto uid = block[0]->As<ColumnUUID>()->At(i);
            std::wstring firstName(block[1]->As<ColumnString>()->At(i).begin(),
                                   block[1]->As<ColumnString>()->At(i).end());
            std::wstring middeName(block[2]->As<ColumnString>()->At(i).begin(),
                                   block[2]->As<ColumnString>()->At(i).end());
            std::wstring lastName(block[3]->As<ColumnString>()->At(i).begin(),
                                  block[3]->As<ColumnString>()->At(i).end());
            std::wstring birthdate(block[4]->As<ColumnString>()->At(i).begin(),
                                   block[4]->As<ColumnString>()->At(i).end());
            std::wstring phone(block[5]->As<ColumnString>()->At(i).begin(),
                               block[5]->As<ColumnString>()->At(i).end());
            std::wstring address(block[6]->As<ColumnString>()->At(i).begin(),
                                 block[6]->As<ColumnString>()->At(i).end());
            data.emplace_back(uid, firstName, middeName, lastName, birthdate, phone, address);
        }
    });
    return data;
}

std::vector <TableDataset3Data> ClickhouseManager::get_dataset3(const Config &config, const std::string &tableName) {
    auto hostAddress = config.get<std::string>("host","address","test.txt");
    auto login = config.get<std::string>("host","login","test.txt");
    auto password = config.get<std::string>("host","password","test.txt");
    std::stringstream ss;
    ss << "SELECT * FROM " << tableName;
    std::string queryStr = ss.str();
    Client client(ClientOptions().SetHost(hostAddress).SetPort(9000).SetUser(login).SetPassword(password));
    std::vector <TableDataset3Data> data;
    client.Select(queryStr, [&](const Block &block) {
        for (int i = 0; i < block.GetRowCount(); i++) {
            auto uid = block[0]->As<ColumnUUID>()->At(i);
            std::wstring name(block[1]->As<ColumnString>()->At(i).begin(),
                                   block[1]->As<ColumnString>()->At(i).end());
            std::wstring email(block[2]->As<ColumnString>()->At(i).begin(),
                                   block[2]->As<ColumnString>()->At(i).end());
            std::wstring birthdate(block[3]->As<ColumnString>()->At(i).begin(),
                                  block[3]->As<ColumnString>()->At(i).end());
            std::wstring sex(block[4]->As<ColumnString>()->At(i).begin(),
                                   block[4]->As<ColumnString>()->At(i).end());
            data.emplace_back(uid,name,email,birthdate,sex);
        }
    });
    return data;
}