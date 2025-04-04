#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QSettings>
#include "license.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    License* thirdPartyLicense;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString myUncompress(QString);
    QString myCompress(QString);
    QSettings *settings;

public slots:
    void myQuit();
    void aboutQT();
    void calculateActualScale();
    void setTabAndDefaultFocus(int tabIndex);
    void calculatekVA();
    void calculateEarthingConductorSizing();
    void selectCB();
    void updateCBRatingColour();
    void copyDown();
    void copySizingFormula();
    void goToViewPortTab();
    void goTokVACalculationTab();
    void goTokVAExample();
    void showLicenseAndCredits();
    void loadDefaultSettings();
    void saveDefaultSettings();
    void editDefaultSettings();

private:
    Ui::MainWindow *ui;
    bool calculationIsActive = true;
    QString textEditViewportExplanation;
    QStringList CBRatingList = {"1","1.25","1.6","2","2.5","3.2","4","5","6.3","8","10","12.5","16","20","25","32","40","50","63","80","100","125",
                                "160","200","250","320","400","500","630","800","1000","1250","1600","2000","2500","3150", "4000","N/A"};
};
#endif // MAINWINDOW_H
