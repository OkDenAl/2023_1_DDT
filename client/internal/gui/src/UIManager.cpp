#include "UIManager.h"

#include "EntryWindow.h"
#include "TasksWindow.h"
#include "SignUpDialog.h"
#include "AuthDialog.h"

void UIManager::showEntryWindow() {
    entryWindow->show();
}

void UIManager::showTasksWindow() {
    userWindow->show();
}

UIManager::UIManager(QWidget *parent) : QWidget(parent) {
    userWindow = new TasksWindow(this);
    entryWindow = new EntryWindow(this);
}
