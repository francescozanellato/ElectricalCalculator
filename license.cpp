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

#include "license.h"
#include "ui_license.h"
#include <QDesktopServices>
#include <QMessageBox>

License::License(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::License)
{
    ui->setupUi(this);
    ViewAllLicensesButton = ui->buttonBox->addButton("View All Licenses", QDialogButtonBox::AcceptRole);
    ViewAllSourcesButton = ui->buttonBox->addButton("View All Sources", QDialogButtonBox::AcceptRole);
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(viewAllLicensesOrSourcesFolder(QAbstractButton *)));
}

License::~License()
{
    delete ui;
}

void License::setApplicationLicenseText(QString licenseText)
{
    ui->ApplicationLicense->setPlainText(licenseText);
    ui->buttonBox->setFocus();

    //The following string is obtained from the THIRD-PARTY_LICENSES.html" file included in the distribution of this program, using the following code:
    //qDebug(QVariant(qCompress(ui->LicenseText->toHtml().toUtf8()).toBase64()).toString().toUtf8());
    QString myHTML = "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";
    ui->LicenseText->setHtml(QVariant(qUncompress(QByteArray::fromBase64(myHTML.toUtf8()))).toString());
}

void License::viewAllLicensesOrSourcesFolder(QAbstractButton *clickedButton)
{
    if ((QPushButton*) clickedButton == ViewAllLicensesButton) {
        if (!QDesktopServices::openUrl(QUrl(QCoreApplication::applicationDirPath()+"/LICENSES")))
            QMessageBox::warning(this,"Error","Error: the LICENSES folder does not exist\nTry to reinstall the program.\nAlternatively, all licenses can be downloaded from:\n"
                                                "https://repo.msys2.org/mingw/sources/");
    } else if ((QPushButton*) clickedButton == ViewAllSourcesButton) {
        if (!QDesktopServices::openUrl(QUrl(QCoreApplication::applicationDirPath()+"/SOURCES")))
            QMessageBox::warning(this,"Error","Error: the SOURCES folder does not exist\nTry to reinstall the program.\nAlternatively, all sources can be downloaded from:\n"
                                                "https://repo.msys2.org/mingw/sources/");
    }
}
