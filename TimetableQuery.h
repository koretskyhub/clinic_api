//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_TIMETABLEQUERY_H
#define CONNECTORTEST_TIMETABLEQUERY_H

#include "dbQuery.h"

class TimetableQuery : public dbQuery {
public:
    cppcms::json::value specialistsByDate(const std::string& date, const std::string& specId);
    void createAppointment(const std::string& dateTimeId, const std::string& medcardId);
};


#endif //CONNECTORTEST_TIMETABLEQUERY_H
