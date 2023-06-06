#include "EntryWindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QMenuBar>
#include <QStatusBar>

#include "AuthDialog.h"
#include "SignUpDialog.h"
#include "UIManager.h"

EntryWindow::EntryWindow(QWidget *parent) : QMainWindow(parent) { setupUi(this); }

void EntryWindow::setupUi(QMainWindow *EntryWindow) {
    EntryWindow->resize(600, 600);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(EntryWindow->sizePolicy().hasHeightForWidth());
    EntryWindow->setSizePolicy(sizePolicy);

    centralwidget = new QWidget(EntryWindow);
    verticalLayout = new QVBoxLayout(centralwidget);

    introLabel = new QLabel(centralwidget);
    introLabel->setText("Добро пожаловать в SourcedOut!");
    introLabel->setGeometry(QRect(140, 200, 331, 31));

    verticalLayout->addWidget(introLabel, 0, Qt::AlignHCenter);

    loginButton = new QPushButton(centralwidget);
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
    loginButton->setSizePolicy(sizePolicy1);
    verticalLayout->addWidget(loginButton);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    verticalLayout->addItem(horizontalSpacer);

    signUpButton = new QPushButton(centralwidget);
    sizePolicy1.setHeightForWidth(signUpButton->sizePolicy().hasHeightForWidth());
    signUpButton->setSizePolicy(sizePolicy1);

    verticalLayout->addWidget(signUpButton);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    verticalLayout->addItem(horizontalSpacer_2);

    exitButton = new QPushButton(centralwidget);
    sizePolicy1.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
    exitButton->setSizePolicy(sizePolicy1);

    verticalLayout->addWidget(exitButton);

    EntryWindow->setCentralWidget(centralwidget);

    connect(signUpButton, &QPushButton::clicked, this, &EntryWindow::on_signUpButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &EntryWindow::on_loginButton_clicked);
    connect(exitButton, &QPushButton::clicked, this, &EntryWindow::on_exitButton_clicked);

    retranslateUi(EntryWindow);
}

void EntryWindow::retranslateUi(QMainWindow *EntryWindow) {
    EntryWindow->setWindowTitle(QCoreApplication::translate("EntryWindow", "Главное окно", nullptr));
    loginButton->setText(QCoreApplication::translate("EntryWindow", "Войти", nullptr));
    signUpButton->setText(QCoreApplication::translate("EntryWindow", "Зарегистрироваться", nullptr));
    exitButton->setText(QCoreApplication::translate("EntryWindow", "Выйти", nullptr));
}

void EntryWindow::on_exitButton_clicked() { QApplication::quit(); }

void EntryWindow::on_loginButton_clicked() {
    AuthDialog authDialog(this);
    if (authDialog.exec() == QDialog::Accepted) {
        hide();
        qobject_cast<UIManager *>(parent())->showTasksWindow();
    }
}

void EntryWindow::on_signUpButton_clicked() {
    SignUpDialog signupDialog(this);
    if (signupDialog.exec() == QDialog::Accepted) {
        hide();
        qobject_cast<UIManager *>(parent())->showTasksWindow();
    }
}
