// CalendarWindow.h
#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include <QDate>
#include "databaseManager/dataBaseUser/DataBaseUser.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDate>
#include <QSqlQuery>
#include "interfaces/WindowOptions.h"

class QPushButton;
class QLabel;

class CalendarWindow : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit CalendarWindow(QWidget *parent = nullptr);
    void setUserId(int userId);

    signals:
        void backToMenuClicked();

private slots:
    void onBackButtonClicked();
    void onDayClicked(const QDate &date);

private:
    void showMonth(int year, int month);
    void highlightDeadlines();
    void clearCalendar();
    void updateNavigation();

    int currentYear;
    int currentMonth;

    QMap<QDate, bool> deadlineDates;
    int currentUserId = -1;
    QLabel *monthLabel = nullptr;
    QPushButton *prevButton = nullptr;
    QPushButton *nextButton = nullptr;
    QListWidget *taskList = nullptr;
    QVector<QPushButton*> dayButtons;
};

#endif // CALENDARWINDOW_H