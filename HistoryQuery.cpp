//
// Created by mike on 17.05.18.
//

#include "HistoryQuery.h"

cppcms::json::value HistoryQuery::getHistoryRecord(const string medcardId, const string page) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select pos_name, expert_id_fk, first_name, second_name, middle_name,"
                                   " patienthood, diagnostic, assignment, date_format(receipt_date,"
                                   " '%d.%m.%Y') as date"
                                   " from history, expert, position where expert.id = history.expert_id_fk"
                                   " and history.medcard_id_fk = ");
        queryString.append(medcardId);
        queryString.append(" and position.id = expert.pos_id_fk;");

        queryResult = stmt->executeQuery(queryString);
        const int pageSize = 5;
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
        delete queryResult;
        return jsonResponse;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void HistoryQuery::createHistoryRecord(const cppcms::json::value &newRecord, const string sid) {
    try {
        string queryString;
        queryString.append("insert into history values (null, (select expert_id_fk from user,"
                                   " session where session.session_id = '");
        queryString.append(sid);
        queryString.append("' and session.user_id_fk = user.id), ");
        queryString.append(newRecord["medcard_id"].str());
        queryString.append(", '");
        queryString.append(newRecord["symptoms"].str());
        queryString.append("', '");
        queryString.append(newRecord["appointment"].str());
        queryString.append("', '");
        queryString.append(newRecord["diagnosis"].str());
        queryString.append("', date(now()));");


        stmt->execute(queryString);

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}