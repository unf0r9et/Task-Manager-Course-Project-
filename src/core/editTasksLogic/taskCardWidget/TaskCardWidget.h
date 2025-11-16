#ifndef TASKCARDWIDGET_H
#define TASKCARDWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

class TaskCardWidget : public QWidget {
    Q_OBJECT

public:
    explicit TaskCardWidget(int taskId, const QString &title, const QString &description,
                            const QString &category, const QDate &deadline, bool completed,
                            QWidget *parent = nullptr);

signals:
    void editingRequested(int taskId);

    void completedChanged(int taskId, bool completed);

private slots:
    void onCompletedChanged();

    void onEditingClicked();

private:
    int taskId;
    QCheckBox *completedCheckBox = nullptr;
    QLabel *titleLabel = nullptr;
    QLabel *descriptionLabel = nullptr;
    QLabel *categoryLabel = nullptr;
    QLabel *deadlineLabel = nullptr;
    QPushButton *deleteButton = nullptr;
};

#endif // TASKCARDWIDGET_H
