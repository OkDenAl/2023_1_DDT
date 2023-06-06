#ifndef INCLUDE_UIMANAGER_H_
#define INCLUDE_UIMANAGER_H_

#include <QObject>
#include "EntryWindow.h"
#include "TasksWindow.h"

class UIManager : public QWidget {
Q_OBJECT
public:
    UIManager(QWidget *parent = nullptr);

public slots:
    void showEntryWindow();
    void showTasksWindow();

private:
    EntryWindow* entryWindow = nullptr;
    TasksWindow* userWindow = nullptr;
};

#endif  // INCLUDE_UIMANAGER_H_
