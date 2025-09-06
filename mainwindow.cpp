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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QClipboard>
#define LICENSE "ElectricalCalculator version 1.0.2\n\n© Francesco Zanellato 2015-2025\n\nThis program is freeware;\nit is provided \"AS IT IS\", without any warranty."

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/"+APP_NAME+".txt",QSettings::IniFormat,this);
    ui->setupUi(this);
    this->setWindowTitle(qApp->applicationName()+" "+QString(APP_VERSION));
    ui->ViewportScale->setCompleter(nullptr);

    ui->PlotScale_measure->setCompleter(nullptr);
    ui->PlotScale_units->setCompleter(nullptr);

    ui->CBSpareMargin->setCompleter(nullptr);
    ui->ratedVoltage->setCompleter(nullptr);
    ui->ratedPower->setCompleter(nullptr);
    ui->fullLoadEfficiency->setCompleter(nullptr);
    ui->powerFactor->setCompleter(nullptr);
    ui->shortCircuitImpedance->setCompleter(nullptr);
    thirdPartyLicense = new License(this);
    //CONNECT INTERFAC ACTIONS
    connect(ui->actionGo_To_ViewPortScale, SIGNAL(triggered()), this, SLOT(goToViewPortTab()));
    connect(ui->actionGo_to_kVA_Calculation, SIGNAL(triggered()), this, SLOT(goTokVACalculationTab()));
    connect(ui->actionGo_to_kVA_Example, SIGNAL(triggered()), this, SLOT(goTokVAExample()));
    //CONNECT ACTIONS
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(myQuit()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(myQuit()));
    connect(ui->Calculate, SIGNAL(clicked()), this, SLOT(calculateActualScale()));
    connect(ui->actionQT_Information, SIGNAL(triggered()), this, SLOT(aboutQT()));
    connect(ui->actionLicenseAndCredits, SIGNAL(triggered()), this, SLOT(showLicenseAndCredits()));
    connect(ui->ViewportScale->lineEdit(), SIGNAL(returnPressed()), this, SLOT(calculateActualScale()));
    connect(ui->ViewportScale, SIGNAL(editTextChanged(QString)), this, SLOT(calculateActualScale()));
    connect(ui->LayoutUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculateActualScale()));
    connect(ui->ModelUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculateActualScale()));
    connect(ui->ActualScale, SIGNAL(returnPressed()), this, SLOT(calculateActualScale()));

    connect(ui->PlotScale_measure->lineEdit(), SIGNAL(returnPressed()), this, SLOT(calculateActualScale()));
    connect(ui->PlotScale_measure, SIGNAL(editTextChanged(QString)), this, SLOT(calculateActualScale()));
    connect(ui->PlotScale_units->lineEdit(), SIGNAL(returnPressed()), this, SLOT(calculateActualScale()));
    connect(ui->PlotScale_units, SIGNAL(editTextChanged(QString)), this, SLOT(calculateActualScale()));
    connect(ui->PlotScale_mm_or_inches, SIGNAL(currentIndexChanged(int)), this, SLOT(calculateActualScale()));

    //CONNECT kVA ACTIONS
    connect(ui->numberOfPhases, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->ratedVoltage, SIGNAL(editTextChanged(QString)), this, SLOT(calculatekVA()));
    connect(ui->ratedVoltageUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->ratedPower, SIGNAL(editTextChanged(QString)), this, SLOT(calculatekVA()));
    connect(ui->ratedPowerUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->fullLoadEfficiency, SIGNAL(editTextChanged(QString)), this, SLOT(calculatekVA()));
    connect(ui->efficiencyUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->powerFactor, SIGNAL(editTextChanged(QString)), this, SLOT(calculatekVA()));
    connect(ui->powerFactorUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->shortCircuitImpedance, SIGNAL(editTextChanged(QString)), this, SLOT(calculatekVA()));
    connect(ui->shortCircuitImpedanceUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->CBSpareMargin, SIGNAL(editTextChanged(QString)), this, SLOT(calculatekVA()));
    connect(ui->CBSpareMarginUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->ratedApparentPowerUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->ratedActivePowerUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->ratedReactivePowerUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(calculatekVA()));
    connect(ui->Calculation_kVA, SIGNAL(clicked()), this, SLOT(calculatekVA()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setTabAndDefaultFocus(int)));
    //CONNECT kVA EARTHING SIZING ACTIONS
    connect(ui->CopyDown, SIGNAL(clicked()), this, SLOT(copyDown()));
    connect(ui->copySizingFormula, SIGNAL(clicked()), this, SLOT(copySizingFormula()));
    connect(ui->Earthing_Calculation, SIGNAL(clicked()), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->earthFaultCurrent_kA, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->splitFactor, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->faultClearingTime_s, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->Qf, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->Qi, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->_k, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->beta, SIGNAL(textChanged(QString)), this, SLOT(calculateEarthingConductorSizing()));
    connect(ui->actionLoadDefaultSettings, SIGNAL(triggered()), this, SLOT(loadDefaultSettings()));
    connect(ui->actionSaveDefaultSettings, SIGNAL(triggered()), this, SLOT(saveDefaultSettings()));
    connect(ui->actionEditDefaultSettings, SIGNAL(triggered()), this, SLOT(editDefaultSettings()));
    connect(ui->CBRating, SIGNAL(currentTextChanged(QString)), this, SLOT(updateCBRatingColour()));
    //FILL UI
    textEditViewportExplanation = "Viewport Custom Scale is %VP_SCALE%.\n"
                                  "Viewport Custom Scale * plot scaling factor is %VP_WITH_SCALING%.\n"
                                  "%VP_WITH_SCALING% %LAYOUT_UNIT% (in layout units) : 1 %MODEL_UNIT% (in model units).\n"
                                  "Therefore:\n"
                                  "%VP_WITH_SCALING% %LAYOUT_UNIT% : %SECOND_NUMBER% %LAYOUT_UNIT%\n"
                                  "Dividing both numbers by the lowest (%LOWEST_NUMBER%):\n"
                                  "%VP_WITH_SCALING%/%LOWEST_NUMBER% %LAYOUT_UNIT% : %SECOND_NUMBER%/%LOWEST_NUMBER% %MODEL_UNIT%\n"
                                  "The resulting scale is %ACTUAL_SCALE%";
    //STARTUP
    ui->CBRating->addItems(CBRatingList);
    ui->CBRating->setCurrentIndex(CBRatingList.count()-1);
    setTabAndDefaultFocus(1);

    //qDebug(myCompress("ciao. 123. Io mi chiamo ioo1234567890%$£!\\ooooooooooooooooooooooooooooooooo").toUtf8());
    //qDebug(myCompress(LICENSE).toUtf8());
    //qDebug(myUncompress("AAAAPHicS85MzNdTMDQy1lPwzFfIzVRIzshMzM1XyMwnDAB5WRbE").toUtf8());
    //(myUncompress("AAAATHicS85MzNdTMDQy1lPwzFfIzVRIzshMzM1XyMzPBwqamJqZW1gaqKocWqwYk08IAACqgRr8").toUtf8());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myQuit()
{
    //qApp->exit();
    QCoreApplication::exit(0);
}

QString MainWindow::myCompress(QString uncompressedString)
{
    //usage: qDebug(myCompress("ciao. 123. Io mi chiamo ioo1234567890%$£!\\ooooooooooooooooooooooooooooooooo").toUtf8());
    return QVariant(qCompress(uncompressedString.toUtf8()).toBase64()).toString();
}

QString MainWindow::myUncompress(QString compressedHexString)
{
    //usage: qDebug(myUncompress("AAAAPHicS85MzNdTMDQy1lPwzFfIzVRIzshMzM1XyMwnDAB5WRbE").toUtf8());

    //QByteArray myByteArray = QByteArray::fromHex(compressedHexString.toUtf8());
    //QByteArray myByteArray = QByteArray::fromBase64(compressedHexString.toUtf8()); //Uncompression OK
    //qDebug() << "compressed: " << myByteArray.toHex();
    //qDebug() << "compressed: " << myByteArray.toBase64();
    //qDebug() << "uncompressed: " << qUncompress(myByteArray);
    return QVariant(qUncompress(QByteArray::fromBase64(compressedHexString.toUtf8()))).toString();
}

void MainWindow::aboutQT()
{
    QMessageBox::aboutQt(this, "About QT");
}

void MainWindow::showLicenseAndCredits()
{
    //QMessageBox::information(this,"License", LICENSE);
    //thirdPartyLicense->setApplicationLicenseText(LICENSE);
    //thirdPartyLicense->setApplicationLicenseText(qUncompress(LICENSE));
    //thirdPartyLicense->setApplicationLicenseText(myUncompress(LICENSE));
    thirdPartyLicense->setApplicationLicenseText(LICENSE);
    thirdPartyLicense->show();
}

void MainWindow::loadDefaultSettings()
{
    //if (settings == nullptr) settings = new QSettings(QCoreApplication::applicationDirPath()+"/ElectricalCalculator.txt",QSettings::IniFormat,this);
    if (!settings) return;
    calculationIsActive = false;

    ui->numberOfPhases->setCurrentText(settings->value("numberOfPhases","three-phase").toString());
    ui->ratedVoltage->setCurrentText(settings->value("ratedVoltage",0.4).toString());
    ui->ratedVoltageUnit->setCurrentText(settings->value("ratedVoltageUnit","kV").toString());
    ui->ratedPower->setCurrentText(settings->value("ratedPower",10).toString());
    ui->ratedPowerUnit->setCurrentText(settings->value("ratedPowerUnit","kW").toString());
    ui->fullLoadEfficiency->setCurrentText(settings->value("fullLoadEfficiency",100).toString());
    ui->efficiencyUnit->setCurrentText(settings->value("efficiencyUnit","%").toString());
    ui->powerFactor->setCurrentText(settings->value("powerFactor",80).toString());
    ui->powerFactorUnit->setCurrentText(settings->value("powerFactorUnit","%").toString());
    ui->shortCircuitImpedance->setCurrentText(settings->value("shortCircuitImpedance",16).toString());
    ui->shortCircuitImpedanceUnit->setCurrentText(settings->value("shortCircuitImpedanceUnit","%").toString());
    ui->earthFaultCurrent_kA->setText(settings->value("earthFaultCurrent_kA",25).toString());
    ui->CBSpareMargin->setCurrentText(settings->value("CBSpareMargin_A",20).toString());
    ui->CBSpareMarginUnit->setCurrentText(settings->value("CBSpareMarginUnit","%").toString());
    settings->setValue("CBSpareMarginUnit",ui->CBSpareMarginUnit->currentText());
    calculationIsActive = true;
    //ui->tabWidget->setCurrentIndex(1);
    setTabAndDefaultFocus(1);
    //calculationIsActive = true;
    //calculatekVA();
    //calculateEarthingConductorSizing();

}

void MainWindow::saveDefaultSettings()
{
    //if (settings == nullptr) settings = new QSettings(QCoreApplication::applicationDirPath()+"/ElectricalCalculator.txt",QSettings::IniFormat,this);
    if (!settings) return;
    settings->setValue("numberOfPhases",ui->numberOfPhases->currentText());
    settings->setValue("ratedVoltage",ui->ratedVoltage->currentText());
    settings->setValue("ratedVoltageUnit",ui->ratedVoltageUnit->currentText());
    settings->setValue("ratedPower",ui->ratedPower->currentText());
    settings->setValue("ratedPowerUnit",ui->ratedPowerUnit->currentText());
    settings->setValue("fullLoadEfficiency",ui->fullLoadEfficiency->currentText());
    settings->setValue("efficiencyUnit",ui->efficiencyUnit->currentText());
    settings->setValue("powerFactor",ui->powerFactor->currentText());
    settings->setValue("powerFactorUnit",ui->powerFactorUnit->currentText());
    settings->setValue("shortCircuitImpedance",ui->shortCircuitImpedance->currentText());
    settings->setValue("shortCircuitImpedanceUnit",ui->shortCircuitImpedanceUnit->currentText());
    settings->setValue("CBSpareMargin_A",ui->CBSpareMargin->currentText());
    settings->setValue("CBSpareMarginUnit",ui->CBSpareMarginUnit->currentText());
    settings->setValue("earthFaultCurrent_kA",ui->earthFaultCurrent_kA->text());

    settings->setValue("Calculation/ratedApparentPower",ui->ratedApparentPower->text());
    settings->setValue("Calculation/ratedApparentPowerUnit",ui->ratedApparentPowerUnit->currentText());
    settings->setValue("Calculation/ratedActivePower",ui->ratedActivePower->text());
    settings->setValue("Calculation/ratedActivePowerUnit",ui->ratedActivePowerUnit->currentText());
    settings->setValue("Calculation/ratedReactivePower",ui->ratedReactivePower->text());
    settings->setValue("Calculation/ratedReactivePowerUnit",ui->ratedReactivePowerUnit->currentText());
    settings->setValue("Calculation/ratedCurrent_A",ui->ratedCurrent_A->text());
    settings->setValue("Calculation/CBRating_A",ui->CBRating->currentText());
    settings->setValue("Calculation/shortCircuitContribution",ui->shortCircuitContribution->text());
    settings->setValue("Calculation/shortCircuitContributionUnit",ui->shortCircuitContributionUnit->text());

    settings->setValue("Earthing_Conductor_Sizing/splitFactor",ui->splitFactor->text());
    settings->setValue("Earthing_Conductor_Sizing/faultClearingTime_s",ui->faultClearingTime_s->text());
    settings->setValue("Earthing_Conductor_Sizing/_k",ui->_k->text());
    settings->setValue("Earthing_Conductor_Sizing/beta",ui->beta->text());
    settings->setValue("Earthing_Conductor_Sizing/Qi",ui->Qi->text());
    settings->setValue("Earthing_Conductor_Sizing/Qf",ui->Qf->text());
    settings->setValue("Earthing_Conductor_Sizing/earthingConductorSize_mm2",ui->earthingConductorSize_mm2->text());
}

void MainWindow::editDefaultSettings()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/"+APP_NAME+".txt"));
}

void MainWindow::setTabAndDefaultFocus(int tabIndex)
{
    if (tabIndex == 0) {
        //ui->tabWidget->setCurrentIndex(0);
        ui->ViewportScale->setFocus();
        ui->ViewportScale->lineEdit()->selectAll();
        ui->Calculate->setDefault(true);
        calculateActualScale();
    }
    else if (tabIndex == 1) {
        //ui->tabWidget->setCurrentIndex(1);
        ui->ratedPower->setFocus();
        ui->ratedPower->lineEdit()->selectAll();
        ui->Calculation_kVA ->setDefault(true);
        calculationIsActive = true;
        calculatekVA();
        calculateEarthingConductorSizing();
    }
}
void MainWindow::goToViewPortTab()
{
    //setTabAndDefaultFocus(0);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::goTokVACalculationTab()
{
    //setTabAndDefaultFocus(2);
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::goTokVAExample()
{
    //setTabAndDefaultFocus(1);
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::calculateActualScale()
{



    QString myLayoutUnit = ui->LayoutUnit->currentText();
    double myLayoutUnitNumber;
    if (myLayoutUnit == "mm") myLayoutUnitNumber = 0.001;
    else if (myLayoutUnit == "cm") myLayoutUnitNumber = 0.01;
    else if (myLayoutUnit == "dm") myLayoutUnitNumber = 0.1;
    else if (myLayoutUnit == "m") myLayoutUnitNumber = 1.0;
    else if (myLayoutUnit == "dam") myLayoutUnitNumber = 10.0;
    else if (myLayoutUnit == "hm") myLayoutUnitNumber = 100.0;
    else if (myLayoutUnit == "km") myLayoutUnitNumber = 1000.0000;
    else myLayoutUnitNumber = 1;
    QString myModelUnit = ui->ModelUnit->currentText();
    double myModelUnitNumber;
    if (myModelUnit == "mm") myModelUnitNumber = 0.001;
    else if (myModelUnit == "cm") myModelUnitNumber = 0.01;
    else if (myModelUnit == "dm") myModelUnitNumber = 0.1;
    else if (myModelUnit == "m") myModelUnitNumber = 1.0;
    else if (myModelUnit == "dam") myModelUnitNumber = 10.0;
    else if (myModelUnit == "hm") myModelUnitNumber = 100.0;
    else if (myModelUnit == "km") myModelUnitNumber = 1000.0000;
    else myModelUnitNumber = 1;

    double mm_or_inch_conversion = (ui->PlotScale_mm_or_inches->currentText()=="mm"? 1 : 0.0254/myLayoutUnitNumber);
    double myPlotScalingFactor = QVariant(ui->PlotScale_measure->currentText()).toDouble() / QVariant(ui->PlotScale_units->currentText()).toDouble() * mm_or_inch_conversion;
    //double myLayoutScalingFactor = myViewportScale*myPlotScalingFactor;

    ui->label_PlotScale_units->setText("units ("+ui->LayoutUnit->currentText() + ")");

    double myViewportScale = QVariant(ui->ViewportScale->currentText()).toDouble()*myPlotScalingFactor;
    ui->PlotScalingFactor->setText(ui->PlotScale_measure->currentText() + (ui->PlotScale_mm_or_inches->currentText()=="mm"? "/" : "*0.0254m/") +
                                   ui->PlotScale_units->currentText() + ui->LayoutUnit->currentText() + "=" + QString::number(myPlotScalingFactor) +
                                   "; so, the actual Viewport Custom Scale is: " + (QString::number(myViewportScale) + " in the layout"));

    //CALCULATION:
    //double ratioNumber = myViewportScale * myLayoutUnitNumber / myModelUnitNumber;
    double scaleFactor = myModelUnitNumber/myLayoutUnitNumber;
    double lowest_number = qMin(myViewportScale,scaleFactor);
    double numerator = myViewportScale / lowest_number;
    double denominator = scaleFactor / lowest_number;
    //if (ratioNumber > 1) {numerator = ratioNumber; denominator = 1.0;}
    //else if (ratioNumber < 1) {numerator = 1.0; denominator = 1.0 / ratioNumber;}
    //else {numerator = 0.0; denominator = 0.0;}
    // ui->ScaleText->setText(ui->ViewportScale->currentText()+" "+myLayoutUnit+" (in the layout) : 1 " + myModelUnit + " (in the model)");
    ui->ScaleText->setText(QString::number(myViewportScale)+" "+myLayoutUnit+" (in the layout) : 1 " + myModelUnit + " (in the model)");
    //double isNumeratorInteger = QString::number(numerator).toDouble()-QString::number(numerator,'F',0).toDouble();
    bool isNumeratorInteger = std::abs(numerator - std::round(numerator)) < 1e-10;
    // double isNumeratorInteger = QVariant(numerator).toInt()-numerator;
    // double isDenominatorInteger = QString::number(denominator).toDouble()-QString::number(denominator,'F',0).toDouble();
    //bool isDenominatorInteger = denominator-floor(denominator);
    bool isDenominatorInteger = std::abs(denominator - std::round(denominator)) < 1e-10;
    //double isDenominatorInteger = QVariant(denominator).toInt()-numerator;
    // if (isNumeratorInteger!=0 || isDenominatorInteger!=0)
    if (!isNumeratorInteger || !isDenominatorInteger)
    { ui->ActualScale->setStyleSheet("color: red;");
        ui->ActualScale->setText(QString::number(numerator,'F',0) + ":" + QString::number(denominator,'F',0) + " (Approximate scale)");
    }
    else
    { ui->ActualScale->setStyleSheet("color: green;");
        ui->ActualScale->setText(QString::number(numerator,'F',0) + ":" + QString::number(denominator,'F',0) + " (Exact scale)");
    }
    QString statusText = QString::number(numerator,'F',0)+" "+myLayoutUnit+" (in the layout) : " +
                         QString::number(denominator,'F',0)+ " " + myLayoutUnit + " (in the model)";
    ui->Explanation->setText(statusText);
    ui->Explanation->setToolTip(statusText);
    QString CompleteExplanation = textEditViewportExplanation;
    ui->plainTextEdit->setPlainText(CompleteExplanation.replace("%VP_SCALE%",ui->ViewportScale->currentText()).replace("%LAYOUT_UNIT%",myLayoutUnit)
                                        .replace("%MODEL_UNIT%",myModelUnit).replace("%SECOND_NUMBER%",QString::number(scaleFactor))
                                        .replace("%LOWEST_NUMBER%",QString::number(lowest_number)).replace("%ACTUAL_SCALE%",ui->ActualScale->text())
                                        .replace("%VP_WITH_SCALING%",QString::number(myViewportScale)));
}
void MainWindow::calculateEarthingConductorSizing()
{
    if (!calculationIsActive) return;
    /*ui->earthingConductorSize_mm2->setText(QVariant(
                                               ((ui->earthFaultCurrent_kA->text().toDouble()/ui->_k->text().toDouble())*
                                                sqrt(ui->faultClearingTime_s->text().toDouble()/
                                                log((ui->Qf->text().toDouble()+ui->beta->text().toDouble())/(ui->Qi->text().toDouble()+ui->beta->text().toDouble()))))
                                               ).toString());*/
    ui->earthingConductorSize_mm2->setText(QVariant(QString::number(
                                                        ((ui->earthFaultCurrent_kA->text().toDouble()*ui->splitFactor->text().toDouble()*1000/ui->_k->text().toDouble())*
                                                         sqrt(ui->faultClearingTime_s->text().toDouble()/
                                                              log((ui->Qf->text().toDouble()+ui->beta->text().toDouble())/
                                                                  (ui->Qi->text().toDouble()+ui->beta->text().toDouble())))), 'f', 3)
                                                    ).toString());
}
void MainWindow::copyDown()
{
    ui->earthFaultCurrent_kA->setText(ui->shortCircuitContribution->text());
}

void MainWindow::copySizingFormula()
{
    qApp->clipboard();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(
        "(" + ui->earthFaultCurrent_kA->text()  + "*1000*" + ui->splitFactor->text() + "/" + ui->_k->text() + ")*(sqrt(" + ui->faultClearingTime_s->text() + "/(ln((" + ui->Qf->text() + "+" + ui->beta->text() +  ")/(" + ui->Qi->text() +  "+" + ui->beta->text() + ")))))"
        );
    //ui->earthFaultCurrent_kA->setText(ui->shortCircuitContribution->text());
}

void MainWindow::calculatekVA()
{
    if (!calculationIsActive) return;
    //INPUT
    QString _numberOfPhases = ui->numberOfPhases->currentText();
    double _powerFactor = ui->powerFactor->currentText().toDouble();
    double _fullLoadEfficiency = ui->fullLoadEfficiency->currentText().toDouble();
    double _ratedApparentPower, _ratedActivePower, _ratedReactivePower, _voltagePhaseFactor;
    QString _powerFactorUnit = ui->powerFactorUnit->currentText();
    QString _efficiencyUnit = ui->efficiencyUnit->currentText();
    QString _ratedPowerUnit = ui->ratedPowerUnit->currentText();
    double _ratedPower = ui->ratedPower->currentText().toDouble();
    double _ratedVoltage = ui->ratedVoltage->currentText().toDouble();
    QString _ratedVoltageUnit = ui->ratedVoltageUnit->currentText();
    double _shortCircuitImpedance = ui->shortCircuitImpedance->currentText().toDouble();
    QString _shortCircuitImpedanceUnit = ui->shortCircuitImpedanceUnit->currentText();
    double _ratedCurrent;
    double _shortCircuitCurrentContribution;

    //CALCULATION
    if (_ratedPowerUnit == "MW" || _ratedPowerUnit == "MVA" || _ratedPowerUnit == "Mvar") _ratedPower = _ratedPower * 1000.0;
    if (_ratedVoltageUnit == "V") _ratedVoltage = _ratedVoltage/1000.0;
    if (_powerFactorUnit == "%") _powerFactor = _powerFactor/100.0;
    if (_efficiencyUnit == "%") _fullLoadEfficiency = _fullLoadEfficiency/100.0;
    if (_powerFactor ==0) {
        _ratedApparentPower = _ratedPower/_fullLoadEfficiency;
        _ratedActivePower = 0.0;
        _ratedReactivePower = _ratedApparentPower;
    }
    else {
        if (_ratedPowerUnit == "kVA" || _ratedPowerUnit == "MVA")
            _ratedApparentPower = _ratedPower/_fullLoadEfficiency;
        else if (_ratedPowerUnit == "kW" || _ratedPowerUnit == "MW")
            _ratedApparentPower = _ratedPower/_powerFactor/_fullLoadEfficiency;
        else if (_ratedPowerUnit == "kvar" || _ratedPowerUnit == "Mvar") _ratedApparentPower = _ratedPower/_fullLoadEfficiency/_powerFactor/tan(acos(_powerFactor));
        else _ratedApparentPower = 0.0;
        _ratedActivePower = _ratedApparentPower * _powerFactor;
        _ratedReactivePower = sqrt(pow(_ratedApparentPower,2) - pow(_ratedActivePower,2));
    }

    if (_numberOfPhases == "three-phase") _voltagePhaseFactor = sqrt(3); else _voltagePhaseFactor = 1.0;
    _ratedCurrent = _ratedApparentPower/_ratedVoltage/_voltagePhaseFactor;
    if (_shortCircuitImpedanceUnit == "%") _shortCircuitImpedance = _shortCircuitImpedance / 100.0;
    _shortCircuitCurrentContribution = _ratedCurrent / _shortCircuitImpedance / 1000.0;

    //UPDATE WINDOW FORM
    if (((_ratedPowerUnit == "kvar" || _ratedPowerUnit == "Mvar") && _powerFactor == 1.0) ||
        ((_ratedPowerUnit == "kW" || _ratedPowerUnit == "MW") && _powerFactor == 0.0)) {
        ui->ratedPowerUnit->setStyleSheet("color: red;");
        ui->powerFactor->setStyleSheet("color: red;");
        ui->ratedApparentPower->setText("-");
        ui->ratedActivePower->setText("-");
        ui->ratedReactivePower->setText("-");
        ui->ratedCurrent_A->setText("-");
        ui->shortCircuitContribution->setText("-");
        return;
    }
    else {
        ui->ratedPowerUnit->setStyleSheet("color: green;");
        ui->powerFactor->setStyleSheet("color: green;");
    }
    if (_powerFactor > 1.0 || _powerFactor < 0.0 || qIsInf(_powerFactor) || qIsNaN(_powerFactor)) ui->powerFactor->setStyleSheet("color: red;");
    QString _ratedApparentPowerUnit = ui->ratedApparentPowerUnit->currentText();
    if (_ratedApparentPowerUnit == "MVA")
        ui->ratedApparentPower->setText(QString::number(_ratedApparentPower/1000.0, 'G', 9));
    else ui->ratedApparentPower->setText(QString::number(_ratedApparentPower, 'G', 9));
    QString _ratedActivePowerUnit = ui->ratedActivePowerUnit->currentText();
    if (_ratedActivePowerUnit == "MW")
        ui->ratedActivePower->setText(QString::number(_ratedActivePower/1000.0, 'G', 9));
    else ui->ratedActivePower->setText(QString::number(_ratedActivePower, 'G', 9));
    QString _ratedReactivePowerUnit = ui->ratedReactivePowerUnit->currentText();
    if (_ratedReactivePowerUnit == "Mvar")
        ui->ratedReactivePower->setText(QString::number(_ratedReactivePower/1000.0, 'G', 9));
    else ui->ratedReactivePower->setText(QString::number(_ratedReactivePower, 'G', 9));
    ui->ratedCurrent_A->setText(QString::number(_ratedCurrent, 'G', 6));
    //ui->shortCircuitContribution->setText(QString::number(_shortCircuitCurrentContribution, 'G', 7));
    ui->shortCircuitContribution->setText(QString::number(_shortCircuitCurrentContribution, 'f', 4));
    if (_fullLoadEfficiency > 1.0 || _fullLoadEfficiency <= 0.0 || qIsInf(_fullLoadEfficiency) || qIsNaN(_fullLoadEfficiency)) ui->fullLoadEfficiency->setStyleSheet("color: red;");
    else ui->fullLoadEfficiency->setStyleSheet("color: green;");
    if (_ratedActivePower > 1.0E10 || _ratedActivePower < 0.0 || qIsInf(_ratedActivePower) || qIsNaN(_ratedActivePower)) ui->ratedActivePower->setStyleSheet("color: red;");
    else ui->ratedActivePower->setStyleSheet("color: green;");
    if (_ratedApparentPower > 1.0E10 || _ratedApparentPower < 0.0 || qIsInf(_ratedApparentPower) || qIsNaN(_ratedApparentPower)) ui->ratedApparentPower->setStyleSheet("color: red;");
    else ui->ratedApparentPower->setStyleSheet("color: green;");
    if (_ratedReactivePower > 1.0E10 || _ratedReactivePower < 0.0 || qIsInf(_ratedReactivePower) || qIsNaN(_ratedReactivePower)) ui->ratedReactivePower->setStyleSheet("color: red;");
    else ui->ratedReactivePower->setStyleSheet("color: green;");
    if (_ratedCurrent > 1.0E6 || _ratedCurrent < 0.0 || qIsInf(_ratedCurrent) || qIsNaN(_ratedCurrent)) ui->ratedCurrent_A->setStyleSheet("color: red;");
    else ui->ratedCurrent_A->setStyleSheet("color: green;");
    if (_ratedVoltage > 1.0E6 || _ratedVoltage <= 0.0 || qIsInf(_ratedVoltage) || qIsNaN(_ratedVoltage)) ui->ratedVoltage->setStyleSheet("color: red;");
    else ui->ratedVoltage->setStyleSheet("color: green;");
    if (_ratedPower > 1.0E6 || _ratedPower <= 0.0 || qIsInf(_ratedPower) || qIsNaN(_ratedPower)) ui->ratedPower->setStyleSheet("color: red;");
    else ui->ratedPower->setStyleSheet("color: green;");
    if (_shortCircuitCurrentContribution > 1.0E6 || _shortCircuitCurrentContribution <= 0.0 || qIsInf(_shortCircuitCurrentContribution) || qIsNaN(_shortCircuitCurrentContribution))
    { ui->shortCircuitImpedance->setStyleSheet("color: red;");
        ui->shortCircuitContribution->setStyleSheet("color: red;");}
    else { ui->shortCircuitImpedance->setStyleSheet("color: green;");
        ui->shortCircuitContribution->setStyleSheet("color: green;");}

    if (ui->CBSpareMargin->currentText().toDouble()<0.0 || (ui->CBSpareMarginUnit->currentText()=="p.u." && ui->CBSpareMargin->currentText().toDouble()>0.5))
        ui->CBSpareMargin->setStyleSheet("color: red;");
    else ui->CBSpareMargin->setStyleSheet("color: green;");

    selectCB();
}

void MainWindow::selectCB()
{
    if (!calculationIsActive) return;
    //ui->CBRating->setStyleSheet("color: ;");
    ui->CBRating->setCurrentIndex(CBRatingList.count()-1);
    double inputCurrent = ui->ratedCurrent_A->text().toDouble();
    double cbSpareMargin = ui->CBSpareMargin->currentText().toDouble();
    if (ui->CBSpareMarginUnit->currentText()=="%") cbSpareMargin = 1.0+cbSpareMargin/100.0;
    else cbSpareMargin = 1.0+cbSpareMargin;
    for (int i = 0; i < CBRatingList.count(); i++) {
        if (QVariant(CBRatingList.at(i)).toDouble() >= inputCurrent*cbSpareMargin) {
            ui->CBRating->setCurrentIndex(i);
            //if (ui->CBRating->currentText().toDouble()>3150) ui->CBRating->setStyleSheet("color: red;");
            break;
        }
    }
}

void MainWindow::updateCBRatingColour()
{
    if (ui->CBRating->currentText().toDouble()>3150) ui->CBRating->setStyleSheet("color: red;");
    else ui->CBRating->setStyleSheet("color: ;");
}



