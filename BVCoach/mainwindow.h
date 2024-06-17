#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "databasemanager.h"
#include "addplayer.h"
#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void changeTypeOfTrainComboBox();

    void on_deleteExerciseButton_clicked();


    //void on_deleteAllExercisesButton_clicked();

    void on_actionAdd_anew_player_triggered();

private:
    Ui::MainWindow *ui;

    DataBaseManager dbManager;

    QStringListModel *exercises_model;

    inline static const QStringList timeOfDay{
        "morning", "noon", "evening"
    };

    inline static const QStringList typesOfTraining{
        "tactical", "technical", "physical"
    };

    void getExercises(const int type_id);

    std::unique_ptr<AddPlayer> addPlayerAction;
};
#endif // MAINWINDOW_H
