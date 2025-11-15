#ifndef ADDTASKWIDGET_H
#define ADDTASKWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class DatabaseManager;

class AddTaskWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddTaskWidget(DatabaseManager *dbManager, QWidget *parent = nullptr);

    signals:
        void taskAdded();  // Сигнал, что задача добавлена

private slots:
    void onAcceptClicked();

private:
    DatabaseManager *dbManager = nullptr;
    QLineEdit *titleEdit = nullptr;
    QTextEdit *descriptionEdit = nullptr;
    QComboBox *categoryCombo = nullptr;
    QDateEdit *deadlineEdit = nullptr;
    QPushButton *acceptButton = nullptr;
    QPushButton *cancelButton = nullptr;
};

#endif // ADDTASKWIDGET_H