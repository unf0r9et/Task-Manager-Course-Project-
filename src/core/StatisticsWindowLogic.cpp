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


    int studyDone = dbManager->getTaskCountByCategory(currentUserId, "Учёба", true);
    int personalDone = dbManager->getTaskCountByCategory(currentUserId, "Хобби", true);
    int workDone = dbManager->getTaskCountByCategory(currentUserId, "Работа", true);
    int otherDone = dbManager->getTaskCountByCategory(currentUserId, "Другое", true);

    int study = dbManager->getTaskCountByCategory(currentUserId, "Учёба", false);
    int personal = dbManager->getTaskCountByCategory(currentUserId, "Хобби", false);
    int work = dbManager->getTaskCountByCategory(currentUserId, "Работа", false);
    int other = dbManager->getTaskCountByCategory(currentUserId, "Другое", false);


    studyChart->setValue(study == 0 ? 0 : 100 * studyDone / (study + studyDone));
    personalChart->setValue(personalDone == 0 ? 0 : 100 * personalDone / (personal + personalDone));
    workChart->setValue(workDone == 0 ? 0 : 100 * workDone / (work + workDone));
    otherChart->setValue(otherDone == 0 ? 0 : 100 * otherDone / (other + otherDone));
    allChart->setValue(total == 0 ? 0 : 100 * (studyDone + personalDone + workDone + otherDone) / total);
}
