#ifndef SIGN_UP_DIALOG_H
#define SIGN_UP_DIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

class SignUpDialog : public QDialog {
Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);

private slots:
    void on_signUpButton_clicked();
    void on_backButton_clicked();

private:
    QVBoxLayout *verticalLayout = nullptr;
    QWidget *fields = nullptr;
    QFormLayout* fieldsLayout = nullptr;
    QLabel *loginLabel = nullptr;
    QLineEdit *login = nullptr;
    QLabel* usernameLabel = nullptr;
    QLineEdit *username = nullptr;
    QLabel *passwordLabel = nullptr;
    QLineEdit *password = nullptr;
    QLabel *passwordRepeatLabel = nullptr;
    QLineEdit *passwordRepeat = nullptr;
    QPushButton *signUpButton = nullptr;
    QPushButton *backButton = nullptr;

    void setupUi(QDialog *SignUpDialog);
    void retranslateUi(QDialog *SignUpDialog);
};

#endif // SIGN_UP_DIALOG_H
