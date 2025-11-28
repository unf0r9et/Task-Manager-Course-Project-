//
// Created by unf0r9et on 15.11.25.
//

#ifndef APPLICATIONMENU_H
#define APPLICATIONMENU_H

#include <QWidget>
#include <QPushButton>

class ApplicationMenu : public QWidget {
    Q_OBJECT

public:
    explicit ApplicationMenu(QWidget *parent = nullptr);

    signals:
    void editTasksRequested();
    void chatBotWindowRequested();
    void statisticsWindowRequested();
    void calendarWindowRequested();

    private slots:
    void editTasksClicked();
    void chatBotClicked();
    void statisticsClicked();
    void calendarClicked();

    private:
    QPushButton *editTasksButton;
    QPushButton *chatBotButton;
    QPushButton *statisticsButton;
    QPushButton *calendarButton;

};


#endif //APPLICATIONMENU_H
