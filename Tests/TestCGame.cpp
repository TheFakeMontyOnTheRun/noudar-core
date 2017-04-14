#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <functional>
#include "Vec2i.h"
#include "CTeam.h"
#include "IMapElement.h"
#include "CItem.h"
#include "CActor.h"
#include "CCharacterArchetype.h"
#include "IFileLoaderDelegate.h"
#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CGame.h"


using ::testing::Return;
using ::testing::_;

class MockRenderer : public Knights::IRenderer {
public:

  MOCK_METHOD2(drawMap, void( Knights::CMap &map, std::shared_ptr<Knights::CActor> current ) );
  MOCK_METHOD0(getInput, char());
};

class MockFileLoader : public Knights::IFileLoaderDelegate {
public:

  MOCK_METHOD1( loadFileFromPath, std::string( const std::string& path ) );
  MOCK_METHOD1( loadBinaryFileFromPath, std::vector<char>( const std::string& path ) );
  MOCK_METHOD0( getFilePathPrefix, std::string());
};

std::string getMap() {
  std::string toReturn;

    toReturn += "t4y0000000000000000000000000000000000000\n";
    toReturn += "0100000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000\n";
    toReturn += "0000000000000000000000000000000000000000";

  return toReturn;
}

TEST(TestCGame, GameWillRefreshUponValidMoveTest ) {
  
  auto mockFileLoader = std::make_shared<MockFileLoader>();
  auto renderer = std::make_shared<MockRenderer>(); 
  auto delegate = std::make_shared<Knights::CGameDelegate>();

  std::string mockMapContents = getMap();

  ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
  ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kMovePlayerNorthCommand));
  EXPECT_CALL(*mockFileLoader, loadFileFromPath(_));
  auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
  EXPECT_CALL(*renderer, drawMap(_,_));
  EXPECT_CALL(*renderer, getInput());
  game->tick();
}

TEST(TestCGame, GameWillKeepPlayerStatusBetweenMapChanges ) {
	auto mockFileLoader = std::make_shared<MockFileLoader>();
	auto renderer = std::make_shared<MockRenderer>();
	auto delegate = std::make_shared<Knights::CGameDelegate>();
	ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(getMap()));
	auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );

	game->getMap()->getAvatar()->addHP( 50 );
	auto previousHP = game->getMap()->getAvatar()->getHP();
	game->proceedToNextLevel();
	ASSERT_EQ( previousHP, game->getMap()->getAvatar()->getHP() );
    ASSERT_TRUE( Knights::EDirection::kNorth == game->getMap()->getAvatar()->getDirection() );
}

TEST(TestCGame, GameWillAdvanceLevelUponEnteringExit ) {
	auto mockFileLoader = std::make_shared<MockFileLoader>();
	auto renderer = std::make_shared<MockRenderer>();
	auto delegate = std::make_shared<Knights::CGameDelegate>();

	auto mockMapContents = getMap();
	mockMapContents[ 2 ] = '9';

	ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
	ON_CALL(*renderer, getInput()).WillByDefault(Return('s'));
	auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
    EXPECT_CALL(*mockFileLoader, loadFileFromPath(_));
    game->tick();
}


TEST(TestCGame, GameWillInvalidateStoredPlayerForNextSession ) {
	auto mockFileLoader = std::make_shared<MockFileLoader>();
	auto renderer = std::make_shared<MockRenderer>();
	auto delegate = std::make_shared<Knights::CGameDelegate>();
	ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(getMap()));
	auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
	auto avatar = game->getMap()->getAvatar();
	avatar->addHP( 50 );
	auto previousHP = avatar->getHP();
	game->proceedToNextLevel();
	avatar = game->getMap()->getAvatar();
	avatar->addHP(-avatar->getHP() * 2 );
	ASSERT_FALSE( avatar->isAlive() );
	game->tick();
	ASSERT_TRUE( game->getMap()->getAvatar()->isAlive() );
	ASSERT_NE( previousHP, game->getMap()->getAvatar()->getHP() );
}

TEST(TestCGame, AvatarInstancesBetweenLevelsAreNotTheSameInstance ) {
	auto mockFileLoader = std::make_shared<MockFileLoader>();
	auto renderer = std::make_shared<MockRenderer>();
	auto delegate = std::make_shared<Knights::CGameDelegate>();
	ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(getMap()));
	auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
	auto avatar = game->getMap()->getAvatar();
	ASSERT_EQ( game->getMap()->getAvatar(), avatar );
	game->proceedToNextLevel();
	ASSERT_NE( game->getMap()->getAvatar(), avatar );
}

TEST(TestCGame, RestoredPlayerWillNotRestoreTransientStateFromBackup ) {
	auto mockFileLoader = std::make_shared<MockFileLoader>();
	auto renderer = std::make_shared<MockRenderer>();
	auto delegate = std::make_shared<Knights::CGameDelegate>();
	ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(getMap()));
	auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
	game->getMap()->getAvatar()->turnLeft();
	auto direction = game->getMap()->getAvatar()->getDirection();
	game->proceedToNextLevel();
	game->tick();
	ASSERT_NE( direction, game->getMap()->getAvatar()->getDirection() );
}

TEST(TestCGame, GameWillNotTryToLoadFileFromBinaryTest ) {
  
  auto mockFileLoader = std::make_shared<MockFileLoader>();
  auto renderer = std::make_shared<MockRenderer>(); 
  auto delegate = std::make_shared<Knights::CGameDelegate>();

  std::string mockMapContents = getMap();
  ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
  EXPECT_CALL(*mockFileLoader, loadFileFromPath(_));
  std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
}


TEST(TestCGame, PlayersCarryingNothingCantDropItems ) {
    auto mockFileLoader = std::make_shared<MockFileLoader>();
    auto renderer = std::make_shared<MockRenderer>();
    auto delegate = std::make_shared<Knights::CGameDelegate>();

    std::string mockMapContents = getMap();
    ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
    auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
    auto actor = game->getMap()->getAvatar();
    actor->turnRight();
    actor->turnRight();
    auto target = game->getMap()->getActorTargetPosition( actor );

    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    game->tick();

    ASSERT_TRUE(actor->getSelectedItem() == nullptr );
    ASSERT_TRUE(game->getMap()->getItemAt(target) == nullptr );
}

TEST(TestCGame, GameWillPreventPlayersFromDroppingItemsOnInvalidPositions ) {

    auto mockFileLoader = std::make_shared<MockFileLoader>();
    auto renderer = std::make_shared<MockRenderer>();
    auto delegate = std::make_shared<Knights::CGameDelegate>();
    std::string mockMapContents = getMap();
    ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
    auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
    auto actor = game->getMap()->getAvatar();

    actor->turnRight();
    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    game->tick();
    auto currentItem = actor->getSelectedItem();
    actor->turnRight();
    actor->turnRight();
    actor->turnRight();
    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    game->tick();

    auto target = game->getMap()->getActorTargetPosition( actor );
    ASSERT_FALSE( game->getMap()->isValid(target));
    ASSERT_TRUE( actor->getSelectedItem() != nullptr );
    auto itemOnTheFloor = game->getMap()->getItemAt(target);
    ASSERT_TRUE(itemOnTheFloor == nullptr );
}


TEST(TestCGame, GameWillPreventPlayersFromPickingItemsOnInvalidPositions ) {

    auto mockFileLoader = std::make_shared<MockFileLoader>();
    auto renderer = std::make_shared<MockRenderer>();
    auto delegate = std::make_shared<Knights::CGameDelegate>();
    std::string mockMapContents = getMap();
    ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
    auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
    auto actor = game->getMap()->getAvatar();

    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    game->tick();

    auto target = game->getMap()->getActorTargetPosition( actor );
    ASSERT_FALSE( game->getMap()->isValid(target));
    ASSERT_TRUE( actor->getSelectedItem() == nullptr );
    auto itemOnTheFloor = game->getMap()->getItemAt(target);
    ASSERT_TRUE(itemOnTheFloor == nullptr );
}

TEST(TestCGame, GameWillPreventPlayersFromDroppingItemsOnBlockingTiles ) {

    auto mockFileLoader = std::make_shared<MockFileLoader>();
    auto renderer = std::make_shared<MockRenderer>();
    auto delegate = std::make_shared<Knights::CGameDelegate>();
    std::string mockMapContents = getMap();
    ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
    auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
    auto actor = game->getMap()->getAvatar();

    actor->turnRight();
    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    game->tick();
    auto currentItem = actor->getSelectedItem();
    actor->turnRight();
    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    game->tick();

    auto target = game->getMap()->getActorTargetPosition( actor );
    ASSERT_EQ(currentItem->getView(), 'y' );
    auto mapElementView = game->getMap()->getElementAt(target);
    ASSERT_EQ(mapElementView, '1' );
    auto itemOnTheFloor = game->getMap()->getItemAt(target);
    ASSERT_TRUE(itemOnTheFloor == nullptr );
}

TEST(TestCGame, GameWillPreventPlayersFromDroppingItemsOnTopOfOtherItems ) {

    auto mockFileLoader = std::make_shared<MockFileLoader>();
    auto renderer = std::make_shared<MockRenderer>();
    auto delegate = std::make_shared<Knights::CGameDelegate>();
    std::string mockMapContents = getMap();
    ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
    auto game = std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
    auto actor = game->getMap()->getAvatar();

    actor->turnRight();
    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    game->tick();
    actor->turnRight();
    actor->turnRight();
    ON_CALL(*renderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    game->tick();

    ASSERT_TRUE( actor->getDirection() == Knights::EDirection::kWest);
    auto target = game->getMap()->getActorTargetPosition( actor );
    ASSERT_TRUE(actor->getSelectedItem() != nullptr );
    ASSERT_EQ(actor->getSelectedItem()->getView(), 'y' );
    auto mapElementView = game->getMap()->getElementAt(target);
    ASSERT_EQ(mapElementView, 't' );
    auto itemOnTheFloor = game->getMap()->getItemAt(target);
    auto selectedItem = actor->getSelectedItem();
    ASSERT_TRUE(itemOnTheFloor != selectedItem );
}



