#pragma once

#include <QMainWindow>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QScrollArea>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QTextEdit>
#include <QThread>
#include "Task.h"
#include "TasksWindow.h"
#include "Solution.h"
#include "Core.h"

class SolutionDownloadTask : public QObject {
Q_OBJECT
public:
    SolutionDownloadTask(const int& task_id, const std::string& filename, const std::string& path_to_file)
        : task_id(task_id), filename(filename), path_to_file(path_to_file) {}

    ~SolutionDownloadTask() {
        qDebug() << "DownloadTask die";
    }

public slots:
    void Start() {
        std::pair<Solution, Solution::Codes> result = Core::submitSolution(task_id, filename, path_to_file);
        emit Ready(result);
    }

signals:
    void Ready(std::pair<Solution, Solution::Codes> data);

private:
    int task_id;
    std::string filename;
    std::string path_to_file;
};

class SolutionsWindow : public QMainWindow {
Q_OBJECT

public:
    explicit SolutionsWindow(Task task, QWidget *parent = nullptr);

private slots:
    void on_backButton_clicked();
    void on_chooseFileButton_clicked();
    void on_sendButton_clicked();
    void on_solutionData_ready(std::pair<Solution, Solution::Codes> data);

private:

    Task task;
    std::string path_to_file;

    QWidget *centralwidget = nullptr;
    QGroupBox* taskBox = nullptr;
    QVBoxLayout* taskLayout = nullptr;
    QVBoxLayout* verticalLayout = nullptr;
    QLabel* taskDescription = nullptr;
    QPushButton* chooseFileButton = nullptr;
    QLabel* filename = nullptr;
    QPushButton* sendButton = nullptr;
    QTextEdit* result = nullptr;
    QPushButton* backButton = nullptr;
    QWidget* solutionWidget = nullptr;
    QGridLayout* solutionLayout = nullptr;
    QLabel* originalLabel = nullptr;
    QTextEdit* original = nullptr;
    QLabel* currentLabel = nullptr;
    QTextEdit* current = nullptr;
    QThread thread;

    void setupUi(QMainWindow *UserWindow);
};
