//
// Created by monty on 12/02/17.
//
#include <iostream>
#include <string>
#include "CItem.h"

#include <sstream>

Knights::CItem::CItem(std::string aName, char aView ) : mName(aName), mView( aView ) {
}

std::string Knights::CItem::to_string() const {
	return mName;
}

char Knights::CItem::getView() const {
	return mView;
}

std::ostream &::Knights::operator<<(std::ostream &os, const Knights::CItem &action) {

	os << action.to_string();

	return os;
}

std::string Knights::to_string(const Knights::CItem &action) {
	return action.to_string();
}