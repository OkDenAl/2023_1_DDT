#include "TasksWindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>

#include "SolutionsWindow.h"
#include "AddTaskDialog.h"
#include "UIManager.h"
#include "Core.h"

TasksWindow::TasksWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);
    connect(tasks, &QComboBox::currentIndexChanged, this, &TasksWindow::indexChanged);
    connect(goToTaskButton, &QPushButton::clicked, this, &TasksWindow::on_goToTaskButton_clicked);
    connect(backButton, &QPushButton::clicked, this, &TasksWindow::on_backButton_clicked);
    connect(addTaskButton, &QPushButton::clicked, this, &TasksWindow::on_addTaskButton_clicked);
}



void TasksWindow::setupUi(QMainWindow *UserWindow) {
    tasks_vector = Core::getAllTasks();

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(UserWindow->sizePolicy().hasHeightForWidth());
    UserWindow->setSizePolicy(sizePolicy);

    centralwidget = new QWidget(UserWindow);
    verticalLayout = new QVBoxLayout(centralwidget);

    taskChooseGroupBox = new QGroupBox(centralwidget);
    sizePolicy.setHeightForWidth(taskChooseGroupBox->sizePolicy().hasHeightForWidth());
    taskChooseGroupBox->setFixedHeight(85);
    taskChooseGroupBox->setSizePolicy(sizePolicy);

    taskVerticalLayout = new QVBoxLayout(taskChooseGroupBox);

    label = new QLabel(this);
    label->setText(QString::fromUtf8("Выберите номер задания:"));

    tasks = new QComboBox(this);
    for (int i = 0; i < tasks_vector.size(); i++) {
        tasks->insertItem(i, QString::fromUtf8(tasks_vector[i].name));
    }

    if (tasks_vector.empty()) {
        tasks->insertItem(0, QString::fromUtf8("Пока заданий нет"));
    }
    tasks->setCurrentIndex(0);

    taskVerticalLayout->addWidget(label);
    taskVerticalLayout->addWidget(tasks);

    taskDescription = new QTextEdit(this);
    taskDescription->setReadOnly(true);
    std::string description = tasks_vector.empty() ? "" : tasks_vector[0].description;
    taskDescription->setText(QString(description.c_str()));

    buttonsWidget = new QWidget(centralwidget);
    sizePolicy.setHeightForWidth(buttonsWidget->sizePolicy().hasHeightForWidth());
    buttonsWidget->setFixedHeight(45);

    buttonsLayout = new QHBoxLayout(buttonsWidget);

    goToTaskButton = new QPushButton(this);
    goToTaskButton->setText(QString::fromUtf8("Перейти к сдаче"));

    if (tasks_vector.empty())
        goToTaskButton->setDisabled(true);

    addTaskButton = new QPushButton(this);
    addTaskButton->setText(QString::fromUtf8("Добавить задание"));

    backButton = new QPushButton(this);
    backButton->setText(QString::fromUtf8("Выйти"));

    buttonsLayout->addWidget(goToTaskButton);
    buttonsLayout->addWidget(addTaskButton);
    buttonsLayout->addWidget(backButton);

    verticalLayout->addWidget(taskChooseGroupBox);
    verticalLayout->addWidget(taskDescription);
    verticalLayout->addWidget(buttonsWidget);

    UserWindow->setCentralWidget(centralwidget);
}

void TasksWindow::indexChanged() {
    std::string description = tasks_vector[tasks->currentIndex()].description;
    taskDescription->setText(QString(description.c_str()));
}

void TasksWindow::on_backButton_clicked() {
    Core::logout();
    close();
    qobject_cast<UIManager*>(parent())->showEntryWindow();
}

void TasksWindow::on_goToTaskButton_clicked() {
    hide();
    auto* solutionsWindow = new SolutionsWindow(tasks_vector[tasks->currentIndex()], this);
    solutionsWindow->show();
}

void TasksWindow::on_addTaskButton_clicked() {
    AddTaskDialog addTaskDialog(this);
    if (addTaskDialog.exec() == QDialog::Accepted) {
        updateTasks();
    }
}

void TasksWindow::updateTasks() {
    tasks_vector = Core::getAllTasks();
    tasks->clear();
    for (int i = 0; i < tasks_vector.size(); i++) {
        tasks->insertItem(i, QString::fromUtf8(tasks_vector[i].name));
    }
    tasks->setCurrentIndex(0);

    std::string description = tasks_vector[0].description;
    taskDescription->setText(QString(description.c_str()));

    goToTaskButton->setDisabled(false);
}
