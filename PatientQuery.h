//
// Created by mike on 16.05.18.
//

#ifndef CONNECTORTEST_PATIENTQUERY_H
#define CONNECTORTEST_PATIENTQUERY_H

#include "dbQuery.h"


class PatientQuery: public dbQuery{
public:

    bool createPatient(cppcms::json::value &newPatient);

    cppcms::json::value getPatientBySecondName(std::string secondName);

    cppcms::json::value getPatientById(std::string id);

    cppcms::json::value todayPatients(std::string sid);

    PatientQuery():dbQuery(){};

};


#endif //CONNECTORTEST_PATIENTQUERY_H
