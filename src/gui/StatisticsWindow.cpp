//
// Created by unf0r9et on 28.11.25.
//

#include "../windows/StatisticsWindow.h"

#include <qboxlayout.h>
#include <QPushButton>
#include "interfaces/WindowOptions.h"
#include "categoryPieChart/CategoryPieChart.h"
#include "databaseManager/DatabaseManager.h"
#include "styleloader/StyleLoader.h"


#include <QGridLayout>
#include <QLabel>

StatisticsWindow::StatisticsWindow(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("StatisticsWindow");
    setAttribute(Qt::WA_StyledBackground, true);

    auto *backButton = new QPushButton("←", this);
    backButton->setGeometry(10, 10, 100, 50);
    connect(backButton, &QPushButton::clicked, this, &StatisticsWindow::backToMenuClicked);

    const QPixmap photo(":/images/jpeg.png");

    QTransform transform;
    transform.scale(-1, 1);

    QPixmap stretched = photo.scaled(800, 1250, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap mirrored = stretched.transformed(transform, Qt::SmoothTransformation);


    int size = 30;

    auto *photoLayout = new QLabel(this);
    photoLayout->setPixmap(stretched.scaled(800, 120, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    photoLayout->setAlignment(Qt::AlignCenter);
    photoLayout->setGeometry(1000-size/2, 900, size, 400);

    auto *photoLayout_2 = new QLabel(this);
    photoLayout_2->setPixmap(mirrored.scaled(800, 120, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    photoLayout_2->setAlignment(Qt::AlignCenter);
    photoLayout_2->setGeometry(1000-size/2, 0, size, 300);

    auto *photoLayout_3 = new QLabel(this);
    photoLayout_3->setPixmap(stretched.scaled(800, 120, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    photoLayout_3->setAlignment(Qt::AlignCenter);
    photoLayout_3->setGeometry(0, 625-size/2, 700, size);

auto *photoLayout_4 = new QLabel(this);
    photoLayout_4->setPixmap(mirrored.scaled(800, 120, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    photoLayout_4->setAlignment(Qt::AlignCenter);
    photoLayout_4->setGeometry(1300, 625-size/2, 700, size);

    auto *textStudy = new QLabel(this);
    textStudy->setText("УЧЁБА");
    textStudy->setGeometry(345, 300, 350, 350);
    auto *textHobby = new QLabel(this);
    textHobby->setText("ХОББИ");
    textHobby->setGeometry(1500, 300, 350, 350);
    auto *textWork = new QLabel(this);
    textWork->setText("РАБОТА");
    textWork->setGeometry(333, 970, 350, 350);
    auto *textAnother = new QLabel(this);
    textAnother->setText("ДРУГОЕ");
    textAnother->setGeometry(1487, 970, 350, 350);
    auto *textAll = new QLabel(this);
    textAll->setText("ВСЕ ЗАДАЧИ");
    textAll->setGeometry(850, 550, 350, 350);




    allChart = new CategoryPieChart("ВСЕ ЗАДАЧИ", this);
    studyChart = new CategoryPieChart("Учёба", this);
    personalChart = new CategoryPieChart("Хобби", this);
    workChart = new CategoryPieChart("Работа", this);
    otherChart = new CategoryPieChart("Другое", this);

    allChart->setGeometry(625, 250, 750, 750);
    studyChart->setGeometry(250, 100, 350, 350);
    personalChart->setGeometry(1400, 100, 350, 350);
    workChart->setGeometry(250, 770, 350, 350);
    otherChart->setGeometry(1400, 770, 350, 350);

    loadStatistics();
    StyleLoader::loadStyleSheet(this, ":/styles/statisticsWindow.qss");
}
