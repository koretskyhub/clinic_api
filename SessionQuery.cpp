//
// Created by mike on 17.05.18.
//

#include "SessionQuery.h"

using namespace std;

bool SessionQuery::authentificate(std::string login, std::string password) {
    try{
        std::string queryString;
        queryString.append("select* from user where login = '");
        queryString.append(login);
        queryString.append("' and password = '");
        queryString.append(password);
        queryString.append("';");

        res = stmt->executeQuery(queryString);
        bool result = false;
        if(res->next()) result = true;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SessionQuery::createSession(std::string login, std::string password, std::string sid) {
    try{
        std::string queryString;
        queryString.append("insert into session values (null, (select id from user where login = '");
        queryString.append(login);
        queryString.append("' and password='");
        queryString.append(password);
        queryString.append("'), date(date_add(now(), interval 10 day)), '");
        queryString.append(sid);
        queryString.append("');");

        res = reinterpret_cast<sql::ResultSet *>(stmt->execute(queryString));

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void SessionQuery::deleteSession(std::string sid) {
    try{
        std::string queryString;
        queryString.append("delete from  session where session_id = '");
        queryString.append(sid);
        queryString.append("';");

        res = reinterpret_cast<sql::ResultSet *>(stmt->execute(queryString));

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::checkSession(std::string login, std::string password) {
    try{
        std::string queryString;
        queryString.append("select * from session where user_id_fk in ( select id from user where login = '");
        queryString.append(login);
        queryString.append("' and password = '");
        queryString.append(password);
        queryString.append("');");

        res = stmt->executeQuery(queryString);
        bool result = true;
        if(res->next()) result = false;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::isDoctor(std::string sid) {
    try{

        //select * from user where id in (select user_id_fk from session where session_id = 'k9VY_zhqb1nU_bbYRIDIEsTdb+gSqy_K') and expert_id_fk is not null;

        std::string queryString;
        queryString.append("select * from user where id in (select user_id_fk from session where session_id = '");
        queryString.append(sid);
        queryString.append("') and expert_id_fk is not null;");

        res = stmt->executeQuery(queryString);
        bool result = false;
        if(res->next()) result = true;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool SessionQuery::isReceptionist(std::string sid) {
    try{

        //select * from user where id in (select user_id_fk from session where session_id = 'k9VY_zhqb1nU_bbYRIDIEsTdb+gSqy_K') and expert_id_fk is not null;

        std::string queryString;
        queryString.append("select * from user where id in (select user_id_fk from session where session_id = '");
        queryString.append(sid);
        queryString.append("') and expert_id_fk is null;");

        res = stmt->executeQuery(queryString);
        bool result = false;
        if(res->next()) result = true;
        return result;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}