//
// Created by mike on 17.05.18.
//

#include <sstream>
#include "SessionQuery.h"

using namespace std;

bool SessionQuery::authentificate(const std::string& login, const std::string& password) {
    try {
        stringstream queryString;
        queryString << "select* from user where login = '";
        queryString << login;
        queryString << "' and password = '";
        queryString << password;
        queryString << "';";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        bool result = false;
        if (queryResult->next()) result = true;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SessionQuery::createSession(const std::string& login, const std::string& password, const std::string& sid) {
    try {
        stringstream queryString;
        queryString << "insert into session values (null, (select id from user where login = '";
        queryString << login;
        queryString << "' and password='";
        queryString << password;
        queryString << "'), date(date_add(now(), interval 10 day)), '";
        queryString << sid;
        queryString << "');";

        stmt->execute(queryString.str());

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SessionQuery::deleteSession(const std::string& sid) {
    try {
        stringstream queryString;
        queryString << "delete from  session where session_id = '";
        queryString << sid;
        queryString << "';";

        stmt->execute(queryString.str());

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::checkSession(const std::string& login, const std::string& password) {
    try {
        stringstream queryString;
        queryString << "select * from session where user_id_fk in ( select id from user where login = '";
        queryString << login;
        queryString << "' and password = '";
        queryString << password;
        queryString << "');";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        bool result = true;
        if (queryResult->next()) result = false;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::isDoctor(const std::string& sid) {
    try {
        stringstream queryString;
        queryString << "select * from user where id in (select user_id_fk from session where session_id = '";
        queryString << sid;
        queryString << "') and expert_id_fk is not null;";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        bool result = false;
        if (queryResult->next()) result = true;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::isReceptionist(const std::string& sid) {
    try {
        stringstream queryString;
        queryString << "select * from user where id in (select user_id_fk from session where session_id = '";
        queryString << sid;
        queryString << "') and expert_id_fk is null;";
        shared_ptr<sql::ResultSet> queryResult(stmt->executeQuery(queryString.str()));
        bool result = false;
        if (queryResult->next()) result = true;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}