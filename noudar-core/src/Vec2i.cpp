#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>

#include "Vec2i.h"

namespace Knights {
	std::ostream &operator<<(std::ostream &os, const EDirection &aDirection) {
		os << to_string(aDirection);

		return os;
	}

	std::string to_string(const EDirection &aDirection) {;
		switch (aDirection) {
			case EDirection::kNorth:
				return "North";
			case EDirection::kWest:
				return "West";
			case EDirection::kSouth:
				return "South";
			case EDirection::kEast:
				return "East";
		}
	}

	std::ostream &operator<<(std::ostream &os, const Vec2i &aVec) {
		os << to_string(aVec);

		return os;
	}

	std::string to_string(const Vec2i &aVec) {
		std::stringstream ss;
		ss << aVec.x << ", " << aVec.y;
		return ss.str();
	}


	Vec2i mapOffsetForDirerction( EDirection aDirection ) {
		switch (aDirection) {
			case EDirection::kNorth:
				return { 0 , -1 };
			case EDirection::kWest:
				return { -1, 0 };
			case EDirection::kSouth:
				return { 0, 1 };
			case EDirection::kEast:
				return { 1, 0 };
		}

		return { 0, 0 };
	}

	EDirection wrapDirection(EDirection direction, int offset) {
		int index = static_cast<int>(direction) + offset;

		while (index < 0) {
			index += 4;
		}

		while (index >= 4) {
			index -= 4;
		}

		return static_cast<EDirection>( index );
	}


	EDirection leftOf(Knights::EDirection d) {
		switch (d) {
			case Knights::EDirection::kNorth:
				return Knights::EDirection::kWest;
			case Knights::EDirection::kSouth:
				return Knights::EDirection::kEast;
			case Knights::EDirection::kEast:
				return Knights::EDirection::kNorth;
			case Knights::EDirection::kWest:
				return Knights::EDirection::kSouth;
		}
	}

	EDirection rightOf(Knights::EDirection d) {
		switch (d) {
			case Knights::EDirection::kNorth:
				return Knights::EDirection::kEast;
			case Knights::EDirection::kSouth:
				return Knights::EDirection::kWest;
			case Knights::EDirection::kEast:
				return Knights::EDirection::kSouth;
			case Knights::EDirection::kWest:
				return Knights::EDirection::kNorth;
		}
	}

}
