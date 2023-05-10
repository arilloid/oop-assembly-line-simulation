#include "Workstation.h"
#include "Station.h"

namespace sdds {
    // global variables
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;
    // publc member function of the workstation class
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }
    bool Workstation::attemptToMoveOrder() {
        bool moved{ false };
        if (!m_orders.empty() && (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)) {
            if (m_pNextStation) {
                *m_pNextStation += std::move(m_orders.front());
            }
            else {
                m_orders.front().isOrderFilled() ? g_completed.push_back(std::move(m_orders.front())) :
                    g_incomplete.push_back(std::move(m_orders.front()));
            }
            m_orders.pop_front();
            moved = true;
        }
        return moved;
    }
    void Workstation::setNextStation(Workstation* station) { m_pNextStation = station; }
    Workstation* Workstation::getNextStation() const { return m_pNextStation; }
    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        m_pNextStation ? os << m_pNextStation->getItemName() : os << "End of Line";
        os << std::endl;
    }
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}   