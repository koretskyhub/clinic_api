//
// Created by mike on 17.05.18.
//

#ifndef CONNECTORTEST_SESSIONQUERY_H
#define CONNECTORTEST_SESSIONQUERY_H

#include "dbQuery.h"

class SessionQuery : public dbQuery {
public:

    bool authentificate(const std::string& login, const std::string& password);

    bool checkSession(const std::string& login, const std::string& password);

    void createSession(const std::string& login, const std::string& password, const std::string& sid);

    void deleteSession(const std::string& sid);

    bool isDoctor(const std::string& sid);

    bool isReceptionist(const std::string& sid);
};


#endif //CONNECTORTEST_SESSIONQUERY_H
