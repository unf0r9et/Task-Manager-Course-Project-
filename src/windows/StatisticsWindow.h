//
// Created by unf0r9et on 28.11.25.
//

#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>
#include "databaseManager/dataBaseUser/DataBaseUser.h"


class StatisticsWindow : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);

    int currentUserId = -1;

signals:
    void backToMenuClicked();

private:
    void onBackButtonClicked();
};


#endif //STATISTICSWINDOW_H
