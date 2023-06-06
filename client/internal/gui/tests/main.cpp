#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "UIManager.h"
#include "EntryWindow.h"
#include "TasksWindow.h"

#include <QApplication>

TEST(ConstructorTest, EntryWindow) {
    int fake = 0;
    QApplication a(fake, nullptr);
    EntryWindow mw;
    EXPECT_NO_FATAL_FAILURE(mw.show());
    a.exec();
}

TEST(ConstructorTest, UserWindow) {
    int fake = 0;
    QApplication a(fake, nullptr);
    TasksWindow uw;
    EXPECT_NO_FATAL_FAILURE(uw.show());
    a.exec();
}

TEST(ConstructorTest, UIManagerMW) {
    int fake_argc = 0;
    QApplication a(fake_argc, nullptr);
    UIManager um;
    EXPECT_NO_FATAL_FAILURE(um.showEntryWindow());
    a.exec();
}

TEST(ConstructorTest, UIManagerUW) {
    int fake_argc = 0;
    QApplication a(fake_argc, nullptr);
    UIManager um;
    EXPECT_NO_FATAL_FAILURE(um.showTasksWindow());
    a.exec();
}

TEST(ConstructorTest, MainWindow_AuthDialog) {
    int fake_argc = 0;
    QApplication a(fake_argc, nullptr);
    EntryWindow mainWindow;
    EXPECT_NO_FATAL_FAILURE(mainWindow.getAuthDialog()->show());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
