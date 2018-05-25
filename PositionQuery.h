//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_POSITIONQUERY_H
#define CONNECTORTEST_POSITIONQUERY_H

#include "dbQuery.h"

class PositionQuery : public dbQuery {
public:
    cppcms::json::value getPosBySpec(const string id);
};


#endif //CONNECTORTEST_POSITIONQUERY_H
