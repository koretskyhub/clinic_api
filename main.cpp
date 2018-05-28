#include "clinic.h"

using namespace std;

int main(int argc, char **argv) {
    try {
        cppcms::service srv(argc, argv);
        srv.applications_pool().mount(cppcms::applications_factory<Clinic>());
        srv.run();
    }
    catch (exception const &e) {
        cerr << e.what() << endl;
    }
}