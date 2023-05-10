#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const std::string& str) {
		if (!str.empty()) {
			size_t pos{ 0 }, itemsPos{ 0 };
			Utilities u{};
			bool more{ true };
			m_name = u.extractToken(str, pos, more);
			m_product = u.extractToken(str, pos, more);
			itemsPos = pos;
			// calculating the number of items
			while (more) {
				u.extractToken(str, pos, more);
				m_cntItem++;
			}
			more = true;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(u.extractToken(str, itemsPos, more));
			}
			m_widthField = (m_widthField > u.getFieldWidth()) ? m_widthField : u.getFieldWidth();
		}
		else {
			throw "Invalid parameter!";
		}
	}
	// --------------
	// copy semantics
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "Copying is disabled!";
	}
	// move semantics
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = std::move(src);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}
		return *this;
	}
	// --------------
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		bool isFilled{ true };
		for (size_t i = 0; i < m_cntItem && isFilled; i++) {
			if (!m_lstItem[i]->m_isFilled)
				isFilled = false;
		}
		return isFilled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isFilled{ true };
		for (size_t i = 0; i < m_cntItem && isFilled; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
				isFilled = false;
		}
		return isFilled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool isFilled{ false };
		for (size_t i = 0; i < m_cntItem && !isFilled; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					isFilled = true;
					os << "    Filled " << m_name << ", " << m_product 
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product 
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] "
				<< std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName 
				<< "   - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}