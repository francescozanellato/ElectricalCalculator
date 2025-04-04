/*
 * Author: Francesco Paolo Luca Zanellato
 * Copyright (C) 2015-2025 Francesco Paolo Luca Zanellato
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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
