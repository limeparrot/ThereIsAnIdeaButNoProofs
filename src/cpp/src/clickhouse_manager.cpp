//
// Created by Sarmat on 28.09.2024.
//

#include "clickhouse_manager.hpp"

ClickhouseManager::ClickhouseManager() {}

std::vector<std::wstring>
ClickhouseManager::get_string(const Config &config, const std::string &tableName, const std::string &columnName) {
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

std::vector<TableDataset1Data> ClickhouseManager::get_all_from1(const Config &config, const std::string &tableName) {
    auto hostAddress = config.get<std::string>("host","address","test.txt");
    auto login = config.get<std::string>("host","login","test.txt");
    auto password = config.get<std::string>("host","password","test.txt");
    std::stringstream ss;
    ss << "SELECT * FROM " << tableName;
    std::string queryStr = ss.str();
    std::vector <TableDataset1Data> data;
    Client client(ClientOptions().SetHost(hostAddress).SetPort(9000).SetUser(login).SetPassword(password));
    client.Execute("CREATE TABLE IF NOT EXISTS default.clean_table1 (id Uint64, uid UUID, full_name String,address String,sex String,birthdate String,phone String) ENGINE = MergeTree()");
    {
        Block block;
        auto uid = std::make_shared<ColumnUUID>();
        auto full_name = std::make_shared<ColumnString>();
        auto email = std::make_shared<ColumnString>();
        auto address = std::make_shared<ColumnString>();
        auto sex = std::make_shared<ColumnString>();
        auto birthdate = std::make_shared<ColumnString>();
        auto phone = std::make_shared<ColumnString>();
        block.AppendColumn("uid",uid);
        block.AppendColumn("full_name",full_name);
        block.AppendColumn("email",email);
        block.AppendColumn("address",address);
        block.AppendColumn("sex",sex);
        block.AppendColumn("birthdate",birthdate);
        block.AppendColumn("phone",phone);
    }
    client.Select(queryStr, [&] (const Block &block){
        for (int i = 0;i < block.GetRowCount();i++){
            auto uid = block[0]->As<ColumnUUID>()->At(i);
            std::wstring haveFIO(block[1]->As<ColumnString>()->At(i).begin(),block[1]->As<ColumnString>()->At(i).end());
            std::wstring haveMail(block[2]->As<ColumnString>()->At(i).begin(),block[2]->As<ColumnString>()->At(i).end());
            std::wstring address(block[3]->As<ColumnString>()->At(i).begin(),block[3]->As<ColumnString>()->At(i).end());
            std::wstring sex(block[4]->As<ColumnString>()->At(i).begin(),block[4]->As<ColumnString>()->At(i).end());
            std::wstring birthdate(block[5]->As<ColumnString>()->At(i).begin(),block[5]->As<ColumnString>()->At(i).end());
            std::wstring phone(block[6]->As<ColumnString>()->At(i).begin(),block[6]->As<ColumnString>()->At(i).end());
            data.emplace_back(uid,haveFIO,haveMail,address,sex,birthdate,phone);
        }
    });
    return data;
}

void ClickhouseManager::insert_new_data1(const Config& config,const std::vector<TableDataset1Data> &data) {
    auto hostAddress = config.get<std::string>("host","address","test.txt");
    auto login = config.get<std::string>("host","login","test.txt");
    auto password = config.get<std::string>("host","password","test.txt");
    Client client(ClientOptions().SetHost(hostAddress).SetPort(9000).SetUser(login).SetPassword(password));
    client.Execute("CREATE TABLE IF NOT EXISTS default.clean_table1 (id Uint64, uid UUID, full_name String,address String,sex String,birthdate String,phone String) ENGINE = MergeTree()");
    {
        for (const auto &[uid, full_name, email, address, sex, birthdate, phone]: data) {

        }
    }
}