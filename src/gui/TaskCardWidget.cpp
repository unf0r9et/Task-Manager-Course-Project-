#include "../windows/widgets/TaskCardWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QDate>
#include "styleloader/StyleLoader.h"


TaskCardWidget::TaskCardWidget(int taskId, const QString &title, const QString &description,
                               const QString &category, const QDate &deadline, bool completed,
                               QWidget *parent)
    : QWidget(parent), taskId(taskId) {
    setObjectName("TaskCard");
    setAttribute(Qt::WA_StyledBackground, true);

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


    QDate today = QDate::currentDate();
    if (deadline < today) {
        deadlineLabel->setStyleSheet("color: #771213; font-weight: bold;");
    } else {
        deadlineLabel->setStyleSheet("");
    }


    deleteButton = new QPushButton(".", this);
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

    setMinimumHeight(200);
    setMaximumHeight(230);

    if (completed) {
        titleLabel->setStyleSheet("text-decoration: line-through;");
        descriptionLabel->setStyleSheet("color: gray;");
    }
    StyleLoader::loadStyleSheet(this, ":/styles/taskCardWidget.qss");
}

void TaskCardWidget::onCompletedChanged() {
    emit completedChanged(taskId, completedCheckBox->isChecked());
    if (completedCheckBox->isChecked()) {
        titleLabel->setStyleSheet("text-decoration: line-through;");
        descriptionLabel->setStyleSheet("color: #771213;");
    } else {
        titleLabel->setStyleSheet("");
        descriptionLabel->setStyleSheet("");
    }
}

void TaskCardWidget::onEditingClicked() {
    emit editingRequested(taskId);
}
