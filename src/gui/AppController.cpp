//
// Created by unf0r9et on 23.10.25.
//
// AppController.cpp
#include "AppController.h"

AppController::AppController(QStackedWidget *stack, QObject *parent)
    : QObject(parent), stack(stack) {

    authorization = new Authorization();
    registration = new Registration();

    stack->addWidget(authorization);
    stack->addWidget(registration);

    connect(authorization, &Authorization::registerRequested, this, &AppController::showRegistration);
    //connect(authorization, &Authorization::loginSuccessful, this, &AppController::showDashboard);
    //connect(registration, &Registration::backRequested, this, &AppController::showAuthorization);

}

void AppController::showAuthorization() {
    stack->setCurrentWidget(authorization);
}

void AppController::showRegistration() {
    stack->setCurrentWidget(registration);
}

