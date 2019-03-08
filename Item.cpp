

#include <sstream>
#include "Item.h"
#include "Utilities.h"
#include <cstring>
#include<string>


unsigned int Item::field_width = 6;
//constructor overload
//
Item::Item(std::string& record) {
	int index = 0;
	size_t next_position = 0;
	bool more = true;
	Utilities temp;// = new Utilities;
	temp.setDelimiter('|');

	//while (delim_pos > 0) {
	while (more) {
		//<name of item>
		name = temp.extractToken(record, next_position, more);

		//index = next_position; //
		next_position++;

		//<starting serial number>
		//std::string str = temp.extractToken(record, next_position, more);
		//serialNumber = std::stoi(str, next_position, 10);
		std::stringstream iss1(temp.extractToken(record, next_position, more));
		iss1 >> serialNumber;

		next_position++;

		//unsigned int Quantity;

		std::stringstream iss2(temp.extractToken(record, next_position, more));
		iss2 >> Quantity;
		//Quantity = std::stoi(temp.extractToken(record, next_position, more));

		next_position++;

		//std::string description;
		description = temp.extractToken(record, next_position, more);


		//If Utilities field_width is greater, 
		//reset the Item field_width to the Utilities field_width.

		if (temp.Utilities::getFieldWidth() > field_width) {

			field_width = temp.Utilities::getFieldWidth();
		}
		//field_width = temp->getFieldWidth;

	}

}

//Returns a reference to the serial number
const unsigned int Item::getSerialNumber() {

	return serialNumber++;
}

//Returns a reference to the remaining quantity
const unsigned int Item::getQuantity() {
	return Quantity;
}

const std::string& Item::getName() const {
	return name;
}
//Removes 1 from the quantity
void Item::updateQuantity() {
	if (Quantity > 0) {
		Quantity--;
		//Quantity -= 1;
	}
}

void Item::display(std::ostream& os, bool full) const {

	os << std::left << std::setw(13) << name << "[" << serialNumber << "]";

	//If full status is requested
	//include the quantity and description of the Item object
	if (full) {
		os << "Quantity " << Quantity << " " << "Description: " << description;

	}
	os << std::endl;
}

/*
The output for this milestone should look as follows:
CPU          [123456] Quantity 5   Description: Central Processing Unit
Memory       [654321] Quantity 10  Description: Basic Flash Memory
GPU          [456789] Quantity 2   Description: General Porcessing Unit
SSD          [987654] Quantity 5   Description: Solid State Drive
Power Supply [147852] Quantity 20  Description: Basic AC Power Supply


*/