//
// Created by mike on 16.05.18.
//

#include "SpecialistQuery.h"

using namespace std;

cppcms::json::value SpecialistQuery::getSecialistsByPos(string id) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select * from expert where expert.pos_id_fk = ");
        queryString.append(id);
        queryString.append(";");
        queryResult = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["specialists"][count];
        while (queryResult->next()) {
            subJson["specialists_id"] = stoi(string(queryResult->getString("id")));
            subJson["first_name"] =     string(queryResult->getString("first_name"));
            subJson["second_name"] =    string(queryResult->getString("second_name"));
            subJson["middle_name"] =    string(queryResult->getString("middle_name"));
            count++;
        }
        jsonResponse["count"] = count;
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