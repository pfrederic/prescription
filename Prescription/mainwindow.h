#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSqlDatabase>
#include <QModelIndex>

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
    void ouvreBase();//Ouvre une connexion à la base de données
    void verifBase();//Vérifie si la base de données existe, et la crée si besoins
    void jeuEssais();//Insertion d'un jeu d'essais
    void chargeListePatient();//Charge la liste de tous les patients
    void chargeListeMedecins();//Charge la liste de tous les médecins
    void chargeListePrescription();//Charge la liste de tous les patients
    void videLineEditPatient();//Vide tous les lines edit de l'onglet patient
    void videLineEditMedecin();//Vide tous les lines edit de l'onglet médecin
    void chargeParametre();
    bool saisieOKMedecin();//vérifie si la saisie est OK pour activer les boutons de l'onglet medecin
    bool saisieOKPatient();//vérifie si la saisie est OK pour activer les boutons de l'onglet patient

    //propriétés
        QVector<int> vectorIdMedecins;
        QVector<int> vectorIdPatients;
        QVector<int> vectorIdPrescription;
        QSqlDatabase base;


private slots:
    void on_comboBoxPatientMedecin_textChanged(QString );
    void on_lineEditPatientNumSS_textChanged(QString );
    void on_lineEditPatientNom_textChanged(QString );
    void on_pushButtonPatientAjouter_clicked();
    void on_pushButtonPatientAbandonner_clicked();
    void on_pushButtonPatientModifier_clicked();
    void on_pushButtonPatientSupprimer_clicked();
    void on_listWidgetPatients_clicked(QModelIndex index);
    void on_pushButtonPrescriptionSupprimer_clicked();
    void on_listWidgetPrescriptions_clicked(QModelIndex index);
    void on_pushButtonMedecinAbandonner_clicked();
    void on_pushButtonMedecinModifier_clicked();
    void on_listWidgetMedecins_clicked(QModelIndex index);
    void on_pushButtonMedecinSupprimer_clicked();
    void on_pushButtonMedecinAjouter_clicked();
    void on_lineEditMedecinAdr2_textChanged(QString );
    void on_lineEditMedecinAdr1_textChanged(QString );
    void on_lineEditMedecinTel_textChanged(QString );
    void on_lineEditMedecinVille_textChanged(QString );
    void on_lineEditMedecinCP_textChanged(QString );
    void on_lineEditMedecinNumSS_textChanged(QString );
    void on_lineEditMedecinNom_textChanged(QString );
    void on_lineEditParametresCPMedecin_returnPressed();
    void on_lineEditParametreVilleMedecin_returnPressed();
    void on_spinBoxParametreDureeDSI_editingFinished();
    void on_pushButtonPrescriptionEnregistrer_clicked();
};

#endif // MAINWINDOW_H
