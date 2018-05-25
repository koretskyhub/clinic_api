//
// Created by mike on 16.05.18.
//

#include "dbQuery.h"

dbQuery::dbQuery() {
    driver = get_driver_instance();
    con = driver->connect(dbIP, dbLogin, dbPswd);
    con->setSchema(dbSchema);
    stmt = con->createStatement();
};

dbQuery::~dbQuery() {
    delete stmt;
    delete con;
};