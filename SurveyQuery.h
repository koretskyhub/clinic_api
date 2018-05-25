//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_SURVEYQUERY_H
#define CONNECTORTEST_SURVEYQUERY_H

#include "dbQuery.h"

class SurveyQuery : dbQuery {
public:

    void createSurveyRecord(cppcms::json::value &newRecord, string sid);

    cppcms::json::value getSurveyRecord(string medcardId, string page);
};


#endif //CONNECTORTEST_SURVEYQUERY_H
