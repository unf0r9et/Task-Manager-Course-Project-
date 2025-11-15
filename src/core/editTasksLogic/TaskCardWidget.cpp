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

    deleteButton = new QPushButton("❌", this);
    deleteButton->setFixedSize(30, 30);
    connect(deleteButton, &QPushButton::clicked, this, &TaskCardWidget::onDeleteClicked);

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

    setStyleSheet(R"(
        #TaskCard {
            border: 1px solid gray;
            border-radius: 8px;
            padding: 8px;
            margin: 4px;
            background-color: #f9f9f9;
        }
        #TitleLabel {
            font-weight: bold;
            font-size: 14px;
        }
        #DescriptionLabel {
            font-size: 12px;
            color: gray;
        }
        #CategoryLabel {
            font-style: italic;
            color: #007acc;
        }
        #DeadlineLabel {
            color: #e74c3c;
        }
    )");

    if (completed) {
        titleLabel->setStyleSheet("text-decoration: line-through;");
        descriptionLabel->setStyleSheet("color: gray;");
    }
}

void TaskCardWidget::onCompletedChanged() {
    emit completedChanged(taskId, completedCheckBox->isChecked());
    // Обновим стили в зависимости от статуса
    if (completedCheckBox->isChecked()) {
        titleLabel->setStyleSheet("text-decoration: line-through;");
        descriptionLabel->setStyleSheet("color: gray;");
    } else {
        titleLabel->setStyleSheet("");
        descriptionLabel->setStyleSheet("");
    }
}

void TaskCardWidget::onDeleteClicked() {
    emit deleteRequested(taskId);
}