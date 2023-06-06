#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "AuthDialog.h"
#include "SignUpDialog.h"

class EntryWindow : public QMainWindow {
Q_OBJECT

public:
    EntryWindow(QWidget *parent = nullptr);

signals:
    void showTasksWindow();

public slots:
    void on_exitButton_clicked();
    void on_loginButton_clicked();
    void on_signUpButton_clicked();

private:

    QWidget *centralwidget = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QLabel *introLabel = nullptr;
    QPushButton *loginButton = nullptr;
    QSpacerItem *horizontalSpacer = nullptr;
    QPushButton *signUpButton = nullptr;
    QSpacerItem *horizontalSpacer_2 = nullptr;
    QPushButton *exitButton = nullptr;
    QMenuBar *menubar = nullptr;
    QStatusBar *statusbar = nullptr;

    void setupUi(QMainWindow *EntryWindow);
    void retranslateUi(QMainWindow *EntryWindow);
};

#endif  // MAINWINDOW_H
