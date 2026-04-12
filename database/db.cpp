#include "db.h"
#include <iostream>

using namespace std;

MYSQL* DB::connect() {
    MYSQL *conn = mysql_init(NULL);

    if(!conn) {
        cout << "MySQL Initialization Failed" << endl;
        return NULL;
    }
    cout<<"Connecting to Railway DB...\n";

    my_bool ssl_mode = 0;
    mysql_options(conn, MYSQL_OPT_SSL_ENFORCE, &ssl_mode);
    mysql_options(conn, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &ssl_mode);

    if (!mysql_real_connect(
        conn, 
        "metro.proxy.rlwy.net", 
        "root", "dAWVEQVHxKdFROTdwAJFsktKJRdHNJOt", "railway", 23975, NULL, 0)) {
        cout << "Connection Failed: " << mysql_error(conn) << endl;
        return NULL;
    }
    return conn;
}