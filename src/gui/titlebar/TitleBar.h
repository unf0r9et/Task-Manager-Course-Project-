//
// Created by unf0r9et on 24.10.25.
//

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
#include <QWindow>

class QPushButton;

class TitleBar : public QWidget {
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);

private:
    QPushButton *closeButton;
};

#endif //TITLEBAR_H
