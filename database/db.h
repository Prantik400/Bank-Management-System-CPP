#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>

class DB
{
    public:
        static MYSQL* connect();
};

#endif // DB_H