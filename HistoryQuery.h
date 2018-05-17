//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_HISTORYQUERY_H
#define CONNECTORTEST_HISTORYQUERY_H

#include "dbQuery.h"

class HistoryQuery: dbQuery {
public:

    void createHistoryRecord(cppcms::json::value &newRecord, std::string sid);

    cppcms::json::value getHistoryRecord(std::string medcardId, std::string page);
};


#endif //CONNECTORTEST_HISTORYQUERY_H
