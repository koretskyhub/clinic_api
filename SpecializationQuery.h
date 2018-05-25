//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_SPECIALIZATIONQUERY_H
#define CONNECTORTEST_SPECIALIZATIONQUERY_H

#include "dbQuery.h"

class SpecializationQuery : public dbQuery {
public:

    cppcms::json::value getAllSpecializations();

    SpecializationQuery() : dbQuery() {};

};


#endif //CONNECTORTEST_SPECIALIZATIONQUERY_H
