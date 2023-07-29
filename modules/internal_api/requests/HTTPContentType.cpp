#include "HTTPContentType.hpp"

HTTPContentType::HTTPContentType() {
    m_sType = "";
}

std::string HTTPContentType::getType() {
    return m_sType;
}