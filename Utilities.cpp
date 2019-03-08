


#include <cstring>
#include <string>
#include "Utilities.h"


Utilities::Utilities() :field_width(1) {};

void Utilities::setFieldWidth(size_t width) {
	field_width = width;
}

//returns field_width
size_t Utilities::getFieldWidth() const {

	return field_width;
}

//extractToken
//
const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	//delimiter
	std::string token;
	int pos = 0;
	if (next_pos < str.length()) {
		pos = str.find(delimiter, next_pos);

		token = str.substr(next_pos, pos - next_pos);
		//reports an exception if there are two delimiters with no token between them
		if (pos == next_pos + 1 && (token.at(0) == delimiter)) {
			throw "There is no string token between them!";
		}

		more = true;
		//updates the current object's field_width data member if its current value 
		//is less than the size of the token extracted.

		if (token.length() > field_width) {
			field_width = token.length();
		}
		size_t len = token.length();
		next_pos += len;

		if (str.length() <= next_pos) more = false;
	}
	else
		more = false;
	return token;
}

char Utilities::delimiter = '|';

void Utilities::setDelimiter(const char delim) {
	delimiter = delim;
}

const char Utilities::getDelimiter() const {
	return delimiter;

}