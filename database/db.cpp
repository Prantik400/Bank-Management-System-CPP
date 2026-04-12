#include "db.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

MYSQL* DB::connect() {
    MYSQL *conn = mysql_init(NULL);

    if(!conn) {
        cout << "MySQL Initialization Failed" << endl;
        return NULL;
    }
    cout<<"Connecting to Railway DB...\n";
    
    const char*host = getenv("DB_HOST");
    const char*user = getenv("DB_USER");
    const char*pass = getenv("DB_PASS");
    const char*db = getenv("DB_NAME");
    const char*port_str = getenv("DB_PORT");

    if(!host || !user || !pass || !db || !port_str) {
        cout << "Environment variables not set!\n";
        return NULL;
    }

    int port =atoi(port_str); //SSL without strict verification
    my_bool ssl=0;
    mysql_options(conn, MYSQL_OPT_SSL_ENFORCE, &ssl);
    mysql_options(conn, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &ssl);
    if (!mysql_real_connect(
        conn, 
        host, 
        user, pass, db, port, NULL, 0)) {
        cout << "Connection Failed: " << mysql_error(conn) << endl;
        return NULL;
    }
    return conn;
}