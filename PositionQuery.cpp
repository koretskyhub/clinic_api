//
// Created by mike on 16.05.18.
//

#include <sstream>
#include "PositionQuery.h"

using namespace std;

cppcms::json::value PositionQuery::getPosBySpec(const string& id) {
    try {
        stringstream queryString;
        queryString << "select * from position where position.spec_id_fk = ";
        queryString << id;
        queryString << ";";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        int count = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["position"][count];
        while (queryResult->next()) {
            subJson["position_id"] =   string(queryResult->getString("id"));
            subJson["position_name"] = string(queryResult->getString("pos_name"));
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