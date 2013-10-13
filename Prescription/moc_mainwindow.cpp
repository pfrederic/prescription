/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Oct 13 17:59:47 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      57,   51,   11,   11, 0x08,
     113,   11,   11,   11, 0x08,
     160,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     286,   11,   11,   11, 0x08,
     327,   11,   11,   11, 0x08,
     366,   11,   11,   11, 0x08,
     406,   51,   11,   11, 0x08,
     449,   11,   11,   11, 0x08,
     494,   51,   11,   11, 0x08,
     542,   11,   11,   11, 0x08,
     583,   11,   11,   11, 0x08,
     622,   51,   11,   11, 0x08,
     665,   11,   11,   11, 0x08,
     705,   11,   11,   11, 0x08,
     743,   11,   11,   11, 0x08,
     787,   11,   11,   11, 0x08,
     831,   11,   11,   11, 0x08,
     874,   11,   11,   11, 0x08,
     919,   11,   11,   11, 0x08,
     961,   11,   11,   11, 0x08,
    1006,   11,   11,   11, 0x08,
    1049,   11,   11,   11, 0x08,
    1096,   11,   11,   11, 0x08,
    1145,   11,   11,   11, 0x08,
    1191,   11,   11,   11, 0x08,
    1235,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_pushButtonValeurParDefaut_clicked()\0"
    "index\0on_comboBoxPrescriptionPatient_currentIndexChanged(int)\0"
    "on_comboBoxPatientMedecin_textChanged(QString)\0"
    "on_lineEditPatientNumSS_textChanged(QString)\0"
    "on_lineEditPatientNom_textChanged(QString)\0"
    "on_pushButtonPatientAjouter_clicked()\0"
    "on_pushButtonPatientAbandonner_clicked()\0"
    "on_pushButtonPatientModifier_clicked()\0"
    "on_pushButtonPatientSupprimer_clicked()\0"
    "on_listWidgetPatients_clicked(QModelIndex)\0"
    "on_pushButtonPrescriptionSupprimer_clicked()\0"
    "on_listWidgetPrescriptions_clicked(QModelIndex)\0"
    "on_pushButtonMedecinAbandonner_clicked()\0"
    "on_pushButtonMedecinModifier_clicked()\0"
    "on_listWidgetMedecins_clicked(QModelIndex)\0"
    "on_pushButtonMedecinSupprimer_clicked()\0"
    "on_pushButtonMedecinAjouter_clicked()\0"
    "on_lineEditMedecinAdr2_textChanged(QString)\0"
    "on_lineEditMedecinAdr1_textChanged(QString)\0"
    "on_lineEditMedecinTel_textChanged(QString)\0"
    "on_lineEditMedecinVille_textChanged(QString)\0"
    "on_lineEditMedecinCP_textChanged(QString)\0"
    "on_lineEditMedecinNumSS_textChanged(QString)\0"
    "on_lineEditMedecinNom_textChanged(QString)\0"
    "on_lineEditParametresCPMedecin_returnPressed()\0"
    "on_lineEditParametreVilleMedecin_returnPressed()\0"
    "on_spinBoxParametreDureeDSI_editingFinished()\0"
    "on_pushButtonPrescriptionModifier_clicked()\0"
    "on_pushButtonPrescriptionAjouter_clicked()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButtonValeurParDefaut_clicked(); break;
        case 1: on_comboBoxPrescriptionPatient_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_comboBoxPatientMedecin_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: on_lineEditPatientNumSS_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: on_lineEditPatientNom_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: on_pushButtonPatientAjouter_clicked(); break;
        case 6: on_pushButtonPatientAbandonner_clicked(); break;
        case 7: on_pushButtonPatientModifier_clicked(); break;
        case 8: on_pushButtonPatientSupprimer_clicked(); break;
        case 9: on_listWidgetPatients_clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 10: on_pushButtonPrescriptionSupprimer_clicked(); break;
        case 11: on_listWidgetPrescriptions_clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 12: on_pushButtonMedecinAbandonner_clicked(); break;
        case 13: on_pushButtonMedecinModifier_clicked(); break;
        case 14: on_listWidgetMedecins_clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 15: on_pushButtonMedecinSupprimer_clicked(); break;
        case 16: on_pushButtonMedecinAjouter_clicked(); break;
        case 17: on_lineEditMedecinAdr2_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: on_lineEditMedecinAdr1_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: on_lineEditMedecinTel_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: on_lineEditMedecinVille_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: on_lineEditMedecinCP_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: on_lineEditMedecinNumSS_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: on_lineEditMedecinNom_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: on_lineEditParametresCPMedecin_returnPressed(); break;
        case 25: on_lineEditParametreVilleMedecin_returnPressed(); break;
        case 26: on_spinBoxParametreDureeDSI_editingFinished(); break;
        case 27: on_pushButtonPrescriptionModifier_clicked(); break;
        case 28: on_pushButtonPrescriptionAjouter_clicked(); break;
        default: ;
        }
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
