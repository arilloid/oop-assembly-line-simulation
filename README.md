# Project Overview

The assembly line simulation is written in `C++` following the `Object-Oriented` programming principles.

![Assembly Line](assemblyline.jpg)

- The assembly line consists of a set of workstations.
- Each workstation holds a set of stock items specific to the station.
- A line manager moves customer orders along the line, filling the orders at each station as requested.
- Each customer order consists of a list of items that need to be filled.
- Each station processes a queue of orders by filling the next order in the queue if it requests the station's item and the item is in stock.
- The line manager keeps moving customer orders from station to station until all orders have been processed.
- A station that has used all the items in stock cannot fill any more orders.
- At the end of the line, orders are either completed or incomplete due to a lack of inventory at one or more stations.
- The simulator lists the completed orders and the incomplete orders once the line manager has finished processing all orders.



# Modules

-	The tester module and input files.

-	The `Utilities` module supports the parsing of input files, which contain information used to setup and configure the assembly line.

- The `Station` module manages information about a station on the assembly line, which holds a specific item and fills customer orders.

- The `CustomerOrder` module contains all the functionality for processing customer orders as they move from `Station` to `Station` along the assembly line. The `Station` where a given order currently rests fills a request for one item of that station, if there is any such request.

-	The `LineManager` module first configures the assembly line and then moves `CustomerOrders` along it (from start to finish). The `LineManager` object configures the `Workstation` objects identified by the user, and moves orders along the line one step at a time. A `Workstation` is a `Station` that the `LineManager` has activated on the user's request. At each step, every `Workstation` fills one item in a `Customer Order`, if possible. The manager moves orders from station to station. Once an order has reached the end of the line, it is either complete or incomplete. An order is incomplete if one or more stations had an insufficient number of items in stock to cover that order's requests.

-	The `Workstation` class defines the structure of an active station on the assembly line and contains all the functionality for filling customer orders with station items. Each `Workstation` is-a-kind-of `Station`. A `Workstation` object manages order processing for a single Item on the assembly line. Since a `Workstation` object represents a single location on the assembly line for filling customer orders with items, the object cannot be copied or moved. Make sure that this capability is deleted in your definition of the `Workstation` class.



