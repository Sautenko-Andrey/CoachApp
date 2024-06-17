#include "addplayer.h"
#include "ui_addplayer.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QImage>
#include <algorithm>
#include <QPixmap>


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
    // // creating a new folder with players images
    // QDir dir;


    // // creating a players images directory
    // if(!dir.exists(QDir::homePath() + "/Players_images")){
    //     dir.mkpath(QDir::homePath() + "/Players_images");
    // }

    // //saving image in the folder
    // QString player_name = ui->firstNameLine->text() + "_" + ui->lastNameLine->text();

    // // remove all whitespaces
    // player_name = player_name.trimmed().replace(" ", "_");

    // if(!image.save(QDir::homePath() + "/Players_images/" + player_name + ".jpeg")){
    //     QMessageBox::warning(this, "Image error!", "Couldn't save an image!");
    // }

}


void AddPlayer::on_addImageButton_clicked()
{
    const QString path = QFileDialog::getOpenFileName(this, "Select an image");
    QImage image;
    if(!image.load(path)){
        QMessageBox::warning(this, "File error!", "Couldn't load an image!");
    }

    // // creating a new folder with players images
    // QDir dir;


    // // creating a players images directory
    // if(!dir.exists(QDir::homePath() + "/Players_images")){
    //     dir.mkpath(QDir::homePath() + "/Players_images");
    // }

    // //saving image in the folder
    // QString player_name = ui->firstNameLine->text() + "_" + ui->lastNameLine->text();

    // // remove all whitespaces
    // player_name = player_name.trimmed().replace(" ", "_");

    // if(!image.save(QDir::homePath() + "/Players_images/" + player_name + ".jpeg")){
    //     QMessageBox::warning(this, "Image error!", "Couldn't save an image!");
    // }

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

