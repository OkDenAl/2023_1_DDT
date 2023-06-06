#include "AddTaskDialog.h"

#include <QMessageBox>
#include <iostream>

#include "Core.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);
    connect(createButton, &QPushButton::clicked, this, &AddTaskDialog::on_createButton_clicked);
    connect(backButton, &QPushButton::clicked, this, &AddTaskDialog::on_backButton_clicked);
}

void AddTaskDialog::setupUi(QDialog *AddTaskDialog) {
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(AddTaskDialog->sizePolicy().hasHeightForWidth());
    AddTaskDialog->setSizePolicy(sizePolicy);

    verticalLayout = new QVBoxLayout(AddTaskDialog);

    nameLabel = new QLabel(AddTaskDialog);
    nameLabel->setText(QString::fromUtf8("Имя задания:"));
    verticalLayout->addWidget(nameLabel);

    name = new QLineEdit(AddTaskDialog);
    verticalLayout->addWidget(name);

    thresholLabel = new QLabel(AddTaskDialog);
    thresholLabel->setText(QString::fromUtf8("Порог:"));
    verticalLayout->addWidget(thresholLabel);

    threshold = new QLineEdit(AddTaskDialog);
    verticalLayout->addWidget(threshold);

    label = new QLabel(AddTaskDialog);
    label->setText(QString::fromUtf8("Введите текст задания"));
    verticalLayout->addWidget(label);

    editor = new QTextEdit(AddTaskDialog);
    verticalLayout->addWidget(editor);

    createButton = new QPushButton(AddTaskDialog);
    createButton->setText(QString::fromUtf8("Создать задание"));
    verticalLayout->addWidget(createButton);

    backButton = new QPushButton(AddTaskDialog);
    backButton->setText(QString::fromUtf8("Назад"));
    verticalLayout->addWidget(backButton);
}

void AddTaskDialog::on_createButton_clicked() {
    std::string desc = editor->toPlainText().toUtf8().constData();
    double th = threshold->text().toDouble();
    std::string n = name->text().toUtf8().constData();
    if (desc.empty() || n.empty() || threshold->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка отправки", "Поля не могут быть пустыми");
        return;
    }

    unsigned result = Core::createTask(n, desc, th);
    switch (result) {
        case 200:
            accept();
            close();
            break;
        default:
            QMessageBox::critical(this, "Отправка невозможна", "Нет соединения с сервером");
    }
}

void AddTaskDialog::on_backButton_clicked() {
    reject();
    close();
}
