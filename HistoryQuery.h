//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_HISTORYQUERY_H
#define CONNECTORTEST_HISTORYQUERY_H

#include "dbQuery.h"

class HistoryQuery : dbQuery {
public:

    void createHistoryRecord(const cppcms::json::value &newRecord, const string sid);
    cppcms::json::value getHistoryRecord(const string medcardId, const string page);
};


#endif //CONNECTORTEST_HISTORYQUERY_H
