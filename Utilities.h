#pragma once
#include <iostream>

namespace sdds {
	class Utilities {
		size_t m_widthField{ 1 };
		static char m_delimiter;
	public:
		Utilities() = default;
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		// class functions
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		// additional helper functions
		void trim(std::string& str);
	};
}
