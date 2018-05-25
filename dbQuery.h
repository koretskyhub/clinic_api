//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_DBQUERY_H
#define CONNECTORTEST_DBQUERY_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppcms/json.h>

using namespace std;

class dbQuery {
public:
    dbQuery();

    ~dbQuery();

protected:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
private:
    const string dbSchema = "clinic";
    const string dbIP = "tcp://127.0.0.1:3306";
    const string dbLogin = "cpp_project";
    const string dbPswd = "00000000";
};


#endif //CONNECTORTEST_DBQUERY_H
