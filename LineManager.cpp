
****************************************************************************/

#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"


//class LineManager
//{
//	std::vector<Task*> AssemblyLine;
//	std::deque<CustomerOrder> ToBeFilled;		//Queue of Customer Orders to be filled
//	std::deque<CustomerOrder> Completed;		//Queue of Customer Orders completed
//	unsigned int CustomerOrder_Count;			//The number of customer orders the process started with
//
//
LineManager::LineManager(std::string& fName, std::vector<Task*>& task, std::vector<CustomerOrder>& custorder) {
	//open 
	std::fstream f(fName);

	if (f.is_open()) { //use member function
		CustomerOrder_Count = custorder.size();
		Utilities util; //temp
		util.setDelimiter('|');
		std::string str;
		bool more;
		while (std::getline(f, str)) {
			size_t index = 0;
			std::string token = util.extractToken(str, index, more);
			if (more) {
				index++;
				for (size_t i = 0; i < task.size(); i++) {
					if (token == task[i]->getName()) {
						token = util.extractToken(str, index, more);
						for (size_t j = 0; j < task.size(); j++) {
							if (token == task[j]->getName()) { // 
								task[i]->setNextTask(*task[j]);
								AssemblyLine.push_back(task[i]);
							}
						}

					}
				}
			}
			else {
				for (size_t i = 0; i < task.size(); i++)
					if (token == task[i]->getName())
						AssemblyLine.push_back(task[i]);
			}
		}

		for (size_t i = 0; i < AssemblyLine.size(); i++)
			//Validate all the Task objects have been linked correctly
			AssemblyLine[i]->Validate(std::cout); //
			//AssemblyLine[i]->Validate(os);


		//•	Move all the CustomerOrder objects onto the front of the ToBeFilled queue
		//for (auto i : custorder)
		for (auto &i : custorder)
		{
			ToBeFilled.push_front(std::move(i));
		}

	}
}


	/*for_each(AssemblyLine.begin(), AssemblyLine.end(), [&](Task* t)
	{
		if (index < AssemblyLine.size())
		{
			tptr = AssemblyLine.at(index);
			t->setNextTask(&tptr);
		}
	});*/



	//Processes each assembly line task and moves the CustomerOrders through the line
	//Returning true if all items have been completed

	bool LineManager::Run(std::ostream & os){
		//bool result = false;
		if (!ToBeFilled.empty()){
			*AssemblyLine[0] += std::move(ToBeFilled.back());
			ToBeFilled.pop_back();
		}
			
			for (auto &assembly : AssemblyLine){
				assembly->RunProcess(os);
			}

			for (auto &currentAssembly : AssemblyLine)
			{
				currentAssembly->MoveTask();
			}
			CustomerOrder cOrder;
			AssemblyLine.back()->getCompleted(cOrder);
			if (cOrder.getOrderFillState()) {
				Completed.push_back(std::move(cOrder));
			}
			else {
				*AssemblyLine.back() += std::move(cOrder);
			}

			if (Completed.size() == CustomerOrder_Count) {
				//
				for (auto&order : Completed) {
					order.Display(os);
				}
				return true;
			}
			
		
		return false;
		//return result;
	}

