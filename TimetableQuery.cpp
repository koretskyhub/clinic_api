//
// Created by mike on 16.05.18.
//

#include <sstream>
#include "TimetableQuery.h"

using namespace std;

cppcms::json::value TimetableQuery::specialistsByDate(const string& date, const string& specId) {

    try {
        stringstream queryString;
        queryString << "select id, date_format(reception_datetime, '%d.%m.%Y')"
                                   " as date, date_format(reception_datetime, '%T') as time "
                                   "from timetable where id not in (select id from appointment)"
                                   " and expert_id_fk = ";
        queryString << specId;
        queryString << " and date(reception_datetime) = str_to_date('";
        queryString << date;
        queryString << "', '%d.%m.%Y' );";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        int count = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["free_place"][count];
        while (queryResult->next()) {
            subJson["time_id"] =    stoi(string(queryResult->getString("id")));
            subJson["date"] =       string(queryResult->getString("date"));
            subJson["time"] =       string(queryResult->getString("time"));
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

void TimetableQuery::createAppointment(const string& dateTimeId, const string& medcardId) {
    try {

        stringstream queryString;
        queryString << "insert into appointment values(";
        queryString << dateTimeId;
        queryString << ", ";
        queryString << medcardId;
        queryString << " );";
        stmt->execute(queryString.str());

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

