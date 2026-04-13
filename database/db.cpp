#include "db.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MYSQL* DB::connect() {
    MYSQL *conn = mysql_init(NULL);

    if (!conn) {
        cout << "MySQL Initialization Failed" << endl;
        return NULL;
    }

    cout << "Connecting to Railway DB...\n";

    const char* host = getenv("DB_HOST");
    const char* user = getenv("DB_USER");
    const char* pass = getenv("DB_PASS");
    const char* db   = getenv("DB_NAME");
    const char* port_str = getenv("DB_PORT");

    if (!host || !user || !pass || !db || !port_str) {
        cout << "Environment variables not set!\n";
        return NULL;
    }

    int port = atoi(port_str);

    // DISABLE SSL SAFELY (works in MinGW + Linux)
    #ifdef MYSQL_OPT_SSL_ENFORCE
        my_bool ssl = 0;
        mysql_options(conn, MYSQL_OPT_SSL_ENFORCE, &ssl);
    #endif

    // CONNECT
    if (!mysql_real_connect(
        conn,
        host,
        user,
        pass,
        db,
        port,
        NULL,
        CLIENT_MULTI_STATEMENTS)) {

        cout << "Connection Failed: " << mysql_error(conn) << endl;
        return NULL;
    }
    return conn;
}