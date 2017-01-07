//
// Created by monty on 04/01/17.
//

#ifndef NOUDAR_CORE_CTEAM_H
#define NOUDAR_CORE_CTEAM_H

namespace Knights {
	class CTeam {
		std::string mName;
	public:
		CTeam(std::string aName);

		std::string getName();
	};
}

//std::ostream& operator<<(std::ostream& os, const ETeam& aTeam) {
//	os << to_string(aTeam);
//
//	return os;
//}
//
//std::string to_string( const ETeam& aTeam ) {
//	switch (aTeam) {
//		case ETeam::kHeroes:
//			return "Heroes";
//		case ETeam::kVillains:
//			return "Villains";
//	}
//}

#endif //NOUDAR_CORE_CTEAM_H
