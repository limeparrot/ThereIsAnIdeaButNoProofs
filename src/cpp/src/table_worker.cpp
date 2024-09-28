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
    std::string path = config.get<std::string>("mail","path","path.txt");
    read_mails(config.get<std::string>("mail","path","path.txt"));
}

std::vector <std::wstring> TableWorker::get_normalized_mails(const std::string &tableName,
                                               const std::string &columnName) {
    ClickhouseManager clickhouseManager;
    std::vector <std::wstring> mailsList = clickhouseManager.get_string(config,tableName,columnName);
    for (auto& mail : mailsList){
        remove_bad_symbols(mail);
        find_mail_struct(mail);
    }
    return mailsList;
}

std::wstring TableWorker::normalize_phone_number(const std::wstring &number) {

}

std::wstring TableWorker::normalize_birth_date(const std::wstring &date) {

}

std::wstring TableWorker::normalize_name(const std::wstring &name) {

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
    if (mail.find('@') == std::wstring::npos) return;
    std::wstring address,domain;
    for (const auto& ch : mail){
        if (ch == '@') break;
        address += ch;
    }
    for (int i = (int)mail.size() - 1; i >= 0;i--){
        domain += mail[i];
        if (mail[i] == '@') break;
    }
    std::reverse(domain.begin(),domain.end());
    std::pair <int,std::wstring> realDomain = std::make_pair(1e9,domain);
    for (const auto& domainPattern : mailsDomains){
        int dist = levenshtein_distance(domain,domainPattern);
        if (dist < realDomain.first){
            realDomain = std::make_pair(dist,domainPattern);
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
    std::wifstream mailsReader(path);
    if (!mailsReader.is_open()){
        throw std::runtime_error("mail path");
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
        curMail.clear();
    }
}
