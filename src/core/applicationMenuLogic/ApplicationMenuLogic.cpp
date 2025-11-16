//
// Created by unf0r9et on 15.11.25.
//

#include "../../windows/ApplicationMenu.h"

void ApplicationMenu::editTasksClicked() {
    emit editTasksRequested();
}

void ApplicationMenu::chatBotClicked() {
    emit chatBotWidgetRequested();
}

void ApplicationMenu::statisticsClicked() {
    emit statisticsWidgetRequested();
}

void ApplicationMenu::calendarClicked() {
    emit calendarWidgetRequested();
}
