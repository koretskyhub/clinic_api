//
// Created by mike on 17.05.18.
//

#include "SessionQuery.h"

bool SessionQuery::authentificate(string login, string password) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select* from user where login = '");
        queryString.append(login);
        queryString.append("' and password = '");
        queryString.append(password);
        queryString.append("';");

        queryResult = stmt->executeQuery(queryString);
        bool result = false;
        if (queryResult->next()) result = true;
        delete queryResult;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SessionQuery::createSession(string login, string password, string sid) {
    try {
        string queryString;
        queryString.append("insert into session values (null, (select id from user where login = '");
        queryString.append(login);
        queryString.append("' and password='");
        queryString.append(password);
        queryString.append("'), date(date_add(now(), interval 10 day)), '");
        queryString.append(sid);
        queryString.append("');");

        stmt->execute(queryString);

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SessionQuery::deleteSession(string sid) {
    try {
        string queryString;
        queryString.append("delete from  session where session_id = '");
        queryString.append(sid);
        queryString.append("';");

        stmt->execute(queryString);

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::checkSession(string login, string password) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select * from session where user_id_fk in ( select id from user where login = '");
        queryString.append(login);
        queryString.append("' and password = '");
        queryString.append(password);
        queryString.append("');");

        queryResult = stmt->executeQuery(queryString);
        bool result = true;
        if (queryResult->next()) result = false;
        delete queryResult;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::isDoctor(string sid) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select * from user where id in (select user_id_fk from session where session_id = '");
        queryString.append(sid);
        queryString.append("') and expert_id_fk is not null;");

        queryResult = stmt->executeQuery(queryString);
        bool result = false;
        if (queryResult->next()) result = true;
        delete queryResult;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::isReceptionist(string sid) {
    try {
        sql::ResultSet *queryResult;
        string queryString;
        queryString.append("select * from user where id in (select user_id_fk from session where session_id = '");
        queryString.append(sid);
        queryString.append("') and expert_id_fk is null;");

        queryResult = stmt->executeQuery(queryString);
        bool result = false;
        if (queryResult->next()) result = true;
        delete queryResult;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}