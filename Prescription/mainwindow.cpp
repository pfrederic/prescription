#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ouvreBase();
    this->chargeListePatient();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::chargeListeMedecins()
{
    //vidange
    ui->listWidgetMedecins->clear();
    this->vectorIdMedecins.clear();

    /////////////////  CHARGEMENT  DE LA LISTE  /////////////
    QSqlQuery requete;
    if(requete.exec("SELECT * FROM medecin ORDER BY docNom;"))
    {
         while(requete.next())
         {
            ui->listWidgetMedecins->addItem(requete.value(1).toString()+" ("+requete.value(2).toString()+")");
            this->vectorIdMedecins.push_back(requete.value(0).toInt());
         }
    }

}

void MainWindow::ouvreBase()
{
    base=QSqlDatabase::addDatabase("QSQLITE");
    //nom fichier qui contient la base sqlite3
    base.setDatabaseName("prescription.db");

    //ouverture de la base de données
    base.open();

    //si la base ne s'est pas ouverte correctement
    if(base.isOpen() != true)
    {
        QMessageBox::critical(this, "Erreur critique", "Impossible d'ouvrir la base de données.");
    }
    else
    {
        this->verifBase();
    }
}

void MainWindow::verifBase()
{
    this->base.exec("select patNum, patNom, PatNumSS, patDoc from patient");
    this->base.exec("select docNum, docNom, docNumSS, docAdresse1, docAdresse2, docCP, docVille, docTel");
    this->base.exec("select presNum, presDuree, presDateFin, presModRenouv, presType, patNum");
    this->base.exec("select dureeDSI, medCP, medVille, dureeOrdo");

    if (this->base.lastError().number()!=0)//si la requete renvoie une erreur
    {
        this->base.exec("create table patient (patNum integer primary key, patNom varchar(20), patNumSS varchar(15), patDoc integer);");
        this->base.exec("create table medecin (docNum integer primary key, docNom varchar(20), docNumSS varchar(15), docAdresse1 varchar(50), docAdresse2 varchar(50), docCP varchar(5), docVille varchar(30), docTel varchar(10));");
        this->base.exec("create table prescription (presNum integer primary key, presDuree integer, presDateFin date, presModRenouv varchar(10), presType varchar(10), patNum integer);");
        this->base.exec("create table defaut (dureeDSI integer , medCP varchar(5), medVille varchar(45),dureeOrdo integer);");
        this->jeuEssais();
 //       this->base.exec("commit;"); //fin transaction
    }
}

void MainWindow::jeuEssais()
{
    this->base.exec("insert into patient (patNom,patNumSS,patDoc) values('Bouveuil','125364738495049','Champier');");
}

void MainWindow::chargeListePatient()
{
    //vidage des listes des patients
    ui->listWidgetPatients->clear();

    /**************************************/
    /** chargement de la liste*************/
    /**************************************/
    //requete
    QSqlQuery req;
    if (req.exec("select * from patient order by patNom;"))
    {
        while(req.next())
        {
               ui->listWidgetPatients->addItem(req.value(1).toString()+" ("+req.value(2).toString()+")");

        }
    }
}
