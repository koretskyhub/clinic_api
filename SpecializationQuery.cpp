//
// Created by mike on 16.05.18.
//

#include "SpecializationQuery.h"

using namespace std;

cppcms::json::value SpecializationQuery::getAllSpecializations() {
    try{
        std::string queryString;
        queryString.append("select * from specialization;");
        res = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            jsonResponse["specialization"][count]["specialization_id"] = std::string(res->getString("id"));
            jsonResponse["specialization"][count]["specialization_name"] = std::string(res->getString("spec_name"));
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