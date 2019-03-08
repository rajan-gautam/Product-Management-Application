

#include <algorithm>
#include "Task.h"


//
//class Task : public Item
//{
//	std::deque<CustomerOrder> Orders;				//Current orders at this station
//
//	Task* pNextTask;								//Reference to the next task

//Constructor
Task::Task(std::string& str) : Item(str) {

	//set pNextTask to safe state
	pNextTask = nullptr;

}

//This function fills the last order on the order queue
void Task::RunProcess(std::ostream& os) {

	if (!Orders.empty()) //If there are CustomerOrders in the queue,
	{
		if (Orders.back().getOrderFillState() == false) //it will verify the fill status of the last CustomerOrder 
		{
			Orders.back().fillItem((*this), os); //void CustomerOrder::fillItem(Item&item_, std::ostream& os) 
		}
	}

}

//moves the last CustomerOrder in the queue to the next task on the assembly line
//if the orders fill state for the current Item is true.  
//Otherwise, the CustomerOrder should remain in the queue for the next processing cycle.   
//If the queue is empty, return false.
//
bool Task::MoveTask() 
{
	
	if (!Orders.empty())
	{
		//if the orders fill state for the current Item is true.  
		if (Orders.back().getItemFillState(this->getName()) == true) {
			if (pNextTask) {
				*pNextTask += std::move(Orders.back());
				Orders.pop_back();
				return true;
			}
		}
	}
	return false;
	
}
//Sets up the pointer to the next task if the tasks names line up
//stores the provided Task objects reference into the pNextTask pointer
//	
void Task::setNextTask(Task& task) {

	//pNextTask = new Task(&obj.getName());
	pNextTask = &task;
	
}

//
bool Task::getCompleted(CustomerOrder & src) {
	bool valid = false;
	if (!Orders.empty()) { //if CustomerOrder queue is not empty

		src = std::move(Orders.back()); //Removes the last CustomerOrder from the queue, places it in src
		Orders.pop_back();
		//mydeque.back()
		valid = true;
	}
	else {
		valid = false; //If the CustomerOrder queue is empty, return false.
	}
	return valid;
}

//writes the name of the Item this Task is responsible for to os.   
//If pNextTask exists, writes the name of the next task on the assembly line.

void Task::Validate(std::ostream& os) {
	if (pNextTask != nullptr) { //pNextTask exists,

		os << getName() << " >> " << pNextTask->getName();
		os << std::endl;
	}
}

//Move a CustomerOrder into the orders queue
//Moves the newOrder onto the front of the CustomerOrder queue.
//
Task& Task::operator+=(CustomerOrder&& newOrder) {
	
	Orders.push_front(std::move(newOrder)); ////Moves the newOrder onto the front of the CustomerOrder queue.

	return *this;

}