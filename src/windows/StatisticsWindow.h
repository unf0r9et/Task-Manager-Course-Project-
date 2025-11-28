//
// Created by unf0r9et on 28.11.25.
//

#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>

#include "../gui/categoryPieChart/CategoryPieChart.h"
#include "databaseManager/dataBaseUser/DataBaseUser.h"

class StatisticsWindow : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);

    int currentUserId = -1;

    void loadStatistics();

signals:
    void backToMenuClicked();

private:
    void onBackButtonClicked();
    CategoryPieChart *studyChart;
    CategoryPieChart *personalChart;
    CategoryPieChart *workChart;
    CategoryPieChart *otherChart;
    CategoryPieChart *allChart;
};


#endif //STATISTICSWINDOW_H
