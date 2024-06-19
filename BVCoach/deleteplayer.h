#ifndef DELETEPLAYER_H
#define DELETEPLAYER_H

#include <QDialog>
#include "databasemanager.h"

namespace Ui {
class DeletePlayer;
}

class DeletePlayer : public QDialog
{
    Q_OBJECT

public:
    explicit DeletePlayer(QWidget *parent = nullptr);
    ~DeletePlayer();

private slots:
    void on_deleteButton_clicked();

private:
    Ui::DeletePlayer *ui;

    DataBaseManager dbManager;
};

#endif // DELETEPLAYER_H
