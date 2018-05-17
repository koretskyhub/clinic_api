//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_SESSIONQUERY_H
#define CONNECTORTEST_SESSIONQUERY_H

#include "dbQuery.h"

class SessionQuery: public dbQuery {
public:

    bool authentificate(std::string login, std::string password);

    bool checkSession(std::string login, std::string password);

    void createSession(std::string login, std::string password, std::string sid);

    void deleteSession(std::string sid);

    bool isDoctor(std::string sid);

    bool isReceptionist(std::string sid);
};


#endif //CONNECTORTEST_SESSIONQUERY_H
