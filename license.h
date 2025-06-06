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

#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class License;
}

class License : public QDialog
{
    Q_OBJECT

public:
    explicit License(QWidget *parent = nullptr);
    ~License();
    void setApplicationLicenseText(QString);

public slots:
    void viewAllLicensesOrSourcesFolder(QAbstractButton *clickedButton);

private:
    Ui::License *ui;
    QPushButton *ViewAllLicensesButton;
    QPushButton *ViewAllSourcesButton;
};

#endif // LICENSE_H
