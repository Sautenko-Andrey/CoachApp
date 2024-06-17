#include "databasemanager.h"

DataBaseManager::DataBaseManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE","Connection");
    m_db.setDatabaseName(path_to_db);

    if(!m_db.open()){
        qDebug() << "Couldn't open the data base.";
        exit(1);
    }
}


DataBaseManager::~DataBaseManager()
{
    m_db.close();
}


QSqlDatabase& DataBaseManager::getDB()
{
    return m_db;
}
