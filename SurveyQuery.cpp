//
// Created by mike on 17.05.18.
//

#include "SurveyQuery.h"

using namespace std;

cppcms::json::value SurveyQuery::getSurveyRecord(string medcardId, string page) {
    try {

        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select pos_name, expert_id_fk, first_name, second_name,"
                                   " middle_name, survey_type, results,"
                                   " date_format(receipt_date, '%d.%m.%Y')"
                                   " as date from survey, expert,position"
                                   " where expert.id = survey.expert_id_fk"
                                   " and survey.medcard_id_fk = ");
        queryString.append(medcardId);
        queryString.append(" and position.id = expert.pos_id_fk;");

        queryResult = stmt->executeQuery(queryString);
        const int pageSize = 5;
        int count = 0;
        int pag = stoi(page);
        int currpage = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["survey"][count % pageSize];
        while (queryResult->next()) {
            currpage = count / pageSize;
            if (currpage + 1 == pag) {
                subJson["specialst"]["specialist_id"] = string(queryResult->getString("expert_id_fk"));
                subJson["specialst"]["position"] =      string(queryResult->getString("pos_name"));
                subJson["specialst"]["first_name"] =    string(queryResult->getString("first_name"));
                subJson["specialst"]["second_name"] =   string(queryResult->getString("second_name"));
                subJson["specialst"]["middle_name"] =   string(queryResult->getString("middle_name"));
                subJson["type_of_survey"] =             string(queryResult->getString("survey_type"));
                subJson["result"] =                     string(queryResult->getString("results"));
                subJson["date"] =                       string(queryResult->getString("date"));
            }
            count++;
        }
        int count_pages = (count / pageSize) + ((count % pageSize) > 0) ? 1 : 0;
        if ((pag > count_pages) || (pag < count_pages)) pag = 0;
        jsonResponse["count_pages"] =   count_pages;
        jsonResponse["current_page"] =  pag;
        jsonResponse["next_page"] =     (count_pages >= pag) ? pag : pag + 1;
        jsonResponse["prev_page"] =     (pag > 0) ? pag - 1 : pag;
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

void SurveyQuery::createSurveyRecord(cppcms::json::value &newRecord, string sid) {
    try {

        string queryString;
        queryString.append("insert into survey values (null, (select expert_id_fk from user,"
                                   " session where session.session_id = '");
        queryString.append(sid);
        queryString.append("' and session.user_id_fk = user.id), ");
        queryString.append(newRecord["medcard_id"].str());
        queryString.append(", '");
        queryString.append(newRecord["type_of_survey"].str());
        queryString.append("', '");
        queryString.append(newRecord["result"].str());
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