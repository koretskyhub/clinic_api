//
// Created by mike on 16.05.18.
//

#include <sstream>
#include "SpecializationQuery.h"

using namespace std;

cppcms::json::value SpecializationQuery::getAllSpecializations() {
    try {
        stringstream queryString;
        queryString << "select * from specialization;";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        int count = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["specialization"][count];
        while (queryResult->next()) {
            subJson["specialization_id"] =      string(queryResult->getString("id"));
            subJson["specialization_name"] =    string(queryResult->getString("spec_name"));
            count++;
        }
        jsonResponse["count"] = count;
        return jsonResponse;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}