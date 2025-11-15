#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>

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

#endif // ADDTASKDIALOG_H