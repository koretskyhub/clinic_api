//
// Created by mike on 16.05.18.
//

#include "TimetableQuery.h"

using namespace std;

cppcms::json::value TimetableQuery::specialistsByDate(std::string date, std::string specId) {

    try{
        std::string queryString;
        queryString.append("select id, date_format(reception_datetime, '%d.%m.%Y') as date, date_format(reception_datetime, '%T') as time "
                                   "from timetable where id not in (select id from appointment) and expert_id_fk = ");
        queryString.append(specId);
        queryString.append(" and date(reception_datetime) = str_to_date('");
        queryString.append(date);
        queryString.append("', '%d.%m.%Y' );");
        res = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            jsonResponse["free_place"][count]["time_id"] = std::stoi(std::string(res->getString("id")));
            jsonResponse["free_place"][count]["date"] = std::string(res->getString("date"));
            jsonResponse["free_place"][count]["time"] = std::string(res->getString("time"));
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

void TimetableQuery::createAppointment(std::string dateTimeId, std::string medcardId) {
    try{
        std::string queryString;
        queryString.append("insert into appointment values(");
        queryString.append(dateTimeId);
        queryString.append(", ");
        queryString.append(medcardId);
        queryString.append(" );");
        res = reinterpret_cast<sql::ResultSet *>(stmt->execute(queryString));

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

