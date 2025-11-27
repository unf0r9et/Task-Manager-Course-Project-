#include "TaskCardWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QDate>

TaskCardWidget::TaskCardWidget(int taskId, const QString &title, const QString &description,
                               const QString &category, const QDate &deadline, bool completed,
                               QWidget *parent)
    : QWidget(parent), taskId(taskId) {
    setObjectName("TaskCard");

    completedCheckBox = new QCheckBox(this);
    completedCheckBox->setChecked(completed);
    connect(completedCheckBox, &QCheckBox::toggled, this, &TaskCardWidget::onCompletedChanged);

    titleLabel = new QLabel(title, this);
    titleLabel->setObjectName("TitleLabel");

    descriptionLabel = new QLabel(description, this);
    descriptionLabel->setObjectName("DescriptionLabel");
    descriptionLabel->setWordWrap(true);

    categoryLabel = new QLabel(category, this);
    categoryLabel->setObjectName("CategoryLabel");

    deadlineLabel = new QLabel(deadline.toString("dd.MM.yyyy"), this);
    deadlineLabel->setObjectName("DeadlineLabel");

    deleteButton = new QPushButton("Р", this);
    deleteButton->setFixedSize(50, 50);
    connect(deleteButton, &QPushButton::clicked, this, &TaskCardWidget::onEditingClicked);

    auto *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(completedCheckBox);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(deleteButton);

    auto *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(categoryLabel);
    infoLayout->addStretch();
    infoLayout->addWidget(deadlineLabel);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addLayout(infoLayout);

    setMinimumHeight(100);
    setMaximumHeight(200);

    if (completed) {
        titleLabel->setStyleSheet("text-decoration: line-through;");
        descriptionLabel->setStyleSheet("color: gray;");
    }
}

void TaskCardWidget::onCompletedChanged() {
    emit completedChanged(taskId, completedCheckBox->isChecked());
    if (completedCheckBox->isChecked()) {
        titleLabel->setStyleSheet("text-decoration: line-through;");
        descriptionLabel->setStyleSheet("color: red;");
    } else {
        titleLabel->setStyleSheet("");
        descriptionLabel->setStyleSheet("");
    }
}

void TaskCardWidget::onEditingClicked() {
    emit editingRequested(taskId);
}
