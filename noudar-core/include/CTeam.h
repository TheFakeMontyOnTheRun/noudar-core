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

		std::string to_string() const;
	};

#ifdef USE_IOSTREAM
	std::ostream& operator<<(std::ostream& os, const CTeam& aTeam);
#endif
}

#endif //NOUDAR_CORE_CTEAM_H
