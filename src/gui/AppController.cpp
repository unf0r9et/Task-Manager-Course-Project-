#include "AppController.h"

#include <QMessageBox>

AppController::AppController(QStackedWidget *stack, QObject *parent)
    : QObject(parent), stack(stack) {
    if (!dbManager.initDatabase()) {

    }
    authorization = new Authorization();
    registration = new Registration();


    registration->setDatabaseManager(&dbManager);


    stack->addWidget(authorization);
    stack->addWidget(registration);

    connect(authorization, &Authorization::registerRequested, this, &AppController::showRegistration);
    connect(registration, &Registration::authorizationRequested, this, &AppController::showAuthorization);
}

void AppController::showAuthorization() {
    stack->setCurrentWidget(authorization);
}

void AppController::showRegistration() {
    stack->setCurrentWidget(registration);
}
