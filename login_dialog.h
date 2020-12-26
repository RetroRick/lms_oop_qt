#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>

namespace Ui {
class login_dialog;
}

class login_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit login_dialog(QWidget *parent = nullptr);
    ~login_dialog();

private:
    Ui::login_dialog *ui;
private slots:
    void on_goback_tn_clicked();
};

#endif // LOGIN_DIALOG_H