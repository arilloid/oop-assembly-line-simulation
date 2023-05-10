#pragma once
#include <iostream>

namespace sdds {
	class Station {
		int stId{ 0 };
		std::string itemName{};
		std::string stDescription{};
		unsigned int serialNum{ 0 };
		unsigned int numInStock{ 0 };
		// class variables
		static size_t m_widthField;
		static int id_generator;
	public:
		Station();
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}






























