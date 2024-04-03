#include "validator.h"
#include <sstream>

void OfertaValidator::validateOferta(const Oferta& o) {
    char msgs[100] = "";
    if (o.getPret() < 0)
        strcat_s(msgs, "Pret negativ!!!\n");
    if (o.getTip().size() == 0)
        strcat_s(msgs, "Tip vid!!!\n");
    if (o.getDestinatie().size() == 0)
        strcat_s(msgs, "Destinatie vida!!!\n");
    if (o.getDenumire().size() == 0)
        strcat_s(msgs, "Denumire vida!!!\n");
    if (strlen(msgs)) {
        throw ValidateException(msgs);
    }
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
    out << ex.msgs;
    return out;
}
