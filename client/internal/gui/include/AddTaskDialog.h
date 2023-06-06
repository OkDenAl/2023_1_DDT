#pragma once

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>

class AddTaskDialog : public QDialog {
Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);

public slots:
    void on_createButton_clicked();
    void on_backButton_clicked();

private:
    QVBoxLayout* verticalLayout = nullptr;
    QLineEdit* name = nullptr;
    QLabel* nameLabel = nullptr;
    QLineEdit* threshold = nullptr;
    QLabel* thresholLabel = nullptr;
    QLabel* label = nullptr;
    QTextEdit* editor = nullptr;
    QPushButton *createButton = nullptr;
    QPushButton *backButton = nullptr;

    void setupUi(QDialog *AddTaskDialog);
};
