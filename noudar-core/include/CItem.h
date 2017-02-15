//
// Created by monty on 12/02/17.
//

#ifndef NOUDAR_CORE_CITEM_H
#define NOUDAR_CORE_CITEM_H

namespace Knights {


	//hate this...
	class CMap;
	class CActor;

	using CItemAction = std::function< void(std::shared_ptr<CActor>, std::shared_ptr<CMap>)>;

	const CItemAction kItemDoNothingAction = [](std::shared_ptr<CActor>, std::shared_ptr<CMap>){};

	class CItem {
		std::string mName;
		char mView;
		CItemAction mItemAction;
	public:
		CItem(std::string aName, char aView, const CItemAction& itemAction );
		CItem(std::string aName, char aView );

		std::string to_string() const;

		void use(std::shared_ptr<CActor>, std::shared_ptr<CMap>);
		char getView() const;
	};

	std::ostream &operator<<(std::ostream &os, const CItem &action);

	std::string to_string(const CItem &action);


}


#endif //NOUDAR_CORE_CITEM_H
