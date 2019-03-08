

#include "CustomerOrder.h"
#include<iostream>


CustomerOrder::CustomerOrder() {
	ItemCount = 0;
}

CustomerOrder::~CustomerOrder() {

	if (ItemCount != 0)
	{
		for (unsigned int i = 0; i < (ItemCount); i++) {
			delete ItemList[i];
			//ItemList[i] = nullptr;
		}
	}
	delete [] ItemList;

	//ItemList = nullptr;
}


//an overloaded constructor that takes a reference to a string containing a single record from the CustomerOrders.txt file.  
//It will use the Utilities object to extract the tokens and populate the CustomerOrder object.
//
CustomerOrder::CustomerOrder(std::string&record) {
	ItemCount = 0;
	int index = 0;
	size_t next_position = 0;
	Utilities temp;
	bool more = true;
	std::string strOfItems;
	while (more) {
		//name
		std::string tempStr = temp.extractToken(record, next_position, more);
		if (Name.empty())
			Name = tempStr;
		//Product
		else if (Product.empty())
			Product = tempStr;
		else {
			ItemCount++;
			strOfItems += tempStr + '|';
		}
		next_position++;
		//itemCount
	}
	next_position = 0;
	ItemList = new ItemInfo*[ItemCount];
	for (unsigned int i = 0; i < ItemCount; i++) {
		ItemList[i] = new ItemInfo(temp.extractToken(strOfItems, next_position, more));
		next_position++;
	}
}

//Object move functionality
//
CustomerOrder::CustomerOrder(CustomerOrder&&obj) {

	ItemList = nullptr;
	
	*this = std::move(obj);
}



//move assignment operator
//
CustomerOrder& CustomerOrder::operator=(CustomerOrder&&obj) {
	//checks for self assignment
	if (this != &obj) {
		/*
		if (ItemList != nullptr)
		{
			for (int i = 0; i < (ItemCount); i++)
			{
				ItemList[i] = nullptr;
				delete[] ItemList[i];
			}
			ItemList = nullptr;
			delete[] ItemList;
		}*/

		Name = obj.Name;
		Product = obj.Product;
		ItemCount = obj.ItemCount;
		field_width = obj.field_width;

		
		ItemList = new ItemInfo*[obj.ItemCount];
		
		for (unsigned int i = 0; i < (obj.ItemCount); i++) {
			ItemList[i] = obj.ItemList[i];
		}

		for (unsigned int i = 0; i < (obj.ItemCount); i++){
			obj.ItemList[i] = nullptr;
			//delete[] obj.ItemList[i];
		}
		//obj.ItemList = nullptr;
		//delete[] obj.ItemList;
			
		obj.Name = "";
		obj.Product = "";
		obj.ItemCount = 0;
		obj.field_width = 0;
	}
	return *this;
}



//– Loops through the Items of the CustomerOrder 
//Returns true if order completely filled, false otherwise
//
bool CustomerOrder::getOrderFillState() {
	bool result = false;

	for ( unsigned int i = 0; i < (ItemCount); i++) {
		if (ItemList[i]->FillState == true) {
			result = true;
		}
		else return false;
	}

	return result;
}

////Returns true if the given item has been filled
//returns the FillState of the specified itemName passed into the function 
bool CustomerOrder::getItemFillState(std::string itemName) {
	bool result = true;
	for (unsigned int i = 0; i < (ItemCount); i++)
		if (ItemList[i]->ItemName == itemName)
			if (ItemList[i]->FillState == false)
				result = false;

	return  result;

}
//Fills the  order item if the inventory on Item is available
//
void CustomerOrder::fillItem(Item&item_, std::ostream& os) {
	
	for (unsigned int i = 0; i < (ItemCount); i++) {
		if (ItemList[i]->ItemName == item_.getName() && !ItemList[i]->FillState){	//problems may occur here
			ItemList[i]->SerialNumber = item_.getSerialNumber();
				ItemList[i]->FillState = true;

			os << "FILLED " << Name << ", " << Product << " [" << ItemList[i]->ItemName << "]" << std::endl;
			break;
		}
	}
	 
}

//Displays the details of the CustomerOrder to the ostream object provided
//
void CustomerOrder::Display(std::ostream&os) {
	os << std::setw(field_width) << Name << std::endl;
	os << Product << std::endl;
	for (unsigned int i = 0; i < (ItemCount); i++) {
		
		os << "[" << ItemList[i]->SerialNumber << "]" << ItemList[i]->ItemName;
		
		if (ItemList[i]->FillState) {
			os << " Filled" << std::endl;
		}
	}
}
