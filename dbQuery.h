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

class dbQuery {
public:
    dbQuery();
    ~dbQuery();

protected:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
};


#endif //CONNECTORTEST_DBQUERY_H
