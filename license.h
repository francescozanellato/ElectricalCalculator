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
