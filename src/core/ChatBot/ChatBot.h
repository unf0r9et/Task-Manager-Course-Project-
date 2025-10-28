//
// Created by unf0r9et on 29.10.25.
//

#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>

class ChatBot {
public:
   static std::string extractContent(const std::string &text);

   static std::string get_access_token();

   static std::string send_request_to_gigachat(const std::string &message, const std::string &access_token);
};


#endif //CHATBOT_H
