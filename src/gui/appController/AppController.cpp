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

    registration->setDatabaseManager(&dbManager);
    authorization->setDatabaseManager(&dbManager);
    editTasks->setDatabaseManager(&dbManager);

    stack->addWidget(authorization);
    stack->addWidget(registration);
    stack->addWidget(applicationMenu);
    stack->addWidget(editTasks);

    connect(authorization, &Authorization::registerRequested, this, &AppController::showRegistration);
    connect(registration, &Registration::authorizationRequested, this, &AppController::showAuthorization);
    connect(authorization, &Authorization::loginSuccessful, this, &AppController::showApplicationMenu);
    connect(applicationMenu, &ApplicationMenu::editTasksRequested, this, &AppController::showEditTasks);

}

void AppController::showAuthorization() {
    stack->setCurrentWidget(authorization);
}

void AppController::showRegistration() {
    stack->setCurrentWidget(registration);
}

void AppController::showApplicationMenu() {
    stack->setCurrentWidget(applicationMenu);
}

void AppController::showEditTasks() {
    stack->setCurrentWidget(editTasks);
}
