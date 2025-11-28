#include "AppController.h"

#include <QMessageBox>

AppController::AppController(QStackedWidget *stack, QObject *parent)
    : QObject(parent), stack(stack) {
    if (!dbManager.initDatabase()) {
    }

    authorization = new Authorization();
    registration = new Registration();
    applicationMenu = new ApplicationMenu();
    editTasks = new EditTasks();
    chatBotWindow = new ChatBotWindow();
    statisticsWindow = new StatisticsWindow();

    registration->setDatabaseManager(&dbManager);
    authorization->setDatabaseManager(&dbManager);
    editTasks->setDatabaseManager(&dbManager);
    chatBotWindow->setDatabaseManager(&dbManager);
    statisticsWindow->setDatabaseManager(&dbManager);

    stack->addWidget(authorization);
    stack->addWidget(registration);
    stack->addWidget(applicationMenu);
    stack->addWidget(editTasks);
    stack->addWidget(chatBotWindow);
    stack->addWidget(statisticsWindow);


    connect(authorization, &Authorization::registerRequested, this, &AppController::showRegistration);
    connect(authorization, &Authorization::loginSuccessful, this, &AppController::showApplicationMenu);
    connect(registration, &Registration::authorizationRequested, this, &AppController::showAuthorization);
    connect(applicationMenu, &ApplicationMenu::editTasksRequested, this, &AppController::showEditTasks);
    connect(applicationMenu, &ApplicationMenu::chatBotWindowRequested, this, &AppController::showChatBotWindow);
    connect(applicationMenu, &ApplicationMenu::statisticsWindowRequested, this, &AppController::showStatisticsWindow);
    connect(editTasks, &EditTasks::backToMenuClicked, this, &AppController::showApplicationMenu);
    connect(chatBotWindow, &ChatBotWindow::backToMenuClicked, this, &AppController::showApplicationMenu);
    connect(statisticsWindow, &StatisticsWindow::backToMenuClicked, this, &AppController::showApplicationMenu);
}

void AppController::showAuthorization() {
    stack->setCurrentWidget(authorization);
}

void AppController::showRegistration() {
    stack->setCurrentWidget(registration);
}

void AppController::showApplicationMenu() {
    currentUserId = dbManager.getUserId(authorization->userLogin);
    stack->setCurrentWidget(applicationMenu);
}

void AppController::showEditTasks() {
    if (editTasks->currentUserId == -1) editTasks->currentUserId = currentUserId;
    editTasks->showAllTasks();
    stack->setCurrentWidget(editTasks);
}

void AppController::showChatBotWindow() {
    if (chatBotWindow->currentUserId == -1) chatBotWindow->currentUserId = currentUserId;
    stack->setCurrentWidget(chatBotWindow);
}

void AppController::showStatisticsWindow() {
    if (statisticsWindow->currentUserId == -1) statisticsWindow->currentUserId = currentUserId;
    statisticsWindow->loadStatistics();
    stack->setCurrentWidget(statisticsWindow);
}
