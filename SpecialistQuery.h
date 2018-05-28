//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_SPECIALISTQUERY_H
#define CONNECTORTEST_SPECIALISTQUERY_H

#include "dbQuery.h"

class SpecialistQuery : public dbQuery {
public:
    cppcms::json::value getSecialistsByPos(const std::string& id);
};


#endif //CONNECTORTEST_SPECIALISTQUERY_H
