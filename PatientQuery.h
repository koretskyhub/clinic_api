//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_PATIENTQUERY_H
#define CONNECTORTEST_PATIENTQUERY_H

#include "dbQuery.h"


class PatientQuery : public dbQuery {
public:

    bool createPatient(const cppcms::json::value &newPatient);

    cppcms::json::value getPatientBySecondName(const std::string& secondName);

    cppcms::json::value getPatientById(const std::string& id);

    cppcms::json::value todayPatients(const std::string& sid);

};


#endif //CONNECTORTEST_PATIENTQUERY_H
