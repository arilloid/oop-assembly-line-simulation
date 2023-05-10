#include "Utilities.h"

namespace sdds {
	char sdds::Utilities::m_delimiter = '\0';

	void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }
	size_t Utilities::getFieldWidth() const { return m_widthField; }
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string tokenStr{};
		// finding the position of the next delimiter in the string
		size_t nextDelim = str.find(m_delimiter, next_pos);
		// throwing the exception if the token is absent
		if (nextDelim == next_pos) {
			more = false;
			throw "No token found!";
		}
		// if the token is the last in the string
		if (nextDelim == std::string::npos) {
			tokenStr = str.substr(next_pos);
			more = false;
		}
		else {
			tokenStr = str.substr(next_pos, nextDelim - next_pos);
		}
		trim(tokenStr);
		if (tokenStr.length() > m_widthField)
			m_widthField = tokenStr.length();
		next_pos = ++nextDelim;
		return tokenStr;
	}
	// class functions
	void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }
	char Utilities::getDelimiter() { return m_delimiter; }
	// additional helper functions
	void Utilities::trim(std::string& str) {
		str.erase(0, str.find_first_not_of(" \t"));
		str.erase(str.find_last_not_of(" \t") + 1);
	}
}
