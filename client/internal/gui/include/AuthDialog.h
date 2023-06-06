#ifndef AUTH_DIALOG_H
#define AUTH_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class AuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);

public slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();

private:
    QVBoxLayout *verticalLayout = nullptr;
    QWidget *fields = nullptr;
    QFormLayout* fieldsLayout = nullptr;
    QLabel *loginLabel = nullptr;
    QLineEdit *login = nullptr;
    QLabel *passwordLabel = nullptr;
    QLineEdit *password = nullptr;
    QPushButton *loginButton = nullptr;
    QPushButton *backButton = nullptr;

    void setupUi(QDialog *AuthDialog);
    void retranslateUi(QDialog *AuthDialog);
};

#endif  // AUTH_DIALOG_H
