#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Choisir le bon codec
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    this->ouvreBase();
    this->chargeListePatient();
    this->chargeListeMedecins();
    this->chargeListePrescription();
    this->chargeParametre();
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
    this->base.exec("select docNum, docNom, docNumSS, docAdresse1, docAdresse2, docCP, docVille, docTel from medecin");
    this->base.exec("select presNum, presDuree, presDateFin, presModRenouv, presType, patNum from patient");
    this->base.exec("select dureeDSI, medCP, medVille, dureeOrdo from defaut");

    if (this->base.lastError().isValid())//si la requete renvoie une erreur
    {
        this->base.exec("create table medecin (docNum integer primary key, docNom varchar(20), docNumSS varchar(15), docAdresse1 varchar(50), docAdresse2 varchar(50), docCP varchar(5), docVille varchar(30), docTel varchar(10));");
        this->base.exec("create table patient (patNum integer primary key, patNom varchar(20), patNumSS varchar(15), patDoc integer, foreign key (patDoc) references medecin(patNum));");
        this->base.exec("create table prescription (presNum integer primary key, presDuree integer, presDateFin date, presModRenouv varchar(10), presType varchar(10), patNum integer, foreign key (patNum) references patient(patNum));");
        this->base.exec("create table defaut (dureeDSI integer , medCP varchar(5), medVille varchar(45),dureeOrdo integer);");
        this->jeuEssais();
    }
}

void MainWindow::jeuEssais()
{
    this->base.exec("insert into patient (patNom,patNumSS,patDoc) values('Bouveuil','125364738495049',1);");
    this->base.exec("insert into medecin (docNom, docNumSS, docAdresse1, docCP, docVille, docTel) values('Dr Muller','010203040506070','16 rue carnot','05000','Gap','1122334455')");
    this->base.exec("insert into prescription (presDuree, presDateFin, presModRenouv, presType, patNum) values(6,'2013-12-02','patient','DSI',1)");
    this->base.exec("insert into defaut (dureeDSI,medCP,medVille,dureeOrdo) values(3,'05000','Gap',6);");
}

void MainWindow::chargeListePatient()
{
    //vidage des listes des patients
    ui->listWidgetPatients->clear();

    /**************************************/
    /** chargement de la liste de patient */
    /**************************************/
    //requete
    QSqlQuery req;
    if (req.exec("select patNum, patNom, patNumSS, patDoc from patient order by patNom;"))
    {
        while(req.next())
        {
               ui->listWidgetPatients->addItem(req.value(1).toString()+" ("+req.value(2).toString()+")");
               this->vectorIdPatients.push_back(req.value(0).toInt());
        }
    }
}

void MainWindow::chargeListeMedecins()
{
    //vidange
    ui->listWidgetMedecins->clear();
    ui->comboBoxPatientMedecin->clear();
    this->vectorIdMedecins.clear();

    /**************************************/
    /** chargement de la liste de médecin */
    /**************************************/
    QSqlQuery requete;
    if(requete.exec("SELECT * FROM medecin ORDER BY docNom;"))
    {
        ui->comboBoxPatientMedecin->addItem("Sélectionner un médecin");
        this->vectorIdMedecins.push_back(-1);
        while(requete.next())
        {
           ui->listWidgetMedecins->addItem(requete.value(1).toString()+" ("+requete.value(2).toString()+")");
           ui->comboBoxPatientMedecin->addItem(requete.value(1).toString());
           this->vectorIdMedecins.push_back(requete.value(0).toInt());
        }
    }
}

void MainWindow::chargeListePrescription()
{
    //vidage des listes des patients
    ui->listWidgetPrescriptions->clear();

    /****************************************/
    /** chargement de la liste prescription */
    /****************************************/
    //requete
    QSqlQuery req;
    if (req.exec("select * from prescription order by presNum"))
    {
        while(req.next())
        {
               ui->listWidgetPrescriptions->addItem(req.value(2).toString()+" ("+req.value(4).toString()+")");

        }
    }
}



void MainWindow::on_listWidgetPatients_clicked(QModelIndex index)
{
    QSqlQuery res=this->base.exec("select patNom, patNumSS, patDoc from patient where patNum="+QString::number(this->vectorIdPatients.value(ui->listWidgetPatients->currentIndex().row()))+";");
    //si le patient a bien été trouvé
    if (res.first())
    {
        //affichage dans l'interface
        ui->lineEditPatientNom->setText(res.value(0).toString());
        ui->lineEditPatientNumSS->setText(res.value(1).toString());
        ui->comboBoxPatientMedecin->setCurrentIndex(this->vectorIdMedecins.lastIndexOf(res.value(2).toInt()));
        ui->pushButtonPatientSupprimer->setEnabled(true);
        ui->pushButtonPatientModifier->setEnabled(true);
        ui->pushButtonPatientAbandonner->setEnabled(true);
    }
}

void MainWindow::on_pushButtonPatientSupprimer_clicked()
{
    this->base.exec("delete from patient where patNum="+QString::number(this->vectorIdPatients.value(ui->listWidgetPatients->currentIndex().row()))+";");
    this->chargeListePatient();
    this->videLineEditPatient();
}

void MainWindow::on_pushButtonPatientModifier_clicked()
{
    this->base.exec("update patient set patNom='"+ui->lineEditPatientNom->text().trimmed()+"', patNumSS='"+ui->lineEditPatientNumSS->text().trimmed()+"', patDoc="+QString::number(this->vectorIdMedecins.value(ui->comboBoxPatientMedecin->currentIndex()))+" where patNum="+QString::number(this->vectorIdPatients.value(ui->listWidgetPatients->currentIndex().row()))+";");
    this->chargeListePatient();
    this->videLineEditPatient();
}

void MainWindow::videLineEditPatient()
{
    ui->lineEditPatientNom->clear();
    ui->lineEditPatientNumSS->clear();
    ui->comboBoxPatientMedecin->setCurrentIndex(0);
    ui->pushButtonPatientModifier->setEnabled(false);
    ui->pushButtonPatientSupprimer->setEnabled(false);
    ui->pushButtonPatientAbandonner->setEnabled(false);
    ui->pushButtonPatientAjouter->setEnabled(false);
}

void MainWindow::on_pushButtonPatientAbandonner_clicked()
{
    this->videLineEditPatient();
}

bool MainWindow::saisieOKMedecin()
{
    return ( ui->lineEditMedecinNom->text().trimmed().length()*ui->lineEditMedecinNumSS->text().trimmed().length()*ui->lineEditMedecinAdr1->text().trimmed().length()*ui->lineEditMedecinCP->text().trimmed().length()*ui->lineEditMedecinVille->text().trimmed().length()*ui->lineEditMedecinTel->text().trimmed().length()>0);
}


void MainWindow::on_lineEditMedecinNom_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());
}

void MainWindow::on_lineEditMedecinNumSS_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());

}

void MainWindow::on_lineEditMedecinCP_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());
}

void MainWindow::on_lineEditMedecinVille_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());
}

void MainWindow::on_lineEditMedecinTel_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());

}

void MainWindow::on_lineEditMedecinAdr1_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());

}

void MainWindow::on_lineEditMedecinAdr2_textChanged(QString )
{
    ui->pushButtonMedecinAjouter->setEnabled(this->saisieOKMedecin());
    ui->pushButtonMedecinAbandonner->setEnabled(this->saisieOKMedecin());
}

void MainWindow::on_pushButtonMedecinAjouter_clicked()
{
    this->base.exec("insert into medecin (docNom,docNumSS,docAdresse1,docAdresse2,docCP,docVille,docTel) values ('"+ui->lineEditMedecinNom->text().trimmed()+"','"+ui->lineEditMedecinNumSS->text().trimmed()+"','"+ui->lineEditMedecinAdr1->text().trimmed()+"','"+ui->lineEditMedecinAdr2->text().trimmed()+"','"+ui->lineEditMedecinCP->text().trimmed()+"','"+ui->lineEditMedecinVille->text().trimmed()+"','"+ui->lineEditMedecinTel->text().trimmed()+"');");
    this->chargeListeMedecins();
    this->videLineEditMedecin();
}

void MainWindow::on_pushButtonMedecinSupprimer_clicked()
{
    this->base.exec("delete from medecin where docNum="+QString::number(this->vectorIdMedecins.value(ui->listWidgetMedecins->currentIndex().row()))+";");
    this->chargeListeMedecins();
    this->videLineEditMedecin();
}

void MainWindow::on_listWidgetMedecins_clicked(QModelIndex index)
{
    QSqlQuery res=this->base.exec("select * from medecin where docNum="+QString::number(this->vectorIdMedecins.value(ui->listWidgetMedecins->currentIndex().row()))+";");
    if (res.first())
    {
        //affichage dans l'interface
        ui->lineEditMedecinNom->setText(res.value(1).toString());
        ui->lineEditMedecinNumSS->setText(res.value(2).toString());
        ui->lineEditMedecinAdr1->setText(res.value(3).toString());
        ui->lineEditMedecinAdr2->setText(res.value(4).toString());
        ui->lineEditMedecinCP->setText(res.value(5).toString());
        ui->lineEditMedecinVille->setText(res.value(6).toString());
        ui->lineEditMedecinTel->setText(res.value(7).toString());
        ui->pushButtonMedecinSupprimer->setEnabled(true);
        ui->pushButtonMedecinModifier->setEnabled(true);
    }
}

void MainWindow::on_pushButtonMedecinModifier_clicked()
{
    this->base.exec("update medecin set docNom='"+ui->lineEditMedecinNom->text().trimmed()+"', docNumSS='"+ui->lineEditMedecinNumSS->text().trimmed()+"', docAdresse1='"+ui->lineEditMedecinAdr1->text().trimmed()+"', docAdresse2='"+ui->lineEditMedecinAdr2->text().trimmed()+"', docCP='"+ui->lineEditMedecinCP->text().trimmed()+"', docVille='"+ui->lineEditMedecinVille->text().trimmed()+"', docTel='"+ui->lineEditMedecinTel->text().trimmed()+"' where docNum="+QString::number(this->vectorIdMedecins.value(ui->listWidgetMedecins->currentIndex().row()))+";");
    this->chargeListeMedecins();
    this->videLineEditMedecin();
}

void MainWindow::on_pushButtonMedecinAbandonner_clicked()
{
       this->videLineEditMedecin();
}

void MainWindow::videLineEditMedecin()
{
    ui->lineEditMedecinNom->clear();
    ui->lineEditMedecinNumSS->clear();
    ui->lineEditMedecinAdr1->clear();
    ui->lineEditMedecinAdr2->clear();
    ui->lineEditMedecinCP->clear();
    ui->lineEditMedecinVille->clear();
    ui->lineEditMedecinTel->clear();
    ui->pushButtonMedecinAbandonner->setEnabled(false);
    ui->pushButtonMedecinAjouter->setEnabled(false);
    ui->pushButtonMedecinModifier->setEnabled(false);
    ui->pushButtonMedecinSupprimer->setEnabled(false);
}

void MainWindow::on_listWidgetPrescriptions_clicked(QModelIndex index)
{
    //QSqlQuery res=this->base.exec("select * from medecin where id="+QString::number(this->vectorIdMedecins.value(ui->listWidgetMedecins->currentIndex().row()))+";");
    int numLigneListePres=ui->listWidgetPrescriptions->currentIndex().row();
    int idPres=this->vectorIdPrescription.value(numLigneListePres);
    QSqlQuery resPres;
    resPres=this->base.exec("select * from prescription where presNum="+QString::number(idPres)+";");
    //si l'étudiant a bien été trouvé
    if (resPres.first())
    {
        ui->pushButtonPrescriptionSupprimer->setEnabled(true);
        ui->pushButtonPrescriptionModifier->setEnabled(true);
        //ui->comboBoxPrescriptionPatient->addItem(resPres.value(1).toString());
    }
}

void MainWindow::on_pushButtonPrescriptionSupprimer_clicked()
{
    this->base.exec("delete from prescription where presNum="+QString::number(this->vectorIdPrescription.value(ui->listWidgetPrescriptions->currentIndex().row()))+";");
    this->chargeListePrescription();
}

void MainWindow::on_pushButtonPatientAjouter_clicked()
{
    this->base.exec("insert into patient (patNom, patNumSS, patDoc) values ('"+ui->lineEditPatientNom->text().trimmed()+"','"+ui->lineEditPatientNumSS->text().trimmed()+"','"+QString::number(this->vectorIdMedecins.value(ui->comboBoxPatientMedecin->currentIndex()))+"');");
    this->chargeListePatient();
    this->videLineEditPatient();
}

bool MainWindow::saisieOKPatient()
{
    return ( ui->lineEditPatientNom->text().trimmed().length()*ui->lineEditPatientNumSS->text().trimmed().length()*ui->comboBoxPatientMedecin->currentText().length()>0);
}
void MainWindow::on_lineEditPatientNom_textChanged(QString )
{
    ui->pushButtonPatientAbandonner->setEnabled(this->saisieOKPatient());
    ui->pushButtonPatientAjouter->setEnabled(this->saisieOKPatient());
}

void MainWindow::on_lineEditPatientNumSS_textChanged(QString )
{
    ui->pushButtonPatientAbandonner->setEnabled(this->saisieOKPatient());
    ui->pushButtonPatientAjouter->setEnabled(this->saisieOKPatient());
}

void MainWindow::on_comboBoxPatientMedecin_textChanged(QString )
{
    ui->pushButtonPatientAbandonner->setEnabled(this->saisieOKPatient());
    ui->pushButtonPatientAjouter->setEnabled(this->saisieOKPatient());
}

void MainWindow::chargeParametre()
{

    /////////////////  CHARGEMENT  DES PARAMETRES  /////////////
    QSqlQuery requete;
    if(requete.exec("SELECT  medCP,medVille,dureeDSI,dureeOrdo FROM defaut;"))
    {
         while(requete.next())
         {
            ui->lineEditParametresCPMedecin->setText(requete.value(0).toString());
            ui->lineEditParametreVilleMedecin->setText(requete.value(1).toString());
            ui->spinBoxParametreDureeDSI->setValue(requete.value(2).toInt());
            ui->spinBoxPrescriptionDureeOdronnance->setValue(requete.value(3).toInt());
         }
    }

}

void MainWindow::on_pushButtonPrescriptionEnregistrer_clicked()
{
    QString medCP=ui->lineEditParametresCPMedecin->text();
    QString medVille=ui->lineEditParametreVilleMedecin->text();
    QString dureeDSI=ui->spinBoxParametreDureeDSI->text();
    QString dureeOrdo=ui->spinBoxPrescriptionDureeOdronnance->text();
    QSqlQuery newDefaut;
            if(newDefaut.exec("update defaut set medCP='"+medCP+"',medVille='"+medVille+"' ,dureeDSI="+dureeDSI+" ,dureeOrdo="+dureeOrdo+";"))
            {

            }
            else
            {

            }
}

void MainWindow::on_lineEditParametresCPMedecin_returnPressed()
{
    ui->lineEditParametreVilleMedecin->setFocus();
}

void MainWindow::on_lineEditParametreVilleMedecin_returnPressed()
{
    ui->spinBoxParametreDureeDSI->setFocus();
}

void MainWindow::on_spinBoxParametreDureeDSI_editingFinished()
{
    ui->spinBoxPrescriptionDureeOdronnance->setFocus();
}
