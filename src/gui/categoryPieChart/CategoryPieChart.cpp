// CategoryPieChart.cpp
#include "CategoryPieChart.h"
#include <QPainter>
#include <QFont>

CategoryPieChart::CategoryPieChart(const QString &categoryName, QWidget *parent)
    : QWidget(parent), categoryName(categoryName) {
    if (categoryName == "ВСЕ ЗАДАЧИ") setFixedSize(750, 750);
    else setFixedSize(350, 350);
    setAutoFillBackground(true);
}

void CategoryPieChart::setValue(int percent) {
    this->percent = qBound(0, percent, 100);
    update();
}

void CategoryPieChart::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = Qt::lightGray;
    QColor fgColor;
    if (categoryName == "ВСЕ ЗАДАЧИ") {
        fgColor = QColor(65, 65, 186);
        painter.setPen(QPen(bgColor, 100));
    } else {
        fgColor = QColor(186, 65, 65);
        painter.setPen(QPen(bgColor, 35));
    }


    int side = qMin(width() - 55, height()) - 55;
    QRect rect((width() - side) / 2, (height() - side) / 2, side, side);

    painter.drawEllipse(rect);

    if (percent > 0) {
        if (categoryName == "ВСЕ ЗАДАЧИ") {
            painter.setPen(QPen(fgColor, 80));
        } else {
            painter.setPen(QPen(fgColor, 20));
        }
        painter.drawArc(rect, 90 * 16, -percent * 3.6 * 16);
    }

    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(12);
   // font.setBold(true);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignTop | Qt::AlignHCenter, categoryName);

    if (categoryName == "ВСЕ ЗАДАЧИ") {
        font.setPointSize(80);
    } else {
        font.setPointSize(30);
    }

    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, QString::number(percent) + "%");
}
