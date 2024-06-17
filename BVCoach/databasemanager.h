#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QDir>
#include <QString>

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager();

    QSqlDatabase& getDB();


private:
    QSqlDatabase m_db;

    inline static const QString path_to_db = QDir::homePath() + "/BVCoach/BVCoach/data.db";

};

#endif // DATABASEMANAGER_H
