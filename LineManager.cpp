#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {
        std::string record{}, stName{}, nextStName{};
		std::ifstream file(filename);
        // checking if the file was properly opened
		if (!file)
			throw std::string("Unable to open the file!");
        // getting the records from the file
		while (std::getline(file, record)) {
            size_t pos{ 0 };
            Utilities u{};
            bool more{ true };
            // extracting the name of the current station
            stName = u.extractToken(record, pos, more);
            auto st = std::find_if(stations.begin(), stations.end(),
                [&](Workstation* station) { return station->getItemName() == stName; });
            if (st != stations.end()) 
                m_activeLine.push_back(*st);
            else 
                throw std::string("Station [") + stName + "] not found.";
            // extarcting the name of the next station if there is one
            if (more) {
                nextStName = u.extractToken(record, pos, more);
                auto nextSt = std::find_if(stations.begin(), stations.end(),
                    [&](Workstation* station) { return station->getItemName() == nextStName; });
                if (nextSt != stations.end())
                    (*st)->setNextStation(*nextSt);
                else
                    throw std::string("Station [") + nextStName + "] not found.";
            }
		}
        // finding and setting the first station in the line
        auto firstSt = std::find_if(stations.begin(), stations.end(),
            [&](Workstation* curSt) { return std::none_of(stations.begin(), stations.end(), [&](Workstation* st) {
                return curSt == st->getNextStation();
                });
            });
        if (firstSt != stations.end())
            m_firstStation = *firstSt;
        else
            throw std::string("Unable to determine the first station in the line.");
        // setting the customer order count
        m_cntCustomerOrder = g_pending.size();
    }
    void LineManager::reorderStations() {
        std::vector<Workstation*> orderedLine;
        orderedLine.push_back(m_firstStation);
        for (auto station = m_firstStation->getNextStation(); station != nullptr; station = station->getNextStation())
            orderedLine.push_back(station);
        m_activeLine = orderedLine;
    }
    bool LineManager::run(std::ostream& os) {
        static size_t count{0};
        os << "Line Manager Iteration: " << ++count << std::endl;
        // putting the first order from the g_pending to the m_firstStation and removing it from the line
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        // filling every element of the active line
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& station) {
                station->fill(os);
            });
        // attempting to move every element of the active line
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& station) {
            station->attemptToMoveOrder();
            });
        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }
    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& station) {
            station->display(os);
            });
    }
}