#include "SolutionsWindow.h"

#include <utility>
#include <fstream>
#include <sstream>
#include <QMessageBox>

#include "Solution.h"
#include "Core.h"

SolutionsWindow::SolutionsWindow(Task task, QWidget *parent) : QMainWindow(parent), task(std::move(task)) {
    setupUi(this);
    connect(backButton, &QPushButton::clicked, this, &SolutionsWindow::on_backButton_clicked);
    connect(chooseFileButton, &QPushButton::clicked, this, &SolutionsWindow::on_chooseFileButton_clicked);
    connect(sendButton, &QPushButton::clicked, this, &SolutionsWindow::on_sendButton_clicked);
    thread.start();
}

void SolutionsWindow::setupUi(QMainWindow *SolutionsWindow) {
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(SolutionsWindow->sizePolicy().hasHeightForWidth());
    SolutionsWindow->setSizePolicy(sizePolicy);

    centralwidget = new QWidget(SolutionsWindow);
    verticalLayout = new QVBoxLayout(centralwidget);

    taskBox = new QGroupBox(centralwidget);
    taskLayout = new QVBoxLayout(taskBox);

    taskDescription = new QLabel(taskBox);
    std::string description = task.description;
    taskDescription->setText(QString(description.c_str()));

    taskLayout->addWidget(taskDescription);

    filename = new QLabel(SolutionsWindow);

    chooseFileButton = new QPushButton(SolutionsWindow);
    chooseFileButton->setText(QString::fromUtf8("Выберите файл"));

    sendButton = new QPushButton(SolutionsWindow);
    sendButton->setText(QString::fromUtf8("Отправить"));

    result = new QTextEdit(SolutionsWindow);
    result->setReadOnly(true);
    result->setText(QString::fromUtf8("Отправьте для принятия решения"));

    solutionWidget = new QWidget(SolutionsWindow);
    solutionLayout = new QGridLayout(solutionWidget);

    originalLabel = new QLabel(solutionWidget);
    originalLabel->setText(QString::fromUtf8("Оригинальное решение"));
    original = new QTextEdit(solutionWidget);
    original->setReadOnly(true);

    currentLabel = new QLabel(solutionWidget);
    currentLabel->setText(QString::fromUtf8("Ваше решение"));
    current = new QTextEdit(solutionWidget);
    current->setReadOnly(true);

    solutionLayout->addWidget(currentLabel, 0, 0);
    solutionLayout->addWidget(originalLabel, 0, 1);
    solutionLayout->addWidget(current, 1, 0);
    solutionLayout->addWidget(original, 1, 1);

    backButton = new QPushButton(SolutionsWindow);
    backButton->setText(QString::fromUtf8("Назад"));

    verticalLayout->addWidget(taskBox);
    verticalLayout->addWidget(filename);
    verticalLayout->addWidget(chooseFileButton);
    verticalLayout->addWidget(sendButton);
    verticalLayout->addWidget(result);
    verticalLayout->addWidget(solutionWidget);
    verticalLayout->addWidget(backButton);

    SolutionsWindow->setCentralWidget(centralwidget);
}

void SolutionsWindow::on_backButton_clicked() {
    close();
    qobject_cast<QMainWindow*>(parent())->show();
}

void SolutionsWindow::on_chooseFileButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a file to send"), QDir::homePath());
    filename->setText(QFileInfo(fileName).fileName());
    path_to_file = fileName.toUtf8().constData();
}

void SolutionsWindow::on_sendButton_clicked() {
    if (path_to_file.empty()) {
        QMessageBox::warning(this, "Ошибка отправки", "Файл должен быть указан");
        return;
    }

    SolutionDownloadTask* downloadTask;
    downloadTask = new SolutionDownloadTask(task.id, filename->text().toUtf8().constData(), path_to_file);
    downloadTask->moveToThread(&thread);

    connect(downloadTask, &SolutionDownloadTask::Ready, this, &SolutionsWindow::on_solutionData_ready);
    connect(downloadTask, &SolutionDownloadTask::Ready, downloadTask, &QObject::deleteLater);

    QMetaObject::invokeMethod(downloadTask, [downloadTask]() {
        downloadTask->Start();
    });

    result->setText(QString::fromStdString("Файл отправлен, идет обработка"));
}

void SolutionsWindow::on_solutionData_ready(std::pair<Solution, Solution::Codes> data) {
    Solution sol;
    Solution::Codes codes;
    std::tie(sol, codes) = data;
    result->setText(QString::fromStdString(sol.result));
    original->setHtml(QString::fromStdString(codes.original));
    current->setHtml(QString::fromStdString(codes.current));
}


