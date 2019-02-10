//
// Created by monty on 04/01/17.
//
#include <string>
#include <memory>
#include "CTeam.h"

namespace Knights {
	CTeam::CTeam(std::string aName) : mName(aName) {
	}

	std::string CTeam::to_string() const {
		return mName;
	}
}
