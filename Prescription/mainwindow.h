#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSqlDatabase>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    //méthodes
    void chargeListeMedecins();//Charge la liste de tous les médecins
    void ouvreBase();//Ouvre une connexion à la base de données
    void verifBase();//Vérifie si la base de données existe, et la crée si besoins
    void jeuEssais();//Insertion d'un jeu d'essais
    void chargeListePatient();//Charge la liste de tous les patients

    //propriétés
        QVector<int> vectorIdMedecins;
        QSqlDatabase base;

};

#endif // MAINWINDOW_H
