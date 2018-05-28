//
// Created by mike on 24.05.18.
//

#ifndef CONNECTORTEST_CLINIC_H
#define CONNECTORTEST_CLINIC_H

#include <iostream>
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/http_cookie.h>
#include "PatientQuery.h"
#include "SpecializationQuery.h"
#include "PositionQuery.h"
#include "SpecialistQuery.h"
#include "TimetableQuery.h"
#include "SessionQuery.h"
#include "HistoryQuery.h"
#include "SurveyQuery.h"

class Clinic : public cppcms::application {
public:
    Clinic(cppcms::service &srv) : cppcms::application(srv) {

        const std::string dateRegexp("(((0[1-9]|[12]\\d|3[01])\\.(0[13578]|1[02])\\.((19|[2-9]\\d)\\d{2})) "
                                        "|((0[1-9]|[12]\\d|30)\\.(0[13456789]|1[012])\\.((19|[2-9]\\d)"
                                        "\\d{2}))|((0[1-9]|1\\d|2[0-8])\\.02\\.((19|[2-9]\\d)\\d{2}))|"
                                        "(29\\.02\\.((1[6-9]|[2-9]\\d)(0[48]|[2468][048]|[13579][26])|"
                                        "((16|[2468][048]|[3579][26])00))))$");


        dispatcher().assign("/specializations",
                            &Clinic::specializations, this);

        dispatcher().assign("/specializations/(\\d+)/positions",
                            &Clinic::posBySpecilazation, this, 1);

        dispatcher().assign("/position/(\\d+)/specialists",
                            &Clinic::specialistsByPos, this, 1);

        dispatcher().assign(std::string("/specialists/(\\d+)/timetable/").append(dateRegexp),
                            &Clinic::specialistsByDate, this, 1, 2);

        dispatcher().assign("/timetable/(\\d+)/medcard/(\\d+)",
                            &Clinic::newTimetableEntry, this, 1, 2);

        dispatcher().assign("/patients",
                            &Clinic::getOrCreatePatient, this);

        dispatcher().assign("/doctor/patients/date/today",
                            &Clinic::todayPatients, this);

        dispatcher().assign("/medcard/(\\d+)",
                            &Clinic::medcardMeta, this, 1);

        dispatcher().assign("/medcard/(\\d+)/history",
                            &Clinic::medcardHistory, this, 1);

        dispatcher().assign("/medcard/(\\d+)/survey",
                            &Clinic::medcardSurvey, this, 1);

        dispatcher().assign("/survey",
                            &Clinic::newSurvey, this);

        dispatcher().assign("/history",
                            &Clinic::newHistory, this);

        dispatcher().assign("/login",
                            &Clinic::login, this);

        mapper().assign("login", "/login");

        dispatcher().assign("/logout", &Clinic::logout, this);

        mapper().assign("");

        mapper().root("/");
    }

    void specializations();

    void posBySpecilazation(const std::string specializationId);

    void specialistsByPos(const std::string positionId);

    void specialistsByDate(const std::string num, const std::string date);

    void newTimetableEntry(const std::string timeId, const std::string medcardId);

    void getOrCreatePatient();

    void todayPatients();

    void medcardMeta(const std::string medcardId);

    void medcardHistory(const std::string medcardId);

    void medcardSurvey(const std::string medcardId);

    void newSurvey();

    void newHistory();

    void login();

    void logout();

    bool isDoctor(const std::string sid) const;

    bool isReceptionist(const std::string sid) const;

    std::string generate_sid();

    std::string getClientSid();

};

#endif //CONNECTORTEST_CLINIC_H
