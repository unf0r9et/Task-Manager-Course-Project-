// CategoryPieChart.h
#ifndef CATEGORYPIECHART_H
#define CATEGORYPIECHART_H

#include <QWidget>

class CategoryPieChart : public QWidget {
    Q_OBJECT

public:
    explicit CategoryPieChart(const QString &categoryName, QWidget *parent = nullptr);
    void setValue(int percent);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString categoryName;
    int percent = 0;
};

#endif // CATEGORYPIECHART_H