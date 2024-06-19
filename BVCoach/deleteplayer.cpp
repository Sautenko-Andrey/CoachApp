#include "deleteplayer.h"
#include "ui_deleteplayer.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <string>

DeletePlayer::DeletePlayer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeletePlayer)
{
    ui->setupUi(this);

    // view settings
    ui->playersComboBox->setMinimumWidth(100);

    ui->playersComboBox->setPlaceholderText("Choose a player");

    // getting players data from database
    QSqlQuery query(dbManager.getDB());

    if(!query.exec("SELECT first_name, last_name, sex, age, id FROM Player ORDER BY id;")){
        QMessageBox::warning(this, "Error", "Couldn't load players data");
        return;
    }

    QStringList players_data;

    while(query.next()){

        QString first_name = query.value(0).toString();
        QString last_name = query.value(1).toString();
        QString sex;
        (query.value(2).toInt() == 1) ? sex = "male" : sex = "female";
        QString age = query.value(3).toString();
        QString id = query.value(4).toString();


        players_data.append(id + ", " + first_name + " " + last_name + ", " + sex + ", " + age);
    }

    ui->playersComboBox->addItems(players_data);
}

DeletePlayer::~DeletePlayer()
{
    delete ui;
}

void DeletePlayer::on_deleteButton_clicked()
{
    // make delete query
    QSqlQuery query(dbManager.getDB());

    // getting selected player
    std::string selected_player_id = ui->playersComboBox->currentText().toStdString();

    auto comma_pos = selected_player_id.find(",");

    std::string player_id = selected_player_id.substr(0, comma_pos);

    int id = stoi(player_id);

    query.prepare("DELETE FROM Player WHERE id = :selected_id;");

    query.bindValue(":selected_id", id);

    if(!query.exec()){
        QMessageBox::warning(this, "Error", "Couldn't delete the player. Probably a wrong name.");
        return;
    }

    QMessageBox::information(this, "Report", "Player has been successfully deleted.");

}
