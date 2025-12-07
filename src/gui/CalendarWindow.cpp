// CalendarWindow.cpp
#include "../windows/CalendarWindow.h"
#include "styleloader/StyleLoader.h"

CalendarWindow::CalendarWindow(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("CalendarWindow");
    setAttribute(Qt::WA_StyledBackground, true);


    auto *label = new QLabel(this);
    label->setText("Задачи на выбранную дату:");
    label->setGeometry(20, 460, 600, 100);
    label->setObjectName("Label");
    auto *backButton = new QPushButton("←", this);
    backButton->setGeometry(10, 10, 100, 50);
    backButton->setObjectName("BackButton");
    connect(backButton, &QPushButton::clicked, this, &CalendarWindow::onBackButtonClicked);

    prevButton = new QPushButton("<", this);
    nextButton = new QPushButton(">", this);
    prevButton->setFixedWidth(100);
    nextButton->setFixedWidth(100);
    monthLabel = new QLabel(this);
    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setStyleSheet("font-size: 30px; font-weight: bold;");

    auto *navLayout = new QHBoxLayout();
    navLayout->addStretch();
    navLayout->addWidget(prevButton);
    navLayout->addSpacing(15);
    navLayout->addWidget(monthLabel);
    navLayout->addSpacing(15);
    navLayout->addWidget(nextButton);
    navLayout->addStretch();

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
        label->setStyleSheet("font-weight: bold; background-color: #1f1f1f; font-size: 20px;");
        gridLayout->addWidget(label, 0, i);
    }

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            auto *button = new QPushButton(this);
            button->setFixedSize(100, 40);
            button->setStyleSheet("QPushButton { background-color: #1f1f1f;}"
                "QPushButton:hover { background-color: #2f2f2f; }");
            gridLayout->addWidget(button, row + 1, col);
            dayButtons.append(button);
        }
    }

    taskList = new QListWidget(this);
    taskList->setObjectName("TaskList");
    taskList->setMaximumHeight(700);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addSpacing(80);
    mainLayout->addLayout(navLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(new QLabel(this));
    mainLayout->addWidget(taskList);

    setLayout(mainLayout);

    QDate today = QDate::currentDate();
    currentYear = today.year();
    currentMonth = today.month();

    updateNavigation();
    showMonth(currentYear, currentMonth);
    StyleLoader::loadStyleSheet(this, ":/styles/calendarWindow.qss");
}
