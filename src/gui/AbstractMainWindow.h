#pragma once

#include <QMainWindow>
#include <QStackedWidget>

class AppController;

class AbstractMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AbstractMainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    AppController *controller;
};
