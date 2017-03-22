//
// Created by monty on 22-03-2017.
//
#include <string>
#include <functional>
#include <memory>
#include <sstream>
#include "CItem.h"
#include "CStorageItem.h"

std::string formatName( const std::string& name, int amount ) {
    std::stringstream ss;

    ss << name;
    ss << "(";
    ss << amount;
    ss << ")";

    return ss.str();
}

Knights::CStorageItem::CStorageItem(const std::string &aName, char aView, bool aConsumable,
                                    const Knights::CItemAction &itemAction, int initialAmount )
        : CItem( formatName( aName, initialAmount ), aView, aConsumable, itemAction), mAmount( initialAmount ), mOriginalName(aName) {
}

void Knights::CStorageItem::empty() {
    mAmount = 0;
}

int Knights::CStorageItem::getAmount() {
    return mAmount;
}

void Knights::CStorageItem::add(int amount) {
    mAmount = std::max( 0, mAmount + amount );
    mName = formatName( mOriginalName, mAmount );
}
