//
// Created by Sarmat on 28.09.2024.
//

#include "table_worker.hpp"

TableWorker::TableWorker(const Config &config){
    this->config = config;
    for (wchar_t ch = 'a';ch <= 'z';ch++){
        goodMailSymbols.insert(ch); goodMailSymbols.insert(toupper(ch));
    }
    for (wchar_t ch = '0';ch <= '9';ch++) goodMailSymbols.insert(ch);
    goodMailSymbols.insert({'.','_','@','-'});
    read_mails(config.get<std::string>("mail","path","path.txt"));
}

void TableWorker::remove_bad_symbols(std::wstring &mail) {
    std::wstring newMail;
    for (const auto& ch : mail){
        if (goodMailSymbols.find(ch) != goodMailSymbols.end())
            newMail += ch;
    }
    mail = std::move(newMail);
}

void TableWorker::find_mail_struct(std::wstring &mail) {
    std::wstring address;
    std::pair <int,std::wstring> realDomain = {1e9,mailsDomains.front()};
    if (mail.find('@') == std::wstring::npos){
        std::wstring suffix;
        for (int i = (int)mail.size() - 1;i >= std::max(0,i - maxMailLen);i--){
            suffix += mail[i];
            std::reverse(suffix.begin(),suffix.end());
            for (auto& domain : mailsDomains){
                int dist = levenshtein_distance(suffix,domain);
                if (dist < realDomain.first){
                    realDomain = std::make_pair(dist,domain);
                }
            }
            std::reverse(suffix.begin(),suffix.end());
        }
        for (int i = 0;i < (int)mail.size() - (int)realDomain.second.size();i++)
            address += mail[i];
    }
    else {
        std::wstring domain;
        for (const auto &ch: mail) {
            if (ch == '@') break;
            address += ch;
        }
        for (int i = (int) mail.size() - 1; i >= 0; i--) {
            domain += mail[i];
            if (mail[i] == '@') break;
        }
        std::reverse(domain.begin(), domain.end());
        realDomain.second = domain;
        for (const auto &domainPattern: mailsDomains) {
            int dist = levenshtein_distance(domain, domainPattern);
            if (dist < realDomain.first) {
                realDomain = std::make_pair(dist, domainPattern);
            }
        }
    }
    mail = address + realDomain.second;
}

int TableWorker::levenshtein_distance(const std::wstring &text,const std::wstring &pattern) const {
    int n = (int)text.size(),m = (int)pattern.size();
    std::vector < std::vector <int> > dp(n + 1,std::vector <int> (m + 1));
    dp[0][0] = 0;
    for (int i = 1;i <= n;i++) dp[i][0] = i;
    for (int j = 1;j <= m;j++) dp[0][j] = j;
    for (int i = 1;i <= n;i++){
        for (int j = 1;j <= m;j++){
            dp[i][j] = std::min(dp[i - 1][j] + 1,dp[i][j - 1] + 1);
            if (text[i - 1] == pattern[j - 1]) dp[i][j] = std::min(dp[i][j],dp[i - 1][j - 1]);
            else dp[i][j] = std::min(dp[i][j],dp[i - 1][j - 1] + 1);
        }
    }
    return dp[n - 1][m - 1];
}

void TableWorker::read_mails(const std::string &path) {
    maxMailLen = 0;
    std::wifstream mailsReader(path);
    if (!mailsReader.is_open()){
        throw std::runtime_error(path);
    }
    std::wstring mailsData;
    std::getline(mailsReader,mailsData);
    std::wstring curMail;
    for (const auto& ch : mailsData){
        if (ch != ','){
            curMail += ch; continue;
        }
        if ((int)curMail.size() == 0) continue;
        curMail.pop_back();
        std::reverse(curMail.begin(),curMail.end());
        curMail.pop_back();
        curMail += '@';
        std::reverse(curMail.begin(),curMail.end());
        mailsDomains.push_back(curMail);
        maxMailLen = std::max(maxMailLen,(int)curMail.size());
        curMail.clear();
    }
}

std::vector<TableDataset1Data> TableWorker::get_normalazied_dataset1(const std::string &tableName) {
    std::vector <TableDataset1Data> data = ClickhouseManager::get_dataset1(config,tableName);
    for (auto& [uid,full_name,email,address,sex,birthdate,phone] : data){
        normalize_name(full_name);
        normalize_mail(email);
        normalize_phone(phone);
    }
    return data;
}

std::vector <TableDataset2Data> TableWorker::get_normalalized_dataset2(const std::string &tableName) {
    std::vector <TableDataset2Data> data = ClickhouseManager::get_dataset2(config,tableName);
    for (auto& [uid,firstName,middleName,lastName,birthdate,phone,address] : data){
        normalize_name(firstName);
        normalize_name(middleName);
        normalize_name(lastName);
        normalize_phone(phone);
    }
    return data;
}

std::vector <TableDataset3Data> TableWorker::get_normalazied_dataset3(const std::string &tableName) {
    std::vector <TableDataset3Data> data = ClickhouseManager::get_dataset3(config,tableName);
    for (auto& [uid,name,email,birthdate,sex] : data){
        normalize_name(name);
        normalize_mail(email);
    }
    return data;
}

void TableWorker::normalize_name(std::wstring &name) {
    std::set <wchar_t> badChs = {',','|',';',':','*','-','`','+','_','&','#','%','@','^','(',')'};
    std::wstring normalName;
    for (auto& ch : name) {
        if ((ch >= '0' && ch <= '9') || badChs.find(ch) != badChs.end()) continue;
        normalName += ch;
    }
    name = normalName;
}

void TableWorker::normalize_phone(std::wstring &phone) {
    std::wstring realPhone;
    for (const auto& ch : phone){
        if (ch >= '0'&& ch <= '9') realPhone += ch;
    }
    if ((int)realPhone.size() == 11) {
        phone = realPhone;
        if (phone.front() == '7') phone.front() = '8';
    }
    else if ((int)realPhone.size() == 10){
        std::reverse(realPhone.begin(),realPhone.end());
        realPhone += '8';
        std::reverse(realPhone.begin(),realPhone.end());
        phone = realPhone;
    }
}

void TableWorker::normalize_mail(std::wstring &mail) {
    remove_bad_symbols(mail);
    find_mail_struct(mail);
}