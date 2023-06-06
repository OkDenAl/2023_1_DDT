#include "AuthDialog.h"

#include <QMessageBox>
#include <iostream>

#include "Core.h"

AuthDialog::AuthDialog(QWidget *parent) : QDialog(parent) { setupUi(this); }

void AuthDialog::setupUi(QDialog *AuthDialog) {
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(AuthDialog->sizePolicy().hasHeightForWidth());
    AuthDialog->setSizePolicy(sizePolicy);

    verticalLayout = new QVBoxLayout(AuthDialog);

    fields = new QWidget(AuthDialog);
    fields->setEnabled(true);

    fieldsLayout = new QFormLayout(fields);

    loginLabel = new QLabel(this);
    login = new QLineEdit(this);

    fieldsLayout->addRow(loginLabel, login);

    passwordLabel = new QLabel(this);
    password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);

    fieldsLayout->addRow(passwordLabel, password);

    verticalLayout->addWidget(fields);

    loginButton = new QPushButton(AuthDialog);
    loginButton->setDefault(true);

    verticalLayout->addWidget(loginButton);

    backButton = new QPushButton(AuthDialog);

    verticalLayout->addWidget(backButton);

    retranslateUi(AuthDialog);

    connect(loginButton, &QPushButton::clicked, this, &AuthDialog::on_loginButton_clicked);
    connect(backButton, &QPushButton::clicked, this, &AuthDialog::on_backButton_clicked);
}

void AuthDialog::retranslateUi(QDialog *AuthDialog) {
    AuthDialog->setWindowTitle("Вход");
    loginLabel->setText("Логин");
    passwordLabel->setText("Пароль");
    loginButton->setText("Войти");
    backButton->setText("Назад");
}

void AuthDialog::on_loginButton_clicked() {
    std::string log = login->text().toUtf8().constData();
    std::string pass = password->text().toUtf8().constData();
    if (log.empty() || pass.empty()) {
        QMessageBox::warning(this, "Ошибка авторизации", "Логин и пароль не могут быть пустыми");
        return;
    }
    unsigned result = Core::login(std::string(log), std::string(pass));
    switch (result) {
        case 200:
            accept();
            close();
            break;
        case 404:
            QMessageBox::warning(this, "Ошибка авторизации", "Неправильный логин или пароль");
            break;
        default:
            QMessageBox::critical(this, "Авторизация невозможна", "Нет соединения с сервером");
    }
}

void AuthDialog::on_backButton_clicked() {
    reject();
    close();
}
