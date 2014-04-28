#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>

#include "lssbar.h"
#include "categoryform.h"
#include "productform.h"
#include "customerform.h"
#include "models/categoriesmodel.h"
#include "models/productsmodel.h"
#include "models/customersmodel.h"
#include <QSortFilterProxyModel>

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT
    QString currentTab;

public:
    explicit AngadiMainWindow(QWidget *parent = 0);
    ~AngadiMainWindow();

public slots:

signals:
    void exit();

private:
    bool tabLoadedStatus(QString tabName);
    Ui::AngadiMainWindow *ui;
    CategoryForm *categoryForm;
    ProductForm *productForm;
    CustomerForm *customerForm;

    CategoriesModel *categoriesModel;
    ProductsModel *productsModel;
    CustomersModel *customersModel;

    QSortFilterProxyModel *categoriesProxyModel;
    QSortFilterProxyModel *productsProxyModel;
    QSortFilterProxyModel *customersProxyModel;

    void openCustomerTab();
    void openProductTab();
    void openCategoryTab();

    void onCustomerTabClosed();
    void onProductTabClosed();
    void onCategoryTabClosed();

    void setupConnections();
    void setupModels();

    void showRightDock(bool);
    Lssbar *lssbar;

private slots:    
    void exitApp();
    void openTab();
    void onCloseTab(int);
    void onTabChanged(int);
    void doubleClicked(QModelIndex index);
    void search(QString value);
    void moveUpDown(int indexOffset);
};

#endif // ANGADIMAINWINDOW_H
