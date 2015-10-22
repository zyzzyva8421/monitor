/****************************************************************************
** Meta object code from reading C++ file 'form_patient_drug_sum.h'
**
** Created: Mon Jun 8 17:02:27 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "form_patient_drug_sum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_patient_drug_sum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CFormPatientInfo2[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CFormPatientInfo2[] = {
    "CFormPatientInfo2\0"
};

void CFormPatientInfo2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CFormPatientInfo2::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CFormPatientInfo2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CFormPatientInfo2,
      qt_meta_data_CFormPatientInfo2, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CFormPatientInfo2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CFormPatientInfo2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CFormPatientInfo2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CFormPatientInfo2))
        return static_cast<void*>(const_cast< CFormPatientInfo2*>(this));
    if (!strcmp(_clname, "Ui_Form_pmng_drug_sum"))
        return static_cast< Ui_Form_pmng_drug_sum*>(const_cast< CFormPatientInfo2*>(this));
    return QWidget::qt_metacast(_clname);
}

int CFormPatientInfo2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
