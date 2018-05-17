#include <cppcms/application.h>
#include <iostream>
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
    Clinic(cppcms::service &srv) :  
        cppcms::application(srv)  
    {

        std::string dateRegexp("(((0[1-9]|[12]\\d|3[01])\\.(0[13578]|1[02])\\.((19|[2-9]\\d)\\d{2})) "
                                       "|((0[1-9]|[12]\\d|30)\\.(0[13456789]|1[012])\\.((19|[2-9]\\d)"
                                       "\\d{2}))|((0[1-9]|1\\d|2[0-8])\\.02\\.((19|[2-9]\\d)\\d{2}))|"
                                       "(29\\.02\\.((1[6-9]|[2-9]\\d)(0[48]|[2468][048]|[13579][26])|"
                                       "((16|[2468][048]|[3579][26])00))))$");


    	dispatcher().assign("/specializations", &Clinic::specializations, this);

    	dispatcher().assign("/specializations/(\\d+)/positions", &Clinic::posBySpecilazation, this, 1);
    	
    	dispatcher().assign("/position/(\\d+)/specialists", &Clinic::specialistsByPos, this, 1);
    	
    	dispatcher().assign(std::string("/specialists/(\\d+)/timetable/").append(dateRegexp), &Clinic::specialistsByDate, this, 1, 2);
    	
    	dispatcher().assign("/timetable/(\\d+)/medcard/(\\d+)", &Clinic::newTimetableEntry, this, 1, 2);


    	dispatcher().assign("/patients", &Clinic::getOrCreatePatient, this);


    	dispatcher().assign("/doctor/patients/date/today", &Clinic::todayPatients, this);
    	
    	dispatcher().assign("/medcard/(\\d+)", &Clinic::medcardMeta, this, 1);
    	
    	dispatcher().assign("/medcard/(\\d+)/history", &Clinic::medcardHistory, this, 1);
    	
    	dispatcher().assign("/medcard/(\\d+)/survey", &Clinic::medcardSurvey, this, 1);
    	
    	dispatcher().assign("/survey", &Clinic::newSurvey, this);
    	
    	dispatcher().assign("/history", &Clinic::newHistory, this);


    	dispatcher().assign("/login", &Clinic::login, this);
    	mapper().assign("login","/login");

    	dispatcher().assign("/logout", &Clinic::logout, this);
   	    mapper().assign("");  
  
 		mapper().root("/");
    }  

    void specializations(){
    	if (isReceptionist())
    	{
            SpecializationQuery sq;
    		cppcms::json::value jsonResponse = sq.getAllSpecializations();
    		jsonResponse.save(response().out(),cppcms::json::readable);
    	}
    }

    void posBySpecilazation(std::string specializationId){
    	if (isReceptionist())
    	{
            PositionQuery pq;
    		cppcms::json::value jsonResponse = pq.getPosBySpec(specializationId);
    		jsonResponse.save(response().out(),cppcms::json::readable);
    	}
    }
    
    void specialistsByPos(std::string positionId){
    	if (isReceptionist())
    	{
            SpecialistQuery sq;
    		cppcms::json::value jsonResponse = sq.getSecialistsByPos(positionId);
    		jsonResponse.save(response().out(),cppcms::json::readable);
    	}
    }
    
    void specialistsByDate(std::string num, std::string date){

    	if (isReceptionist())
    	{
            TimetableQuery tq;
    		cppcms::json::value jsonResponse = tq.specialistsByDate(date, num);
    		jsonResponse.save(response().out(),cppcms::json::readable);
    	}
    }

    
    void newTimetableEntry(std::string timeId, std::string medcardId){
    	if (isReceptionist())
    	{
            TimetableQuery tq;
            tq.createAppointment(timeId, medcardId);
    	}
    }


    void getOrCreatePatient(){

		if (request().request_method() == "POST")
		{
			if (isReceptionist())
    		{
				std::pair<void *,size_t> data = request().raw_post_data();
		  		std::string postData(reinterpret_cast<char *>(data.first),data.second);
		  		const char * dataStart = reinterpret_cast<char *>(data.first);
		  		cppcms::json::value jsonRequest; 
		  		jsonRequest.load(dataStart, postData.data() + postData.size(), false);
    			PatientQuery pq;
                pq.createPatient(jsonRequest);
    		}
		}
		if (request().request_method() == "GET")
		{
			if (isReceptionist() || isDoctor())
				{
                    PatientQuery pq;
					std::string second_name = request().get("second_name");
		    		cppcms::json::value jsonResponse = pq.getPatientBySecondName(second_name);
		    		jsonResponse.save(response().out(),cppcms::json::readable);

				}	
		}
    	
    }


	void todayPatients(){
		if (isDoctor())
		{
            PatientQuery pq;
    		cppcms::json::value jsonResponse = pq.todayPatients(request().cookie_by_name("sid").value());
    		jsonResponse.save(response().out(),cppcms::json::readable);
		}

	}
	
	void medcardMeta(std::string medcardId){
		if (isDoctor())
		{
            PatientQuery pq;
    		cppcms::json::value jsonResponse = pq.getPatientById(medcardId);
    		jsonResponse.save(response().out(),cppcms::json::readable);
		}
	}
	
	void medcardHistory(std::string medcardId){
		if (isDoctor())
		{
    		std::string page_num = request().get("page");
		    cppcms::json::value jsonResponse;
            HistoryQuery hq;
            jsonResponse = hq.getHistoryRecord(medcardId, page_num);
    		jsonResponse.save(response().out(),cppcms::json::readable);	


		}
	}
	
	void medcardSurvey(std::string medcardId){
		if (isDoctor())
		{
            std::string page_num = request().get("page");
            cppcms::json::value jsonResponse;
            SurveyQuery sq;
            jsonResponse = sq.getSurveyRecord(medcardId, page_num);
            jsonResponse.save(response().out(),cppcms::json::readable);
		}
	}
	
	void newSurvey(){
		if (isDoctor())
		{
			if (request().request_method() == "POST")
			{
				std::pair<void *,size_t> data = request().raw_post_data();
		  		std::string postData(reinterpret_cast<char *>(data.first),data.second);
		  		const char * dataStart = reinterpret_cast<char *>(data.first);
		  		cppcms::json::value jsonData; 
		  		jsonData.load(dataStart, postData.data() + postData.size(), false);
			    SurveyQuery sq;
                sq.createSurveyRecord(jsonData, request().cookie_by_name("sid").value());
            }
		}
	}
	
	void newHistory(){
		if (isDoctor())
		{
			if (request().request_method() == "POST")
			{
                std::pair<void *,size_t> data = request().raw_post_data();
                std::string postData(reinterpret_cast<char *>(data.first),data.second);
                const char * dataStart = reinterpret_cast<char *>(data.first);
                cppcms::json::value jsonRequest;
                jsonRequest.load(dataStart, postData.data() + postData.size(), false);
                HistoryQuery hq;
                hq.createHistoryRecord(jsonRequest, request().cookie_by_name("sid").value());
			}
		}
	}



	void login()  
	{  
		if(request().request_method()=="POST") 
		{
            SessionQuery sq;
			if ((sq.authentificate(request().post("login"), request().post("password")))
                && sq.checkSession(request().post("login"), request().post("password")))
			{
                std::string sid = generate_sid();
                cppcms::http::cookie user_cookie = cppcms::http::cookie(std::string("user"), request().post("login"));
                user_cookie.expires(time(nullptr) + 864000);
				response().set_cookie(user_cookie);
				cppcms::http::cookie sid_cookie = cppcms::http::cookie(std::string("sid"), sid);
                sid_cookie.expires(time(nullptr) + 864000);
                response().set_cookie(sid_cookie);
                sq.createSession(request().post("login"), request().post("password"), sid);
			}
		}
	}
	
	void logout()  
	{  	
		cppcms::http::cookie sid_cookie = request().cookie_by_name("sid");
        cppcms::http::cookie user_cookie = request().cookie_by_name("user");
        SessionQuery sq;
        sq.deleteSession(sid_cookie.value());
        sid_cookie.expires(0);
        user_cookie.expires(0);
        response().set_cookie(sid_cookie);
        response().set_cookie(user_cookie);
	}

	bool isDoctor(){
		SessionQuery sq;
        return sq.isDoctor(request().cookie_by_name("sid").value());
	}

	bool isReceptionist(){
        SessionQuery sq;
        return sq.isReceptionist(request().cookie_by_name("sid").value());
	}

	std::string generate_sid(){
	    static const std::string alphanum("0123456789abcdefghijklmnopqrstuvwxyz"
                                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ-+=_&");
	    srand(time(0));
	    int length = 10 + rand() % 26;
	    std::string rand_string;
	    for (int i = 0; i < length; ++i) {
	        rand_string.append(1, alphanum.at(rand() % 67));
	    }
	    return rand_string;
	}    

};


int main(int argc,char ** argv)  
{  
    try {  
        	cppcms::service srv(argc,argv);
    		srv.applications_pool().mount(cppcms::applications_factory<Clinic>());
    	    srv.run();  
}  
catch(std::exception const &e) {  
    std::cerr<<e.what()<<std::endl;  
}
}  