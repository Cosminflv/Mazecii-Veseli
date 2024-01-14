export module Chat;

import <vector>;
import <string>;
import <utility>;

export class Chat {
public:
    std::vector<std::pair<std::string, std::string>> getChatVector();
    void WriteMessage(std::pair<std::string, std::string> message);
private:
    std::vector<std::pair<std::string, std::string>> m_messages;
};