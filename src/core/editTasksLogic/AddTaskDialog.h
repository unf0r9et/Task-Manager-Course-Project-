#ifndef ADDTASKWIDGET_H
#define ADDTASKWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class DatabaseManager;

class AddTaskDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddTaskDialog(DatabaseManager *dbManager, QWidget *parent = nullptr);

private slots:
    void onAcceptClicked();

private:
    DatabaseManager *dbManager = nullptr;
    QLineEdit *titleEdit = nullptr;
    QTextEdit *descriptionEdit = nullptr;
    QComboBox *categoryCombo = nullptr;
    QDateEdit *deadlineEdit = nullptr;
};

#endif // ADDTASKWIDGET_H