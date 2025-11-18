//
// Created by unf0r9et on 16.11.25.
//

#ifndef EDITINGTASKMENU_H
#define EDITINGTASKMENU_H

#include <QWidget>

#include "../addTaskWidgetMenu/AddTaskWidgetMenu.h"


class EditingTaskMenu : public QWidget{
    Q_OBJECT

public:
    explicit EditingTaskMenu(DatabaseManager *dbManager, QWidget *parent = nullptr);
    signals:
        void taskWasAdded();
    void taskWasNotAdded();

private slots:
    void onAcceptClicked();
    void onRejectClicked();

private:
    DatabaseManager *dbManager = nullptr;
    QLineEdit *titleEdit = nullptr;
    QTextEdit *descriptionEdit = nullptr;
    QComboBox *categoryCombo = nullptr;
    QDateEdit *deadlineEdit = nullptr;
};


#endif //EDITINGTASKMENU_H
