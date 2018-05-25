//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_TIMETABLEQUERY_H
#define CONNECTORTEST_TIMETABLEQUERY_H

#include "dbQuery.h"

class TimetableQuery : public dbQuery {
public:
    cppcms::json::value specialistsByDate(string date, string specId);

    void createAppointment(string dateTimeId, string medcardId);
};


#endif //CONNECTORTEST_TIMETABLEQUERY_H
