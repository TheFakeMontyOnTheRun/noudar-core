//
// Created by monty on 12/02/17.
//

#ifndef NOUDAR_CORE_CITEM_H
#define NOUDAR_CORE_CITEM_H

namespace Knights {
	class CItem {
		std::string mName;
	public:
		CItem(std::string aName);

		std::string to_string() const;
	};

	std::ostream &operator<<(std::ostream &os, const CItem &action);

	std::string to_string(const CItem &action);
}


#endif //NOUDAR_CORE_CITEM_H
