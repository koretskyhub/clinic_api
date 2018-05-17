//
// Created by mike on 16.05.18.
//

#include "PatientQuery.h"

using namespace std;

bool PatientQuery::createPatient(cppcms::json::value &newPatient) {
    try{
        std::string queryString;
        queryString.append("insert into medcard values (null, '");
        queryString.append(newPatient["second_name"].str());
        queryString.append("', '");
        queryString.append(newPatient["first_name"].str());
        queryString.append("', '");
        queryString.append(newPatient["middle_name"].str());
        queryString.append("', '");
        queryString.append(newPatient["number_of_police"].str());
        queryString.append("', STR_TO_DATE('");
        queryString.append(newPatient["birthday"].str());
        queryString.append("', '%d.%m.%Y'), '");
        queryString.append(newPatient["telephone"].str());
        queryString.append("', '");
        queryString.append(newPatient["address"].str());
        queryString.append("');");


        res = reinterpret_cast<sql::ResultSet *>(stmt->execute(queryString));

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
};

cppcms::json::value PatientQuery::getPatientBySecondName(std::string secondName) {
    try{
        std::string queryString;
        queryString.append("select * from medcard where second_name like '%");
        queryString.append(secondName);
        queryString.append("%';");

        res = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            jsonResponse["patients"][count]["medcard_id"] = std::string(res->getString("id"));
            jsonResponse["patients"][count]["first_name"] = std::string(res->getString("first_name"));
            jsonResponse["patients"][count]["second_name"] = std::string(res->getString("second_name"));
            jsonResponse["patients"][count]["middle_name"] = std::string(res->getString("middle_name"));
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

cppcms::json::value PatientQuery::getPatientById(std::string id) {

    try{
        std::string queryString;
        queryString.append("select id, second_name, first_name, middle_name,"
                                   " medical_policy, date_format(birthday, '%d.%m.%Y') as birthday,"
                                   " telephone, address from medcard where id = ");
        queryString.append(id);
        queryString.append(";");

        res = stmt->executeQuery(queryString);
        cppcms::json::value jsonResponse;
        if(res->next()){
            jsonResponse["medcard_id"] = std::string(res->getString("id"));
            jsonResponse["first_name"] = std::string(res->getString("first_name"));
            jsonResponse["second_name"] = std::string(res->getString("second_name"));
            jsonResponse["middle_name"] = std::string(res->getString("middle_name"));
            jsonResponse["number_of_police"] = std::string(res->getString("medical_policy"));
            jsonResponse["birthday"] = std::string(res->getString("birthday"));
            jsonResponse["address"] = std::string(res->getString("address"));
            jsonResponse["telephone"] = std::string(res->getString("telephone"));
        }
        return jsonResponse;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

cppcms::json::value PatientQuery::todayPatients(std::string sid) {
    try{

        std::string queryString;
        queryString.append("select medcard_id_fk as medcard_id, first_name, second_name,"
                                   " middle_name, time(reception_datetime) as time from timetable,"
                                   " appointment, medcard where expert_id_fk"
                                   " in (select expert_id_fk from user where id"
                                   " in (select user_id_fk from session where session_id = '");
        queryString.append(sid);
        queryString.append("')) and appointment.id = timetable.id and"
                                   " medcard.id = appointment.medcard_id_fk"
                                   " and date(reception_datetime) = date(now());");

        res = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        while(res->next()){
            jsonResponse["patients"][count]["medcard_id"] = std::string(res->getString("medcard_id"));
            jsonResponse["patients"][count]["first_name"] = std::string(res->getString("first_name"));
            jsonResponse["patients"][count]["second_name"] = std::string(res->getString("second_name"));
            jsonResponse["patients"][count]["middle_name"] = std::string(res->getString("middle_name"));
            jsonResponse["patients"][count]["time"] = std::string(res->getString("time"));
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