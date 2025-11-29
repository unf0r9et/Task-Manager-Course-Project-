// CalendarWindow.cpp
#include "CalendarWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDate>
#include <QSqlQuery>
#include "interfaces/WindowOptions.h"

CalendarWindow::CalendarWindow(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("CalendarWindow");

    auto *backButton = new QPushButton("Back", this);
    backButton->setGeometry(10, 10, 80, 30);
    connect(backButton, &QPushButton::clicked, this, &CalendarWindow::onBackButtonClicked);

    prevButton = new QPushButton("<", this);
    nextButton = new QPushButton(">", this);
    monthLabel = new QLabel(this);
    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    auto *navLayout = new QHBoxLayout();
    navLayout->addWidget(prevButton);
    navLayout->addWidget(monthLabel);
    navLayout->addWidget(nextButton);

    connect(prevButton, &QPushButton::clicked, this, [this]() {
        if (currentMonth == 1) {
            currentYear--;
            currentMonth = 12;
        } else {
            currentMonth--;
        }
        showMonth(currentYear, currentMonth);
    });

    connect(nextButton, &QPushButton::clicked, this, [this]() {
        if (currentMonth == 12) {
            currentYear++;
            currentMonth = 1;
        } else {
            currentMonth++;
        }
        showMonth(currentYear, currentMonth);
    });

    auto *gridLayout = new QGridLayout();
    gridLayout->setSpacing(2);

    QStringList weekdays = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    for (int i = 0; i < 7; ++i) {
        auto *label = new QLabel(weekdays[i]);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-weight: bold; background-color: #f0f0f0;");
        gridLayout->addWidget(label, 0, i);
    }

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            auto *button = new QPushButton(this);
            button->setFixedSize(100, 40);
            button->setStyleSheet("QPushButton { background-color: white; border: 1px solid #ccc; }"
                                  "QPushButton:hover { background-color: #e0e0e0; }");
            gridLayout->addWidget(button, row + 1, col);
            dayButtons.append(button);
        }
    }

    taskList = new QListWidget(this);
    taskList->setMaximumHeight(120);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(navLayout);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(new QLabel("Задачи на выбранную дату:"));
    mainLayout->addWidget(taskList);

    setLayout(mainLayout);

    QDate today = QDate::currentDate();
    currentYear = today.year();
    currentMonth = today.month();

    updateNavigation();
    showMonth(currentYear, currentMonth);
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
                "QPushButton { background-color: #FFEB3B; border: 1px solid #FFC107; }"
                "QPushButton:hover { background-color: #FFD54F; }"
            );
        } else {
            dayButtons[index]->setStyleSheet(
                "QPushButton { background-color: white; border: 1px solid #ccc; }"
                "QPushButton:hover { background-color: #e0e0e0; }"
            );
        }

        disconnect(dayButtons[index], nullptr, nullptr, nullptr);
        connect(dayButtons[index], &QPushButton::clicked, this, [this, date]() {
            onDayClicked(date);
        });
    }
}

void CalendarWindow::clearCalendar() {
    for (auto *button : dayButtons) {
        button->setVisible(false);
        button->setText("");
    }
}

void CalendarWindow::updateNavigation() {
    monthLabel->setText(QString::number(currentYear) + " / " + QString::number(currentMonth));
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
            taskList->addItem(query.value(0).toString());
        } while (query.next());
    }
}

