//
// Created by mike on 17.05.18.
//

#include <sstream>
#include "HistoryQuery.h"

using namespace std;

cppcms::json::value HistoryQuery::getHistoryRecord(const string& medcardId, const string& page) {
    try {
        stringstream queryString;
        queryString << "select pos_name, expert_id_fk, first_name, second_name, middle_name,"
                                   " patienthood, diagnostic, assignment, date_format(receipt_date,"
                                   " '%d.%m.%Y') as date"
                                   " from history, expert, position where expert.id = history.expert_id_fk"
                                   " and history.medcard_id_fk = ";
        queryString << medcardId;
        queryString << " and position.id = expert.pos_id_fk;";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        const int pageSize = 5; //Количество записей в формируемом Json-ответе, регулирует его размер
        int count = 0;
        int pageNum = stoi(page);
        int currpage = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["survey"][count % pageSize];
        while (queryResult->next()) {
            currpage = count / pageSize;
            if (currpage + 1 == pageNum) {
                subJson["specialst"]["specialist_id"] = string(queryResult->getString("expert_id_fk"));
                subJson["specialst"]["position"] =      string(queryResult->getString("pos_name"));
                subJson["specialst"]["first_name"] =    string(queryResult->getString("first_name"));
                subJson["specialst"]["second_name"] =   string(queryResult->getString("second_name"));
                subJson["specialst"]["middle_name"] =   string(queryResult->getString("middle_name"));
                subJson["symptoms"] =                   string(queryResult->getString("patienthood"));
                subJson["appointment"] =                string(queryResult->getString("assignment"));
                subJson["diagnosis"] =                  string(queryResult->getString("diagnostic"));
                subJson["date"] =                       string(queryResult->getString("date"));
            }
            count++;
        }
        int count_pages = (count / pageSize) + ((count % pageSize) > 0) ? 1 : 0;
        if ((pageNum > count_pages) || (pageNum < count_pages)) pageNum = 0;
        jsonResponse["count_pages"] = count_pages;
        jsonResponse["current_page"] = pageNum;
        jsonResponse["next_page"] = (count_pages >= pageNum) ? pageNum : pageNum + 1;
        jsonResponse["prev_page"] = (pageNum > 0) ? pageNum - 1 : pageNum;
        //delete queryResult;
        return jsonResponse;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void HistoryQuery::createHistoryRecord(const cppcms::json::value &newRecord, const string& sid) {
    try {
        stringstream queryString;
        queryString << "insert into history values (null, (select expert_id_fk from user,"
                                   " session where session.session_id = '";
        queryString << sid;
        queryString << "' and session.user_id_fk = user.id), ";
        queryString << newRecord["medcard_id"].str();
        queryString << ", '";
        queryString << newRecord["symptoms"].str();
        queryString << "', '";
        queryString << newRecord["appointment"].str();
        queryString << "', '";
        queryString << newRecord["diagnosis"].str();
        queryString << "', date(now()));";


        stmt->execute(queryString.str());

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}