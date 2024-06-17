#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "addplayer.h"
#include <memory>


enum class typeOfTraining {
    TACTICAL, TECHNICAL, PHYSICAL
};

enum class DefaultViewSettings {
    MINIMUM_PLAYERS = 1, STANDART_PLAYERS = 2,
    REGULAR_TRAINING_DURATION = 120,
    MINIMUM_TRAINING_DURATION = 45,
    MAXIMUM_TRAINING_DURATION = 240
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Calendar settings
    ui->calendarWidget->setLocale(QLocale::English);
    ui->calendarWidget->setGridVisible(true);
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui->calendarWidget->setFirstDayOfWeek(Qt::Monday);


    // Previous settings for another widget
    ui->timeOfDayComboBox->addItems(timeOfDay);

    // Players amount spinbox default settings
    ui->playersSpinBox->setValue(static_cast<int>(DefaultViewSettings::STANDART_PLAYERS));
    ui->playersSpinBox->setMinimum(static_cast<int>(DefaultViewSettings::MINIMUM_PLAYERS));

    // Training duration default settings
    ui->durationSpinBox->setMinimum(static_cast<int>(DefaultViewSettings::MINIMUM_TRAINING_DURATION));
    ui->durationSpinBox->setMaximum(static_cast<int>(DefaultViewSettings::MAXIMUM_TRAINING_DURATION));
    ui->durationSpinBox->setValue(static_cast<int>(DefaultViewSettings::REGULAR_TRAINING_DURATION));

    // Type of training combobox default settings
    ui->typeOfTrainingComboBox->addItems(typesOfTraining);

    QSqlQuery query(dbManager.getDB());

    if(query.exec("SELECT first_name, second_name FROM Player ORDER BY first_name")){
        QStringList all_players;
        while(query.next()){
            all_players.append(query.value(0).toString() + " " + query.value(1).toString());
        }

        // Players list combobox settings
        ui->picPlayerComboBox->addItems(all_players);
    }
    else{
        QMessageBox::warning(this, "Query error",
                                 "Couldn't select players from the database."
                             "Probably players database is empty. Fill it.");
    }

    // working with exercises list

    // fill exercises list
    QStringListModel *default_exercises_model = new QStringListModel(this);

    QSqlQuery exer_query(dbManager.getDB());

    if(exer_query.exec("SELECT short_name FROM Exercise WHERE type = 1")){
        QStringList exercises;
        while(exer_query.next()){
            exercises.append(exer_query.value(0).toString());
        }

        default_exercises_model->setStringList(exercises);
        ui->exercisesListView->setModel(default_exercises_model);
    }
    else{
        qDebug() << "Couldn't open DB for default exercises view";
    }

    ui->selectedExercisesList->setAcceptDrops(true);
    ui->selectedExercisesList->setDragEnabled(false);

    ui->exercisesListView->setAcceptDrops(false);
    ui->exercisesListView->setDragEnabled(true);


    // connections
    connect(ui->typeOfTrainingComboBox, SIGNAL(currentTextChanged(QString)),
               this, SLOT(changeTypeOfTrainComboBox()));

    connect(ui->deleteAllExercisesButton, SIGNAL(clicked(bool)),
            ui->selectedExercisesList, SLOT(clear()));

}

void MainWindow::getExercises(const int type_id)
{
    QSqlQuery query(dbManager.getDB());

    query.prepare("SELECT short_name FROM Exercise WHERE type = :train_id");
    query.bindValue(":train_id", type_id);

    if(!query.exec()){
        qDebug() << "Problem with training exercises data while query.";
        return;
    }

    exercises_model = new QStringListModel(this);

    QStringList exercises;

    while(query.next()){
        exercises.append(query.value(0).toString());
    }

    exercises_model->setStringList(exercises);
    ui->exercisesListView->setModel(exercises_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeTypeOfTrainComboBox()
{
    switch (ui->typeOfTrainingComboBox->currentIndex()) {
    case static_cast<int>(typeOfTraining::TACTICAL):
        getExercises(1);
        break;

    case static_cast<int>(typeOfTraining::TECHNICAL):
        getExercises(2);
        break;

    case static_cast<int>(typeOfTraining::PHYSICAL):
        getExercises(3);
        break;
    }
}


void MainWindow::on_deleteExerciseButton_clicked()
{
    QListWidgetItem *item = ui->selectedExercisesList->takeItem(ui->selectedExercisesList->currentRow());
    delete item;
}



void MainWindow::on_actionAdd_anew_player_triggered()
{
    addPlayerAction = std::make_unique<AddPlayer>(this);
    addPlayerAction->show();
}

