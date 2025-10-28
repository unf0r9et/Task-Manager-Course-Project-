#include <QHBoxLayout>
#include <QPushButton>


#include "Registration.h"

#include <QLabel>
#include <QLineEdit>

#include "interfaces/WindowOptions.h"
#include "StyleLoader.cpp"

#include "/home/unf0r9et/myProject/CourseProject/TaskManager/src/core/ChatBot/ChatBot.h"

Registration::Registration(QWidget *parent) : QWidget(parent) {
    setWindowTitle(tr("Registration"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto *layout = new QVBoxLayout(this);

    auto *input = new QLineEdit();
    auto *output = new QLabel("Введите вопрос и нажмите Enter");

    layout->addWidget(input);
    layout->addWidget(output);

    // 🔹 Когда пользователь нажимает Enter:
    connect(input, &QLineEdit::returnPressed, this, [=]() {
        QString request = input->text();
        std::string requestSTD = request.toStdString();

        std::string access_token = ChatBot::get_access_token();
        if (access_token.empty()) {
            output->setText("Ошибка: не удалось получить Access Token");
            return;
        }

        std::string response = ChatBot::extractContent(
            ChatBot::send_request_to_gigachat(requestSTD, access_token)
        );

        if (response.empty())
            output->setText("Ошибка: пустой ответ от GigaChat");
        else
            output->setText(QString::fromStdString(response));
    });
//     auto *button = new QPushButton(this);
//     button->setText("BACK");
//     button->setFixedWidth(200);
//     button->setFixedHeight(100);
//
//     auto *buttonLayout = new QHBoxLayout();
//     buttonLayout->addStretch();
//     buttonLayout->addWidget(button);
//     buttonLayout->addStretch();
//
//     auto *mainLayout = new QVBoxLayout();
//     mainLayout->addStretch();
//     mainLayout->addLayout(buttonLayout);
//     mainLayout->addStretch();
//
//     setLayout(mainLayout);
//
//     this->setStyleSheet(R"(
// QPushButton { color: 000000; })");
//     connect(button, &QPushButton::clicked, this, &Registration::backToAuthorization);
}

void Registration::backToAuthorization() {
    emit authorizationRequested();
}
