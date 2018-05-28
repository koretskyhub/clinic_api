//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_HISTORYQUERY_H
#define CONNECTORTEST_HISTORYQUERY_H

#include "dbQuery.h"

class HistoryQuery : dbQuery {
public:

    void createHistoryRecord(const cppcms::json::value &newRecord, const std::string& sid);
    cppcms::json::value getHistoryRecord(const std::string& medcardId, const std::string& page);
};


#endif //CONNECTORTEST_HISTORYQUERY_H
