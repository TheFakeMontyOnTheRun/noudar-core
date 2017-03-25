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
	protected:
		std::string mName;
		char mView;
        bool mConsumable = false;

		CItemAction mItemAction = kItemDoNothingAction;
        CItemAction mItemPickAction = kItemDoNothingAction;
        CItemAction mItemDropAction = kItemDoNothingAction;
	public:
        CItem(std::string aName, char aView, bool aConsumable, const CItemAction& itemUseAction );
		CItem(std::string aName, char aView, bool aConsumable, const CItemAction& itemUseAction, const CItemAction& itemPickAction, const CItemAction& itemDropAction );
		CItem(std::string aName, char aView );

        std::string to_string() const;

		void use(std::shared_ptr<CActor>, std::shared_ptr<CMap>);
		char getView() const;
		bool isConsumable() const;
	};

	std::ostream &operator<<(std::ostream &os, const CItem &action);

	std::string to_string(const CItem &action);


}


#endif //NOUDAR_CORE_CITEM_H
