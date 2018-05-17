//
// Created by mike on 16.05.18.
//

#include "SpecialistQuery.h"

using namespace std;

cppcms::json::value SpecialistQuery::getSecialistsByPos(std::string id) {
    try{
        std::string queryString;
        queryString.append("select * from expert where expert.pos_id_fk = ");
        queryString.append(id);
        queryString.append(";");
        res = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            jsonResponse["specialists"][count]["specialists_id"] = std::stoi(std::string(res->getString("id")));
            jsonResponse["specialists"][count]["first_name"] = std::string(res->getString("first_name"));
            jsonResponse["specialists"][count]["second_name"] = std::string(res->getString("second_name"));
            jsonResponse["specialists"][count]["middle_name"] = std::string(res->getString("middle_name"));
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