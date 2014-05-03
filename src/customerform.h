/*****************************************************************************
 * customerform.h
 *
 * Created: 18/04/2014 by selvam
 *
 * Copyright 2014 ThamiZha!. All rights reserved.
 *
 * Visit www.thamizha.com for more information.
 *
 * This file is a part of ThamiZha Angadi application.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *
 * Authors :
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#ifndef CUSTOMERFORM_H
#define CUSTOMERFORM_H

#include "lssbar.h"
#include "models/customersmodel.h"
#include "models/formvalidation.h"

#include <QWidget>
#include <QDataWidgetMapper>
#include <QDateTime>
#include <QEvent>
#include <QKeyEvent>
#include <QSqlRecord>

namespace Ui {
class CustomerForm;
}

class CustomerForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)

public:
    explicit CustomerForm(QWidget *parent = 0);
    ~CustomerForm();
    FormValidation *formValidation;
    void setCodeFocus();
    void setModel(CustomersModel *model);
    void setMapperIndex(QModelIndex index);
    void search(QString value);
    QDateTime modifiedDate();
    void setModifiedDate(QDateTime modifiedDate);
    void clear();
    int validCodeFlag, validNameFlag, validEmailFlag;

signals:
    void signalName(QString str);
    void signalFromCustomerForm();

private:
    Ui::CustomerForm *ui;
    CustomersModel *customersModel;
    QDataWidgetMapper *dataMapper;
    Lssbar *lssbar;
    QDateTime m_modifiedDate;

private slots:
    void save();
    void enableSave();
    void on_pushButtonCancel_clicked();
    void onNameChanged(QString str);
    void hideValidationErrors();
    void setSignalFromCustomerForm();
    bool uniqueValid(QString text, QString field);
    bool eventFilter(QObject *obj, QEvent *event);
    bool on_lineEditCode_editingFinished();
    bool on_lineEditName_editingFinished();
    bool on_lineEditEmail_editingFinished();
    void uninstallEventFilter();
    void setAllValidationSuccess();
    void setFieldMaxLength();
};

#endif // CUSTOMERFORM_H
