//
// Created by unf0r9et on 28.11.25.
//

#include "../windows/StatisticsWindow.h"

#include <qboxlayout.h>
#include <QPushButton>
#include "interfaces/WindowOptions.h"
#include "categoryPieChart/CategoryPieChart.h"
#include "databaseManager/DatabaseManager.h"


#include <QGridLayout>

StatisticsWindow::StatisticsWindow(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("StatisticsWindow");

    auto *backButton = new QPushButton("Back", this);
    backButton->setGeometry(10, 10, 80, 30);
    connect(backButton, &QPushButton::clicked, this, &StatisticsWindow::backToMenuClicked);

    allChart = new CategoryPieChart("ВСЕ ЗАДАЧИ", this);
    studyChart = new CategoryPieChart("Учёба", this);
    personalChart = new CategoryPieChart("Хобби", this);
    workChart = new CategoryPieChart("Работа", this);
    otherChart = new CategoryPieChart("Другое", this);

    allChart->setGeometry(625, 250, 750, 750);
    studyChart->setGeometry(250, 100, 350, 350);
    personalChart->setGeometry(1400, 100, 350, 350);
    workChart->setGeometry(250, 800, 350, 350);
    otherChart->setGeometry(1400, 800, 350, 350);
    loadStatistics();
}



