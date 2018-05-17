//
// Created by mike on 16.05.18.
//

#include "PositionQuery.h"

using namespace std;

cppcms::json::value PositionQuery::getPosBySpec(std::string id) {
    try{
        std::string queryString;
        queryString.append("select * from position where position.spec_id_fk = ");
        queryString.append(id);
        queryString.append(";");
        res = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            jsonResponse["position"][count]["position_id"] = std::string(res->getString("id"));
            jsonResponse["position"][count]["position_name"] = std::string(res->getString("pos_name"));
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