#ifndef ADDTASKWIDGETMENU_H
#define ADDTASKWIDGETMENU_H

#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class DatabaseManager;

class AddTaskWidgetMenu : public QWidget {
    Q_OBJECT

public:
    explicit AddTaskWidgetMenu(DatabaseManager *dbManager, int currentUserId, QWidget *parent = nullptr);

signals:
    void taskWasAdded();
    void taskWasNotAdded();

private slots:
    void onAcceptClicked();
    void onRejectClicked();
private:
    DatabaseManager *dbManager = nullptr;
    int currentUserId = -1;
    QLineEdit *titleEdit = nullptr;
    QTextEdit *descriptionEdit = nullptr;
    QComboBox *categoryCombo = nullptr;
    QDateEdit *deadlineEdit = nullptr;
};

#endif // ADDTASKWIDGETMENU_H
