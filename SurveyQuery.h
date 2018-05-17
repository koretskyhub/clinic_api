//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_SURVEYQUERY_H
#define CONNECTORTEST_SURVEYQUERY_H

#include "dbQuery.h"

class SurveyQuery: dbQuery {
public:

    void createSurveyRecord(cppcms::json::value &newRecord, std::string sid);

    cppcms::json::value getSurveyRecord(std::string medcardId, std::string page);
};


#endif //CONNECTORTEST_SURVEYQUERY_H
