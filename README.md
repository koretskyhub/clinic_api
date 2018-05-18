# clinic_api
CPPCMS web-api server with MYSQL for Clinic system

#API для клиента врача

GET	
doctor/patients/date/today/ 
{
  "count": <int>,
  "patients": [
     {
         "medcard_id": <int>,

         "first_name":<string>,
         "second_name":<string>,
         "middle_name":<string>,
         "time" : <string>
     },
     {
       "medcard_id": <int>,
       "first_name":<string>,
       "second_name":<string>,
       "middle_name":<string>,
       "time" : <string>
     }
  ]
}

GET	
medcard/<int>/
{
  "medcard_id": <int>,
  "first_name"(фамилия):<string>,
  "second_name"(имя):<string>,
  "middle_name"(отчество):<string>,
  "number_of_police":<string>,
  "birthday": <string>, 
  "address": <string>,
  "telephone": <string>
}


GET
patients?second_name=<string>
{
   "count":<int>,
   "patients": [
     {
       "medcard_id": <int>,
       "first_name":<string>, 
       "second_name":<string>, 
       "middle_name":<string>   
     }
   ]
}       

GET
medcard/<int>/history/?page=<int>

{
  "count_pages": <int>,
  "current_page":<int>,
  "next_page": <int>,
  "prev_page":<int>,
  "history": [
    {
      "specialist": {
         "spesialist_id"
         "position":<string>,
         "first_name": <string>,
         "second_name": <string>,
         "middle_name": <string>
      },
      "symptoms": <string>,          
      "appointment": <string>,       
      "diagnosis": <string>,         
      "date": <string>               
    }
  ]
}

GET
medcard/<int>/survey/?page=<int>

{
  "count_pages": <int>,
  "current_page":<int>,
  "next_page": <int>,
  "prev_page":<int>,
  "survey": [
    {
      "specialist" : {
        "position":<string>,
        "first_name": <string>,
        "second_name": <string>,
        "middle_name": <string>
      }
      "type_of_survey" : <string>,
      "result": <string>,
      "date" : <string>
    }
  ]
}

POST	history/

{
  "medcard_id": <string>,
  "symptoms": <string>,          
  "appointment": <string>,       
  "diagnosis": <string>,           
}

POST
survey/

{
  "medcard_id": <string>,
  "type_of_survey": <string>,
  "result": <string>
}

#API для клиента регистратуры

POST  patients/

{
   "first_name": <string>,
   "second_name": <string>,
   "middle_name": <string>,
   "number_of_police": <string>,
   "birthday": <string>,          
   "address": <string>,
   "telephone": <string>
} 
GET specialisations/

{
  "count": <int>,
  "specializations": [
    {
      "specialization_id":<int>,
      "specialization_name": <string>
     }
  ]
}
GET specializations/<int>/positions/

{
  "count": <int>,
  "positions": [
    {
      "position_id":<int>,
      "position_name": <stirng>
    }
   ]
}
GET positions/<int>/spesialists/

{
  "count":<int>,
  "spesialists": [
    {
      "specialist_id": <int>,
      "first_name": <stirng>,
      "second_name": <string>,
      "middle_name": <string>
    }
  ]
}
GET specialists/<int>/timetable/<date>/

{
  "count": <int>,
  "free_place": [
    {
      "time_id":<int>,
      "date": <string>,
      "time": <string>
    }
  ]
}

POST timetable/<time_id>/medcard/<medcard_id>

GET patients/?second_name=<string>

{
  "count": <int>,
  "patients" : [
    {
      "medcard_id":<int>,
      "first_name": <string>,
      "second_name": <string>,
      "middle_name" : <string>
    }
  ]
}
