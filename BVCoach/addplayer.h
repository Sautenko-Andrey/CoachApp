#ifndef ADDPLAYER_H
#define ADDPLAYER_H

#include <QDialog>
#include "databasemanager.h"
#include <QImage>

namespace Ui {
class AddPlayer;
}

class AddPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayer(QWidget *parent = nullptr);
    ~AddPlayer();

private slots:
    void on_clearAllButton_clicked();

    void on_saveButton_clicked();

    void on_addImageButton_clicked();

    void on_deleteImageButton_clicked();

private:
    Ui::AddPlayer *ui;

    DataBaseManager dbManager;

    QImage image;

};

#endif // ADDPLAYER_H
