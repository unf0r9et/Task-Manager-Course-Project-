//
// Created by unf0r9et on 27.11.25.
//

#include "../../../windows/ChatBotWindow.h"
#include "ChatBot/ChatBot.h"
#include <nlohmann/json.hpp>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QString>
#include "databaseManager/DatabaseManager.h"


using json = nlohmann::json;

void ChatBotWindow::sendRequest() {
    QString request = input->toPlainText();
    std::string requestSTD = request.toStdString();

    std::string access_token = ChatBot::get_access_token();
    if (access_token.empty()) {
        output->setText("Ошибка: не удалось получить Access Token");
        return;
    }

    std::string response = ChatBot::extractContent(
        ChatBot::send_request_to_gigachat(requestSTD, access_token)
    );

    lastResponse = QString::fromStdString(response);

    json parsed = json::parse(lastResponse.toStdString());

    QString title = QString::fromStdString(parsed["title"].get<std::string>());
    QString description = QString::fromStdString(parsed["description"].get<std::string>());
    QString category = QString::fromStdString(parsed["category"].get<std::string>());
    QString deadlineStr = QString::fromStdString(parsed["deadline"].get<std::string>());

    QString outputStr = "<b>∘ Название: </b>" + title +
                        "<br><b>∘ Описание: </b>" + description +
                        "<br><b>∘ Категория: </b>" + category +
                        "<br><b>∘ Дедлайн: </b>" + deadlineStr;

    if (response.empty())
        output->setText("Ошибка: пустой ответ от GigaChat");
    else
        output->setText(outputStr);
}

void ChatBotWindow::onAddTaskPressed() {
    try {
        json parsed = json::parse(lastResponse.toStdString());

        QString title = QString::fromStdString(parsed["title"].get<std::string>());
        QString description = QString::fromStdString(parsed["description"].get<std::string>());
        QString category = QString::fromStdString(parsed["category"].get<std::string>());
        QString deadlineStr = QString::fromStdString(parsed["deadline"].get<std::string>());

        QDate deadline = QDate::fromString(deadlineStr, "yyyy-MM-dd");

        if (!deadline.isValid()) {
            qWarning() << "Invalid date format:" << deadlineStr;
            deadline = QDate::currentDate().addDays(3);
        }

        if (dbManager) dbManager->addTask(currentUserId, title, description, category, deadline);
        else {
            QMessageBox::critical(this, "ОШИБКА", "ОШИБКА при добавлении задачи.");
        }
    } catch (const json::parse_error &e) {
        QMessageBox::critical(this, "ОШИБКА", "ОШИБКА при добавлении задачи.");
        qCritical() << "JSON parse error:" << e.what();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "ОШИБКА", "ОШИБКА при добавлении задачи.");
        qCritical() << "General error:" << e.what();
    }
    resetWidget();
}

void ChatBotWindow::onNotAddTaskPressed() {
    resetWidget();
}

void ChatBotWindow::onBackButtonClicked() {
    resetWidget();
    emit backToMenuClicked();
}

void ChatBotWindow::resetWidget() {
    lastResponse = nullptr;
    input->setText("");
    output->setText(
        "Привет! Я БРАНК. Введи краткое описание того,\nчто тебе надо сделать. И я придумаю все остальное =)");
}
