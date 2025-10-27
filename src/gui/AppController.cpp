#include "AppController.h"

AppController::AppController(QStackedWidget *stack, QObject *parent)
    : QObject(parent), stack(stack) {
    authorization = new Authorization();
    registration = new Registration();

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
