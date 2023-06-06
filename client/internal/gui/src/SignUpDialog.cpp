#include "SignUpDialog.h"

#include <QCoreApplication>
#include <QPushButton>
#include <QMessageBox>

#include "Core.h"

SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);
}

void SignUpDialog::setupUi(QDialog *SignUpDialog) {
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(SignUpDialog->sizePolicy().hasHeightForWidth());
    SignUpDialog->setSizePolicy(sizePolicy);

    verticalLayout = new QVBoxLayout(SignUpDialog);

    fields = new QWidget(SignUpDialog);
    fields->setEnabled(true);

    fieldsLayout = new QFormLayout(fields);

    loginLabel = new QLabel(this);
    login = new QLineEdit(this);

    fieldsLayout->addRow(loginLabel, login);

    usernameLabel = new QLabel(this);
    username = new QLineEdit(this);

    fieldsLayout->addRow(usernameLabel, username);

    passwordLabel = new QLabel(this);
    password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);

    fieldsLayout->addRow(passwordLabel, password);

    passwordRepeatLabel = new QLabel(this);
    passwordRepeat = new QLineEdit(this);
    passwordRepeat->setEchoMode(QLineEdit::Password);

    fieldsLayout->addRow(passwordRepeatLabel, passwordRepeat);

    verticalLayout->addWidget(fields);

    signUpButton = new QPushButton(SignUpDialog);
    signUpButton->setDefault(true);

    verticalLayout->addWidget(signUpButton);

    backButton = new QPushButton(SignUpDialog);

    verticalLayout->addWidget(backButton);

    retranslateUi(SignUpDialog);

    connect(signUpButton, &QPushButton::clicked, this, &SignUpDialog::on_signUpButton_clicked);
    connect(backButton, &QPushButton::clicked, this, &SignUpDialog::on_backButton_clicked);
}

void SignUpDialog::retranslateUi(QDialog *SignUpDialog) {
    SignUpDialog->setWindowTitle("Регистрация");
    loginLabel->setText("Введите логин");
    usernameLabel->setText("Введите имя");
    passwordLabel->setText("Введите пароль");
    passwordRepeatLabel->setText("Повторите пароль");
    signUpButton->setText("Зарегистрироваться");
    backButton->setText("Назад");
}

void SignUpDialog::on_signUpButton_clicked() {
    std::string log = this->login->text().toUtf8().constData();
    std::string usr = this->username->text().toUtf8().constData();
    std::string pass = this->password->text().toUtf8().constData();
    std::string passRepeat = this->passwordRepeat->text().toUtf8().constData();
    if (pass == passRepeat && !log.empty() && !usr.empty()) {
        unsigned response = Core::signUp(log, usr, pass);
        switch (response) {
            case 200:
                QMessageBox::information(this, "Успех!", "Вы успешно зарегистрированы!");
                accept();
                close();
                break;
            case 403:
                QMessageBox::warning(this, "Регистрация невозможна", "Произошла ошибка! Попробуйте ещё раз. \n"
                                                                     "\n"
                                                                     "Логин должен быть в виде: example@mail.ru \n"
                                                                     "Имя от 3 до 20 символов \n"
                                                                     "Пароль от 8 до 30 символов");
                break;
            default:
                QMessageBox::critical(this, "Регистрация невозможна!", "Нет соединения с сервером!");
        }

    } else if (log.empty()) {
        QMessageBox::warning(this, "Ошибка!", "Логин не может быть пустым!");
    } else if (usr.empty()) {
        QMessageBox::warning(this, "Ошибка!", "Имя не может быть пустым!");
    } else {
        QMessageBox::warning(this, "Ошибка!", "Пароли не совпадают!");
    }
}

void SignUpDialog::on_backButton_clicked() {
    reject();
    close();
}

// setupUi
