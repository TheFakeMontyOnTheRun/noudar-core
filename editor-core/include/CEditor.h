//
// Created by monty on 03/01/17.
//

#ifndef EDITOR_CLION_CEDITOR_H
#define EDITOR_CLION_CEDITOR_H

namespace Knights {
	class CEditor {
		std::shared_ptr<CMap> mMap;
		std::shared_ptr<IRenderer> mRenderer;
		std::shared_ptr<IFileLoaderDelegate> mFileLoaderDelegate;

	public:
		void tick();
		CEditor(std::shared_ptr<IFileLoaderDelegate> fileLoaderDelegate, std::shared_ptr <IRenderer> aRenderer);
		Vec2i getCursorPosition();
		~CEditor() = default;
		std::shared_ptr<CMap> getMap();
	};
}

#endif //EDITOR_CLION_CEDITOR_H
