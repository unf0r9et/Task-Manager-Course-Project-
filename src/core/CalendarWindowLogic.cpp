//
// Created by unf0r9et on 29.11.25.
//

#include "../windows/CalendarWindow.h"

void CalendarWindow::onBackButtonClicked() {
    emit backToMenuClicked();
}

void CalendarWindow::setUserId(int userId) {
    currentUserId = userId;
    if (currentUserId != -1) {
        deadlineDates.clear();
        if (dbManager) {
            QSqlQuery query;
            query.prepare("SELECT DISTINCT deadline FROM tasks WHERE user_id = ? AND deadline IS NOT NULL");
            query.addBindValue(currentUserId);
            query.exec();

            while (query.next()) {
                QDate date = query.value(0).toDate(); // ← Именно так!
                if (date.isValid()) {
                    deadlineDates[date] = true;
                }
            }
        }
        showMonth(currentYear, currentMonth);
        onDayClicked(QDate(currentYear, currentMonth, 1));
    }
}

void CalendarWindow::showMonth(int year, int month) {
    clearCalendar();

    QDate firstDay(year, month, 1);
    int startDay = firstDay.dayOfWeek();
    if (startDay == 7) startDay = 0;

    int daysInMonth = firstDay.daysInMonth();

    updateNavigation();

    for (int day = 1; day <= daysInMonth; ++day) {
        int index = startDay + day - 1;
        if (index >= dayButtons.size()) break;

        QDate date(year, month, day);
        dayButtons[index]->setText(QString::number(day));
        dayButtons[index]->setVisible(true);

        // Подсветка
        if (deadlineDates.contains(date)) {
            dayButtons[index]->setStyleSheet(
                "QPushButton { background-color: #771213; border: 1px solid #ccc; font-size: 20px;}"
                "QPushButton:hover { background-color: #77132f; font-size: 20px;}"
            );
        } else {
            dayButtons[index]->setStyleSheet(
                "QPushButton { background-color: 1f1f1f; border: 1px solid #ccc; font-size: 20px; }"
                "QPushButton:hover { background-color: #2f2f2f; font-size: 20px;}"
            );
        }

        disconnect(dayButtons[index], nullptr, nullptr, nullptr);
        connect(dayButtons[index], &QPushButton::clicked, this, [this, date]() {
            onDayClicked(date);
        });
    }
}

void CalendarWindow::clearCalendar() {
    for (auto *button: dayButtons) {
        button->setVisible(false);
        button->setText("");
    }
}

void CalendarWindow::updateNavigation() {
    monthLabel->setText(QString::number(currentMonth) + " / " + QString::number(currentYear));
}

void CalendarWindow::onDayClicked(const QDate &date) {
    taskList->clear();
    if (!dbManager || currentUserId == -1) return;

    QSqlQuery query;
    query.prepare("SELECT title FROM tasks WHERE user_id = ? AND deadline = ?");
    query.addBindValue(currentUserId);
    query.addBindValue(date);
    query.exec();

    if (!query.next()) {
        taskList->addItem("Нет задач");
    } else {
        do {
            taskList->addItem("∘ " + query.value(0).toString());
        } while (query.next());
    }
}
