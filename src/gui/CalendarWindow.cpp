// CalendarWindow.cpp
#include "../windows/CalendarWindow.h"
#include "styleloader/StyleLoader.h"

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
 //   StyleLoader::loadStyleSheet(this, ":/styles/calendarWindow.qss");
}

