#include <QHBoxLayout>
#include <QPushButton>


#include "Registration.h"
#include "interfaces/WindowOptions.h"
#include "StyleLoader.cpp"

Registration::Registration(QWidget *parent) : QWidget(parent) {
    setWindowTitle(tr("Registration"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    auto *button = new QPushButton(this);
    button->setText("BACK");
    button->setFixedWidth(200);
    button->setFixedHeight(100);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    this->setStyleSheet(R"(
QPushButton { color: 000000; })");
    connect(button, &QPushButton::clicked, this, &Registration::backToAuthorization);
}

void Registration::backToAuthorization() {
    emit authorizationRequested();
}
