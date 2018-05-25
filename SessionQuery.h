//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_SESSIONQUERY_H
#define CONNECTORTEST_SESSIONQUERY_H

#include "dbQuery.h"

class SessionQuery : public dbQuery {
public:

    bool authentificate(string login, string password);

    bool checkSession(string login, string password);

    void createSession(string login, string password, string sid);

    void deleteSession(string sid);

    bool isDoctor(string sid);

    bool isReceptionist(string sid);
};


#endif //CONNECTORTEST_SESSIONQUERY_H
