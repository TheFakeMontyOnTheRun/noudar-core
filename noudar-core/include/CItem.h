//
// Created by monty on 12/02/17.
//

#ifndef NOUDAR_CORE_CITEM_H
#define NOUDAR_CORE_CITEM_H

namespace Knights {
	class CItem {
		std::string mName;
		char mView;
	public:
		CItem(std::string aName, char aView);

		std::string to_string() const;

		char getView() const;
	};

	std::ostream &operator<<(std::ostream &os, const CItem &action);

	std::string to_string(const CItem &action);


}


#endif //NOUDAR_CORE_CITEM_H
