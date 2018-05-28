#include "clinic.h"

using namespace std;

void Clinic::specializations() {
    if (isReceptionist(getClientSid())) {
        SpecializationQuery sq;
        cppcms::json::value jsonResponse = sq.getAllSpecializations();
        jsonResponse.save(response().out(), cppcms::json::readable);
    }
}

void Clinic::posBySpecilazation(const string specializationId) {
    if (isReceptionist(getClientSid())) {
        PositionQuery pq;
        cppcms::json::value jsonResponse = pq.getPosBySpec(specializationId);
        jsonResponse.save(response().out(), cppcms::json::readable);
    }
}

void Clinic::specialistsByPos(const string positionId) {
    if (isReceptionist(getClientSid())) {
        SpecialistQuery sq;
        cppcms::json::value jsonResponse = sq.getSecialistsByPos(positionId);
        jsonResponse.save(response().out(), cppcms::json::readable);
    }
}

void Clinic::specialistsByDate(const string num, const string date) {

    if (isReceptionist(getClientSid())) {
        TimetableQuery tq;
        cppcms::json::value jsonResponse = tq.specialistsByDate(date, num);
        jsonResponse.save(response().out(), cppcms::json::readable);
    }
}


void Clinic::newTimetableEntry(const string timeId, const string medcardId) {
    if (isReceptionist(getClientSid())) {
        TimetableQuery tq;
        tq.createAppointment(timeId, medcardId);
    }
}


void Clinic::getOrCreatePatient() {

    if (request().request_method() == "POST") {
        if (isReceptionist(getClientSid())) {
            pair<void *, size_t> data = request().raw_post_data();
            string postData(reinterpret_cast<char *>(data.first), data.second);
            const char *dataStart = reinterpret_cast<char *>(data.first);
            cppcms::json::value jsonRequest;
            jsonRequest.load(dataStart, postData.data() + postData.size(), false);
            PatientQuery pq;
            pq.createPatient(jsonRequest);
        }
    }
    if (request().request_method() == "GET") {
        if (isReceptionist(getClientSid()) || isDoctor(getClientSid())) {
            PatientQuery pq;
            string second_name = request().get("second_name");
            cppcms::json::value jsonResponse = pq.getPatientBySecondName(second_name);
            jsonResponse.save(response().out(), cppcms::json::readable);
        }
    }

}


void Clinic::todayPatients() {
    if (isDoctor(getClientSid())) {
        PatientQuery pq;
        cppcms::json::value jsonResponse = pq.todayPatients(request().cookie_by_name("sid").value());
        jsonResponse.save(response().out(), cppcms::json::readable);
    }

}

void Clinic::medcardMeta(const string medcardId) {
    if (isDoctor(getClientSid())) {
        PatientQuery pq;
        cppcms::json::value jsonResponse = pq.getPatientById(medcardId);
        jsonResponse.save(response().out(), cppcms::json::readable);
    }
}

void Clinic::medcardHistory(const string medcardId) {
    if (isDoctor(getClientSid())) {
        string page_num = request().get("page");
        cppcms::json::value jsonResponse;
        HistoryQuery hq;
        jsonResponse = hq.getHistoryRecord(medcardId, page_num);
        jsonResponse.save(response().out(), cppcms::json::readable);


    }
}

void Clinic::medcardSurvey(const string medcardId) {
    if (isDoctor(getClientSid())) {
        string page_num = request().get("page");
        cppcms::json::value jsonResponse;
        SurveyQuery sq;
        jsonResponse = sq.getSurveyRecord(medcardId, page_num);
        jsonResponse.save(response().out(), cppcms::json::readable);
    }
}

void Clinic::newSurvey() {
    if (isDoctor(getClientSid())) {
        if (request().request_method() == "POST") {
            pair<void *, size_t> data = request().raw_post_data();
            string postData(reinterpret_cast<char *>(data.first), data.second);
            const char *dataStart = reinterpret_cast<char *>(data.first);
            cppcms::json::value jsonData;
            jsonData.load(dataStart, postData.data() + postData.size(), false);
            SurveyQuery sq;
            sq.createSurveyRecord(jsonData, request().cookie_by_name("sid").value());
        }
    }
}

void Clinic::newHistory() {
    if (isDoctor(getClientSid())) {
        if (request().request_method() == "POST") {
            pair<void *, size_t> data = request().raw_post_data();
            string postData(reinterpret_cast<char *>(data.first), data.second);
            const char *dataStart = reinterpret_cast<char *>(data.first);
            cppcms::json::value jsonRequest;
            jsonRequest.load(dataStart, postData.data() + postData.size(), false);
            HistoryQuery hq;
            hq.createHistoryRecord(jsonRequest, request().cookie_by_name("sid").value());
        }
    }
}


void Clinic::login() {
    if (request().request_method() == "POST") {
        SessionQuery sq;
        if ((sq.authentificate(request().post("login"), request().post("password")))
            && sq.checkSession(request().post("login"), request().post("password"))) {
            const int sidExpiryPeriod = 864000;
            string sid = generate_sid();
            cppcms::http::cookie user_cookie = cppcms::http::cookie(string("user"), request().post("login"));
            user_cookie.expires(time(nullptr) + sidExpiryPeriod);
            response().set_cookie(user_cookie);
            cppcms::http::cookie sid_cookie = cppcms::http::cookie(string("sid"), sid);
            sid_cookie.expires(time(nullptr) + sidExpiryPeriod);
            response().set_cookie(sid_cookie);
            sq.createSession(request().post("login"), request().post("password"), sid);
        }
    }
}

void Clinic::logout() {
    cppcms::http::cookie sid_cookie = request().cookie_by_name("sid");
    cppcms::http::cookie user_cookie = request().cookie_by_name("user");
    SessionQuery sq;
    sq.deleteSession(sid_cookie.value());
    sid_cookie.expires(0);
    user_cookie.expires(0);
    response().set_cookie(sid_cookie);
    response().set_cookie(user_cookie);
}

bool Clinic::isDoctor(const string sid) const {
    SessionQuery sq;
    return sq.isDoctor(sid);
}

bool Clinic::isReceptionist(const string sid) const {
    SessionQuery sq;
    return sq.isReceptionist(sid);
}

string Clinic::generate_sid() {
    static const string alphanum("0123456789abcdefghijklmnopqrstuvwxyz"
                                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ-+=_&");
    srand(time(0));
    int length = 10 + rand() % 26;
    string rand_string;
    for (int i = 0; i < length; ++i) {
        rand_string.append(1, alphanum.at(rand() % 67));
    }
    return rand_string;
}

string Clinic::getClientSid() {
    return request().cookie_by_name("sid").value();
}


