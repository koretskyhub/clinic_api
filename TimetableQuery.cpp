//
// Created by mike on 16.05.18.
//

#include "TimetableQuery.h"

using namespace std;

cppcms::json::value TimetableQuery::specialistsByDate(string date, string specId) {

    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select id, date_format(reception_datetime, '%d.%m.%Y')"
                                   " as date, date_format(reception_datetime, '%T') as time "
                                   "from timetable where id not in (select id from appointment)"
                                   " and expert_id_fk = ");
        queryString.append(specId);
        queryString.append(" and date(reception_datetime) = str_to_date('");
        queryString.append(date);
        queryString.append("', '%d.%m.%Y' );");
        queryResult = stmt->executeQuery(queryString);
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

void TimetableQuery::createAppointment(string dateTimeId, string medcardId) {
    try {

        string queryString;
        queryString.append("insert into appointment values(");
        queryString.append(dateTimeId);
        queryString.append(", ");
        queryString.append(medcardId);
        queryString.append(" );");
        stmt->execute(queryString);

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

