#include "EntryWindow.h"
#include "TasksWindow.h"

#include <QApplication>

#include "UIManager.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    UIManager uiManager;
    uiManager.showEntryWindow();
    return a.exec();
}
