/*****************************************************************************
 * productsmodel.cpp
 *
 * Created: 22/04/2014 by vijay
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
 * D.Mohan Raj <mohanraj.hunk@live.com>
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#include "billform.h"
#include "ui_billform.h"

BillForm::BillForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillForm)
{
    ui->setupUi(this);

    formValidation = new FormValidation;
    billDataMapper = new QDataWidgetMapper;
    billDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    billItemDataMapper = new QDataWidgetMapper;
    billItemDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    productDataMapper = new QDataWidgetMapper;
    productDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    customerDataMapper = new QDataWidgetMapper;
    customerDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

//    validCodeFlag = validNameFlag = 0;

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->lineEditCustomerName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditCustomerName,SIGNAL(returnPressed()),this,SLOT(setSignalFromBillForm()));

    connect(ui->lineEditProductName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditProductName,SIGNAL(returnPressed()),this,SLOT(setSignalFromBillForm()));

    connect(ui->lineEditCustomerCode,SIGNAL(editingFinished()),this,SLOT(codeValid()));
    connect(ui->lineEditCustomerName,SIGNAL(editingFinished()),this,SLOT(nameValid()));
}

BillForm::~BillForm()
{
    delete ui;
}

void BillForm::save(){

}

void BillForm::setCodeFocus()
{
    ui->lineEditCustomerCode->setFocus();
    ui->lineEditCustomerCode->selectAll();
}

void BillForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",false);
        widget->setStyleSheet(styleSheet());
    }
    uninstallEventFilter();
    ui->pushButtonSave->setText("Save");
    ui->pushButtonDelete->setEnabled(false);
    //ui->pushButtonSave->setEnabled(false);
}

void BillForm::setModel(BillModel *model1, BillItemModel *model2 ,ProductsModel *model3, CustomersModel *model4)
{
    billModel = model1;
    billItemModel = model2;
    productsModel = model3;
    customersModel = model4;

    billDataMapper->setModel(billModel);
    billItemDataMapper->setModel(billItemModel);
    productDataMapper->setModel(productsModel);
    customerDataMapper->setModel(customersModel);

    billDataMapper->addMapping(ui->lineEditInvoiceDate,billModel->fieldIndex("date"));
    billDataMapper->addMapping(ui->lineEditInvoiceNo,billModel->fieldIndex("id"));
    billDataMapper->addMapping(ui->lineEditTotal,billModel->fieldIndex("actualAmount"));
    billDataMapper->addMapping(ui->lineEditDiscount,billModel->fieldIndex("discount"));
    billDataMapper->addMapping(ui->lineEditTooBePaid,billModel->fieldIndex("totalAmount"));

    billItemDataMapper->addMapping(ui->lineEditProductName, 2);
    billItemDataMapper->addMapping(ui->lineEditUnit,billItemModel->fieldIndex("unit_price"));
    billItemDataMapper->addMapping(ui->lineEditQty,billItemModel->fieldIndex("quantity"));
    billItemDataMapper->addMapping(ui->lineEditTotal,billItemModel->fieldIndex("total"));

    productDataMapper->addMapping(ui->lineEditProductCode,productsModel->fieldIndex("code"));
    productDataMapper->addMapping(ui->lineEditProductName,productsModel->fieldIndex("name"));
    productDataMapper->addMapping(ui->lineEditRate,productsModel->fieldIndex("sprice"));
    productDataMapper->addMapping(ui->lineEditUnit,productsModel->fieldIndex("unit"));

    customerDataMapper->addMapping(ui->lineEditCustomerCode,customersModel->fieldIndex("code"));
    customerDataMapper->addMapping(ui->lineEditCustomerName,customersModel->fieldIndex("name"));
    customerDataMapper->addMapping(ui->lineEditCustomerAddress,customersModel->fieldIndex("address1"));

    setCodeFocus();
}

//function to validate name field
bool BillForm::nameValid(){
    bool status = false;
//    QString flashMsg = "";
    ui->lineEditCustomerName->installEventFilter(this);
//    if(ui->lineEditName->text().length() > 0){
//        if(uniqueValid(ui->lineEditName->text(),"name")){
//            status = true;
//            ui->lineEditName->setProperty("validationError",false);
//            ui->lineEditName->setProperty("validationSuccess",true);
//            ui->lineEditName->setStyleSheet(styleSheet());
//            validNameFlag = 1;
//        }else{
//            status = false;
//            flashMsg = "This Name has been already taken. Please give some other name.";
//            ui->lineEditName->setProperty("validationError",true);
//            ui->lineEditName->setProperty("validationSuccess",false);
//            ui->lineEditName->setStyleSheet(styleSheet());
//            validNameFlag = 0;
//        }
//    }else{
//        status = false;
//        flashMsg = "Name field is empty. Please give some values.";
//        ui->lineEditName->setProperty("validationError",true);
//        ui->lineEditName->setProperty("validationSuccess",false);
//        ui->lineEditName->setStyleSheet(styleSheet());
//        validNameFlag = 0;
//    }
//    ui->flashMsgUp->setText(flashMsg);
    return status;
}

void BillForm::setMapperIndex(QModelIndex index)
{
    clear();
    billDataMapper->setCurrentIndex(index.row());
    this->ui->pushButtonSave->setText("Update");
    ui->pushButtonDelete->setEnabled(true);
//    validCodeFlag = validNameFlag = 1;
//    ui->pushButtonSave->setEnabled(false);
    setAllValidationSuccess();
}

void BillForm::search(QString value)
{
    QString searchValue = "code = ";
    searchValue.append(value);
    billModel->selectRow(1);
}

void BillForm::on_pushButtonClear_clicked()
{
    resetDataMapper();
    clear();
    setCodeFocus();
}

void BillForm::on_pushButtonDelete_clicked()
{
//    QSqlRecord record = categoriesModel->record(dataMapper->currentIndex());

//    QSqlQueryModel model;
//    QSqlQuery query;
//    query.prepare("Select * from products where category_id = :category_id");
//    query.bindValue(":category_id", record.value("id").toInt());
//    query.exec();
//    model.setQuery(query);

//    if(model.rowCount() == 0){
//        statusMsg = ui->lineEditName->text() + " deleted successfully";

//        QDateTime datetime = QDateTime::currentDateTime();

//        record.setValue("status", "D");
//        record.setValue("modifiedDate", datetime);
//        categoriesModel->setRecord(dataMapper->currentIndex(), record);
//        categoriesModel->submit();
//        categoriesModel->select();

//        on_pushButtonCancel_clicked();
//    }else{
//        QMessageBox msgBox;
//        msgBox.setText("Products found under this category. Cannot delete!!!");
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.setDefaultButton(QMessageBox::Ok);
//        msgBox.exec();
//    }
//    emit signalStatusBar(statusMsg);
}

QDateTime BillForm::modifiedDate() const
{
    return m_modifiedDate;
}

void BillForm::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate = modifiedDate;
}

void BillForm::onNameChanged(QString str)
{
    emit signalName(str);
}

void BillForm::setSignalFromBillForm()
{
    emit signalFromBillForm();
}

void BillForm::setFieldMaxLength()
{
//    ui->lineEditCode->setMaxLength(100);
//    ui->lineEditName->setMaxLength(200);
}

void BillForm::resetDataMapper()
{
    billDataMapper = new QDataWidgetMapper(this);
    billDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    setModel(billModel, billItemModel, productsModel, customersModel);
}

bool BillForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEditCustomerName){
        if(event->type() == QEvent::FocusIn){
            BillForm::nameValid();
            emit signalCustomerNameFocused();
        }
        return false;
    }
    return BillForm::eventFilter(obj, event);
}

void BillForm::uninstallEventFilter()
{
    ui->lineEditCustomerCode->removeEventFilter(this);
    ui->lineEditCustomerName->removeEventFilter(this);
    ui->flashMsgUp->clear();
}

void BillForm::setAllValidationSuccess()
{
//    validCodeFlag = 1;
//    validNameFlag = 1;
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",true);
        widget->setStyleSheet(styleSheet());
    }
}
