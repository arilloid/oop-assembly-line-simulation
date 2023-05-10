#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station() {
		stId = ++id_generator;
	}
	Station::Station(const std::string& str) {
		if (!str.empty()) {
			size_t pos{ 0 };
			Utilities u{};
			bool more = true;
			itemName = u.extractToken(str, pos, more);
			serialNum = std::stoi(u.extractToken(str, pos, more));
			numInStock = std::stoi(u.extractToken(str, pos, more));
			stDescription = u.extractToken(str, pos, more);
			stId = ++id_generator;
			m_widthField = u.getFieldWidth();
		}
		else {
			throw "Invalid parameter!";
		}
	}
	const std::string& Station::getItemName() const { return itemName; }
	size_t Station::getNextSerialNumber() { return serialNum++; }
	size_t Station::getQuantity() const { return numInStock; }
	void Station::updateQuantity() { numInStock = ((numInStock - 1) >= 0) ? numInStock - 1 : 0; }
	void Station::display(std::ostream& os, bool full) const {
		os << std::right <<std::setfill('0') << std::setw(3) << stId << " | "
			<< std::setfill(' ') << std::setw(m_widthField) << std::left << itemName << "| "
			<< std::right << std::setfill('0') << std::setw(6) << serialNum << " | ";
		if (!full) {
			os << std::endl;
		}
		else {
			os << std::setfill(' ') << std::setw(4) << numInStock << " | "
				<< stDescription << std::endl;
		}
	}
}