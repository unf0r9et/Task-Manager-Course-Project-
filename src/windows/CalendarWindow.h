// CalendarWindow.h
#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include <QDate>
#include "databaseManager/dataBaseUser/DataBaseUser.h"

class QPushButton;
class QLabel;

class CalendarWindow : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    int currentUserId = -1;
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

    QMap<QDate, bool> deadlineDates; // Даты с задачами

    QLabel *monthLabel = nullptr;
    QPushButton *prevButton = nullptr;
    QPushButton *nextButton = nullptr;
    QListWidget *taskList = nullptr;
    QVector<QPushButton*> dayButtons;
};

#endif // CALENDARWINDOW_H