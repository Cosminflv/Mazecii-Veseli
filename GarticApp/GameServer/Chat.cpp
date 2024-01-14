module Chat;

std::vector<std::pair<std::string, std::string>> Chat::getChatVector() {
    return m_messages;
}

void Chat::WriteMessage(std::pair<std::string, std::string> message) {
    m_messages.push_back(message);
}