//
// Created by mike on 16.05.18.
//

#include "PatientQuery.h"

bool PatientQuery::createPatient(const cppcms::json::value &newPatient) {
    try {

        string queryString;
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

        stmt->execute(queryString);

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
};

cppcms::json::value PatientQuery::getPatientBySecondName(const string secondName) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select * from medcard where second_name like '%");
        queryString.append(secondName);
        queryString.append("%';");
        queryResult = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["patients"][count];
        while (queryResult->next()) {
            subJson["medcard_id"] =  string(queryResult->getString("id"));
            subJson["first_name"] =  string(queryResult->getString("first_name"));
            subJson["second_name"] = string(queryResult->getString("second_name"));
            subJson["middle_name"] = string(queryResult->getString("middle_name"));
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

cppcms::json::value PatientQuery::getPatientById(const string id) {

    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select id, second_name, first_name, middle_name,"
                                   " medical_policy, date_format(birthday, '%d.%m.%Y') as birthday,"
                                   " telephone, address from medcard where id = ");
        queryString.append(id);
        queryString.append(";");
        queryResult = stmt->executeQuery(queryString);
        cppcms::json::value jsonResponse;
        if (queryResult->next()) {
            jsonResponse["medcard_id"] =        string(queryResult->getString("id"));
            jsonResponse["first_name"] =        string(queryResult->getString("first_name"));
            jsonResponse["second_name"] =       string(queryResult->getString("second_name"));
            jsonResponse["middle_name"] =       string(queryResult->getString("middle_name"));
            jsonResponse["number_of_police"] =  string(queryResult->getString("medical_policy"));
            jsonResponse["birthday"] =          string(queryResult->getString("birthday"));
            jsonResponse["address"] =           string(queryResult->getString("address"));
            jsonResponse["telephone"] =         string(queryResult->getString("telephone"));
        }
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

cppcms::json::value PatientQuery::todayPatients(string sid) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select medcard_id_fk as medcard_id, first_name, second_name,"
                                   " middle_name, time(reception_datetime) as time from timetable,"
                                   " appointment, medcard where expert_id_fk"
                                   " in (select expert_id_fk from user where id"
                                   " in (select user_id_fk from session where session_id = '");
        queryString.append(sid);
        queryString.append("')) and appointment.id = timetable.id and"
                                   " medcard.id = appointment.medcard_id_fk"
                                   " and date(reception_datetime) = date(now());");

        queryResult = stmt->executeQuery(queryString);
        int count = 0;
        cppcms::json::value jsonResponse;
        auto &subJson = jsonResponse["patients"][count];
        while (queryResult->next()) {
            subJson["medcard_id"] =     string(queryResult->getString("medcard_id"));
            subJson["first_name"] =     string(queryResult->getString("first_name"));
            subJson["second_name"] =    string(queryResult->getString("second_name"));
            subJson["middle_name"] =    string(queryResult->getString("middle_name"));
            subJson["time"] =           string(queryResult->getString("time"));
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