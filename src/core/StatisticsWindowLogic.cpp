//
// Created by unf0r9et on 28.11.25.
//

#include "../windows/StatisticsWindow.h"
#include "databaseManager/DatabaseManager.h"

void StatisticsWindow::onBackButtonClicked() {
    emit backToMenuClicked();
}

void StatisticsWindow::loadStatistics() {
    if (!dbManager || currentUserId == -1) return;

    int total = dbManager->getTotalTaskCount(currentUserId);
    if (total == 0) total = 1;


    int studyDone = dbManager->getTaskCountByCategory(currentUserId, "Учёба", true);
    int personalDone = dbManager->getTaskCountByCategory(currentUserId, "Хобби", true);
    int workDone = dbManager->getTaskCountByCategory(currentUserId, "Работа", true);
    int otherDone = dbManager->getTaskCountByCategory(currentUserId, "Другое", true);

    int study = dbManager->getTaskCountByCategory(currentUserId, "Учёба", false);
    int personal = dbManager->getTaskCountByCategory(currentUserId, "Хобби", false);
    int work = dbManager->getTaskCountByCategory(currentUserId, "Работа", false);
    int other = dbManager->getTaskCountByCategory(currentUserId, "Другое", false);


    studyChart->setValue(100 * studyDone / (study + studyDone));
    personalChart->setValue(100 * personalDone / (personal + personalDone));
    workChart->setValue(100 * workDone / (work + workDone));
    otherChart->setValue(100 * otherDone / (other + otherDone));
    allChart->setValue(100 * (studyDone + personalDone + workDone + otherDone) / total);
}