#pragma once
#include <string>
#include "Oferta.h"
#include <vector>
#include <cstring>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
    string msgs;
public:
    ValidateException(const string& errors) :msgs{ errors } {}
    //functie friend (vreau sa folosesc membru privat msg)

    string what() {
        return msgs;
    }

    friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class OfertaValidator {
public:
    void validateOferta(const Oferta& o);
};

