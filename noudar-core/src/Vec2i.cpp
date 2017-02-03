#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Vec2i.h"

namespace Knights {
	std::ostream &operator<<(std::ostream &os, const EDirection &aDirection) {
		os << to_string(aDirection);

		return os;
	}

	std::string to_string(const EDirection &aDirection) {
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
}
