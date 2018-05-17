//
// Created by mike on 17.05.18.
//

#include "SurveyQuery.h"

using namespace std;

cppcms::json::value SurveyQuery::getSurveyRecord(std::string medcardId, std::string page) {
    try{

        //select * from survey, expert where expert.id = survey.expert_id_fk and survey.medcard_id_fk = 1;

        std::string queryString;
        queryString.append("select pos_name, expert_id_fk, first_name, second_name, middle_name, survey_type, results,"
                                   " date_format(receipt_date, '%d.%m.%Y') "
                                   "as date from survey, expert,position where expert.id = survey.expert_id_fk"
                                   " and survey.medcard_id_fk = ");
        queryString.append(medcardId);
        queryString.append(" and position.id = expert.pos_id_fk;");

        res = stmt->executeQuery(queryString);
        int count = 0;
        int pag = std::stoi(page);
        int currpage = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            currpage = count / 5;
            if (currpage + 1 == pag){
                jsonResponse["survey"][count % 5]["specialst"]["specialist_id"] = std::string(res->getString("expert_id_fk"));
                jsonResponse["survey"][count % 5]["specialst"]["position"] = std::string(res->getString("pos_name"));
                jsonResponse["survey"][count % 5]["specialst"]["first_name"] = std::string(res->getString("first_name"));
                jsonResponse["survey"][count % 5]["specialst"]["second_name"] = std::string(res->getString("second_name"));
                jsonResponse["survey"][count % 5]["specialst"]["middle_name"] = std::string(res->getString("middle_name"));
                jsonResponse["survey"][count % 5]["type_of_survey"] = std::string(res->getString("survey_type"));
                jsonResponse["survey"][count % 5]["result"] = std::string(res->getString("results"));
                jsonResponse["survey"][count % 5]["date"] = std::string(res->getString("date"));
            }
            count++;
        }
        int count_pages = (count / 5) + ((count % 5) > 0)?1:0;
        if ((pag > count_pages) || (pag < count_pages)) pag = 0;
        jsonResponse["count_pages"] = count_pages;
        jsonResponse["current_page"] = pag;
        jsonResponse["next_page"] = (count_pages >= pag)?pag:pag+1;
        jsonResponse["prev_page"] = (pag > 0)?pag-1:pag;
        return jsonResponse;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SurveyQuery::createSurveyRecord(cppcms::json::value &newRecord, std::string sid) {
    try{

        //insert into survey values (null, (select expert_id_fk from user, session where session.session_id = 'lGsxaxnNnI' and session.user_id_fk = user.id), 1, 'type_of_survey', 'results', date(now()));
        std::string queryString;
        queryString.append("insert into survey values (null, (select expert_id_fk from user, session where session.session_id = '");
        queryString.append(sid);
        queryString.append("' and session.user_id_fk = user.id), ");
        queryString.append(newRecord["medcard_id"].str());
        queryString.append(", '");
        queryString.append(newRecord["type_of_survey"].str());
        queryString.append("', '");
        queryString.append(newRecord["result"].str());
        queryString.append("', date(now()));");


        res = reinterpret_cast<sql::ResultSet *>(stmt->execute(queryString));

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}