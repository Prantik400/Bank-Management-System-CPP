#include "db.h"
#include <iostream>

using namespace std;

MYSQL* DB::connect() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "bank_user", "1234", "bank_system", 3306, NULL, 0)) {
        cout << "Connection Failed: " << mysql_error(conn) << endl;
        return NULL;
    }
    return conn;
}