#include "addplayer.h"
#include "ui_addplayer.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <algorithm>
#include <QPixmap>
#include <QSqlQuery>



enum class DefaultViewSettings {
    DEFAULT_AGE = 18,
    MIN_AGE = 8,
    MAX_AGE = 80,
    MALE = 1,
    FEMALE = 0,
    DEFAULT_HEIGHT = 190,
    MIN_HEIGHT = 150,
    MAX_HEIGHT = 230,
    IMAGE_SQAURE_SIZE = 300
};


AddPlayer::AddPlayer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPlayer)
{
    ui->setupUi(this);

    // Age box settings
    ui->ageSpinBox->setValue(static_cast<int>(DefaultViewSettings::DEFAULT_AGE));
    ui->ageSpinBox->setMinimum(static_cast<int>(DefaultViewSettings::MIN_AGE));
    ui->ageSpinBox->setMaximum(static_cast<int>(DefaultViewSettings::MAX_AGE));

    // Sex radio buttons settings
    ui->maleRadioButton->setChecked(true);

    // Height box settings
    ui->heightSpinBox->setMinimum(static_cast<int>(DefaultViewSettings::MIN_HEIGHT));
    ui->heightSpinBox->setMaximum(static_cast<int>(DefaultViewSettings::MAX_HEIGHT));
    ui->heightSpinBox->setValue(static_cast<int>(DefaultViewSettings::DEFAULT_HEIGHT));


    // Make focus on the first name line
    ui->firstNameLine->setFocus();


}

AddPlayer::~AddPlayer()
{
    delete ui;
}

void AddPlayer::on_clearAllButton_clicked()
{
    ui->firstNameLine->clear();
    ui->lastNameLine->clear();
    ui->ageSpinBox->setValue(static_cast<int>(DefaultViewSettings::DEFAULT_AGE));
    ui->maleRadioButton->setChecked(true);
    ui->heightSpinBox->setValue(static_cast<int>(DefaultViewSettings::DEFAULT_HEIGHT));
    ui->phoneLine->clear();
    ui->homeTownLine->clear();

    ui->firstNameLine->setFocus();
}


void AddPlayer::on_saveButton_clicked()
{

    // getting data from the dialog
    QString player_first_name = ui->firstNameLine->text();
    QString player_last_name = ui->lastNameLine->text();
    int player_age = ui->ageSpinBox->value();
    int player_height = ui->heightSpinBox->value();
    int player_sex;
    ui->femaleRadioButton->isChecked() ? player_sex = 0 : player_sex = 1;
    QString player_hometown = ui->homeTownLine->text();
    QString player_phone = ui->phoneLine->text();

    // test
    qDebug() << player_first_name;
    qDebug() << player_last_name;
    qDebug() << player_age;
    qDebug() << player_height;
    qDebug() << player_sex;
    qDebug() << player_hometown;
    qDebug() << player_phone;




    // creating a new folder with players images
    QDir dir;

    // creating a players images directory
    if(!dir.exists(QDir::homePath() + "/Players_images")){
        dir.mkpath(QDir::homePath() + "/Players_images");
    }

    //saving image in the folder
    QString player_name = ui->firstNameLine->text() + "_" + ui->lastNameLine->text();

    // remove all whitespaces
    player_name = player_name.trimmed().replace(" ", "_");

    QString image_name = QDir::homePath() + "/Players_images/" + player_name + ".jpeg";
    qDebug() << image_name;

    if(!image.save(image_name)){
        QMessageBox::warning(this, "Image error!", "Couldn't save an image!");
    }

    // making a query
    QSqlQuery query(dbManager.getDB());

    query.prepare("INSERT INTO Player"
                  "(first_name, last_name, age, sex, height, home_town, phone, picture)"
                  " VALUES"
                  "(:f_name, :l_name, :p_age, :p_sex, :p_height, :p_city, :p_phone, :p_img);");

    query.bindValue(":f_name", player_first_name);
    query.bindValue(":l_name", player_last_name);
    query.bindValue(":p_age", player_age);
    query.bindValue(":p_sex", player_sex);
    query.bindValue(":p_height", player_height);
    query.bindValue(":p_city", player_hometown);
    query.bindValue(":p_phone", player_phone);
    query.bindValue(":p_img", image_name);

    if(!query.exec()){
        QMessageBox::warning(this, "Database problem", "Couldn't save new player.");
        return;
    }
    else{
        // clear all lines
        ui->firstNameLine->clear();
        ui->lastNameLine->clear();
        ui->ageSpinBox->setValue(static_cast<int>(DefaultViewSettings::DEFAULT_AGE));
        ui->heightSpinBox->setValue(static_cast<int>(DefaultViewSettings::DEFAULT_HEIGHT));
        ui->maleRadioButton->setChecked(true);
        ui->homeTownLine->clear();
        ui->phoneLine->clear();
        ui->playerImageLabel->clear();
    }
}


void AddPlayer::on_addImageButton_clicked()
{
    const QString player_image_path = QFileDialog::getOpenFileName(this, "Select an image");
    //QImage image;
    if(!image.load(player_image_path)){
        QMessageBox::warning(this, "File error!", "Couldn't load an image!");
    }

    // displaying player's image
    ui->playerImageLabel->setPixmap(QPixmap::fromImage(image));

    ui->playerImageLabel->setMaximumSize(QSize(static_cast<int>(DefaultViewSettings::IMAGE_SQAURE_SIZE),
                                               static_cast<int>(DefaultViewSettings::IMAGE_SQAURE_SIZE)));
    ui->playerImageLabel->setMinimumSize(QSize(static_cast<int>(DefaultViewSettings::IMAGE_SQAURE_SIZE),
                                               static_cast<int>(DefaultViewSettings::IMAGE_SQAURE_SIZE)));

    ui->playerImageLabel->setScaledContents(true);
}


void AddPlayer::on_deleteImageButton_clicked()
{
    ui->playerImageLabel->clear();
}

