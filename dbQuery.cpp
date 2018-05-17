//
// Created by mike on 16.05.18.
//

#include "dbQuery.h"

dbQuery::dbQuery() {
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "cpp_project", "00000000");
    /* Connect to the MySQL test database */
    con->setSchema("clinic");
    stmt = con->createStatement();
};

dbQuery::~dbQuery() {
    delete res;
    delete stmt;
    delete con;
};