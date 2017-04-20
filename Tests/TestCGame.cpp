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
#include "CStorageItem.h"
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

class MockActor : public Knights::CActor {
public:
    MockActor( int, int ) : Knights::CActor( 1, 1){ mDefence = 0; mHP =1000; }
    MOCK_METHOD1( performAttack, void( std::shared_ptr<CActor> ) );
};

class TestCGame : public ::testing::Test {
protected:
    std::shared_ptr<MockFileLoader> mMockFileLoader;
    std::shared_ptr<MockRenderer> mMockRenderer;
    std::shared_ptr<Knights::CGameDelegate> mDelegate;
    std::shared_ptr<Knights::CGame> mGame;

    int countElements(char element, std::shared_ptr<Knights::CMap> map ) {
        int count = 0;

        for ( int y = 0; y < Knights::kMapSize; ++y ) {
            for ( int x = 0; x < Knights::kMapSize; ++x ) {
                if ( map->getMapAt( { x, y } ) == element ) {
                    ++count;
                }
            }
        }

        return count;
    }

    std::string getMap() {
        std::string toReturn;

        toReturn += "v4y0000000000000000000000000000T00000000\n";
        toReturn += "011110000000000000000000########000#0000\n";
        toReturn += "050000000000000000000000000000#0000#0#00\n";
        toReturn += "050000000000000000000000000000########00\n";
        toReturn += "000000000000000000000000000000#000000000\n";
        toReturn += "0000000000000000000000000#0000#0000#0000\n";
        toReturn += "0000000000000000000000000###########0000\n";
        toReturn += "000000000000000000000000000#000000000000\n";
        toReturn += "000000000000000000000000000#000000000000\n";
        toReturn += "000000000000000000000000000#000000000000\n";
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

    virtual void SetUp() {
        mMockFileLoader = std::make_shared<MockFileLoader>();
        mMockRenderer = std::make_shared<MockRenderer>();
        mDelegate = std::make_shared<Knights::CGameDelegate>();
        ON_CALL(*mMockFileLoader, loadFileFromPath(_)).WillByDefault(Return(getMap()));
        mGame = std::make_shared<Knights::CGame>( mMockFileLoader, mMockRenderer, mDelegate );

    }

    // virtual void TearDown() {}
};




TEST_F(TestCGame, GameWillRefreshUponValidMoveTest ) {

  std::string mockMapContents = getMap();

  ON_CALL(*mMockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
  ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kMovePlayerNorthCommand));
  EXPECT_CALL(*mMockFileLoader, loadFileFromPath(_));
  auto game = std::make_shared<Knights::CGame>( mMockFileLoader, mMockRenderer, mDelegate );
  EXPECT_CALL(*mMockRenderer, drawMap(_,_));
  EXPECT_CALL(*mMockRenderer, getInput());
  game->tick();
}

TEST_F(TestCGame, GameWillKeepPlayerStatusBetweenMapChanges ) {

	mGame->getMap()->getAvatar()->addHP( 50 );
	auto previousHP = mGame->getMap()->getAvatar()->getHP();
	mGame->proceedToNextLevel();
	ASSERT_EQ( previousHP, mGame->getMap()->getAvatar()->getHP() );
    ASSERT_TRUE( Knights::EDirection::kNorth == mGame->getMap()->getAvatar()->getDirection() );
}

TEST_F(TestCGame, GameWillAdvanceLevelUponEnteringExit ) {

    auto mockMapContents = getMap();
	mockMapContents[ 2 ] = '9';

	ON_CALL(*mMockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
	ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return('s'));
	auto game = std::make_shared<Knights::CGame>( mMockFileLoader, mMockRenderer, mDelegate );
    EXPECT_CALL(*mMockFileLoader, loadFileFromPath(_));
    game->tick();
}


TEST_F(TestCGame, GameWillInvalidateStoredPlayerForNextSession ) {
	auto avatar = mGame->getMap()->getAvatar();
	avatar->addHP( 50 );
	auto previousHP = avatar->getHP();
	mGame->proceedToNextLevel();
	avatar = mGame->getMap()->getAvatar();
	avatar->addHP(-avatar->getHP() * 2 );
	ASSERT_FALSE( avatar->isAlive() );
	mGame->tick();
	ASSERT_TRUE( mGame->getMap()->getAvatar()->isAlive() );
	ASSERT_NE( previousHP, mGame->getMap()->getAvatar()->getHP() );
}

TEST_F(TestCGame, AvatarInstancesBetweenLevelsAreNotTheSameInstance ) {
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

TEST_F(TestCGame, RestoredPlayerWillNotRestoreTransientStateFromBackup ) {
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

TEST_F(TestCGame, GameWillNotTryToLoadFileFromBinaryTest ) {

  auto mockFileLoader = std::make_shared<MockFileLoader>();
  auto renderer = std::make_shared<MockRenderer>();
  auto delegate = std::make_shared<Knights::CGameDelegate>();

  std::string mockMapContents = getMap();
  ON_CALL(*mockFileLoader, loadFileFromPath(_)).WillByDefault(Return(mockMapContents));
  EXPECT_CALL(*mockFileLoader, loadFileFromPath(_));
  std::make_shared<Knights::CGame>( mockFileLoader, renderer, delegate );
}


TEST_F(TestCGame, PlayersCarryingNothingCantDropItems ) {

    auto actor = mGame->getMap()->getAvatar();
    actor->turnRight();
    actor->turnRight();
    auto target = mGame->getMap()->getActorTargetPosition( actor );

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    mGame->tick();

    ASSERT_TRUE(actor->getSelectedItem() == nullptr );
    ASSERT_TRUE(mGame->getMap()->getItemAt(target) == nullptr );
}

TEST_F(TestCGame, GameWillPreventPlayersFromDroppingItemsOnInvalidPositions ) {

    auto actor = mGame->getMap()->getAvatar();

    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    auto currentItem = actor->getSelectedItem();
    actor->turnRight();
    actor->turnRight();
    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    mGame->tick();

    auto target = mGame->getMap()->getActorTargetPosition( actor );
    ASSERT_FALSE( mGame->getMap()->isValid(target));
    ASSERT_TRUE( actor->getSelectedItem() != nullptr );
    auto itemOnTheFloor = mGame->getMap()->getItemAt(target);
    ASSERT_TRUE(itemOnTheFloor == nullptr );
}


TEST_F(TestCGame, GameWillPreventPlayersFromPickingItemsOnInvalidPositions ) {

    auto actor = mGame->getMap()->getAvatar();

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();

    auto target = mGame->getMap()->getActorTargetPosition( actor );
    ASSERT_FALSE( mGame->getMap()->isValid(target));
    ASSERT_TRUE( actor->getSelectedItem() == nullptr );
    auto itemOnTheFloor = mGame->getMap()->getItemAt(target);
    ASSERT_TRUE(itemOnTheFloor == nullptr );
}

TEST_F(TestCGame, GameWillPreventPlayersFromDroppingItemsOnBlockingTiles ) {

    auto actor = mGame->getMap()->getAvatar();

    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    auto currentItem = actor->getSelectedItem();
    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    mGame->tick();

    auto target = mGame->getMap()->getActorTargetPosition( actor );
    ASSERT_EQ(currentItem->getView(), 'y' );
    auto mapElementView = mGame->getMap()->getElementAt(target);
    ASSERT_EQ(mapElementView, '1' );
    auto itemOnTheFloor = mGame->getMap()->getItemAt(target);
    ASSERT_TRUE(itemOnTheFloor == nullptr );
}

TEST_F(TestCGame, GameWillPreventPlayersFromDroppingItemsOnTopOfOtherItems ) {

    auto actor = mGame->getMap()->getAvatar();

    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    actor->turnRight();
    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kDropItemCommand));
    mGame->tick();

    ASSERT_TRUE( actor->getDirection() == Knights::EDirection::kWest);
    auto target = mGame->getMap()->getActorTargetPosition( actor );
    ASSERT_TRUE(actor->getSelectedItem() != nullptr );
    ASSERT_EQ(actor->getSelectedItem()->getView(), 'y' );
    auto mapElementView = mGame->getMap()->getElementAt(target);
    ASSERT_EQ(mapElementView, 'v' );
    auto itemOnTheFloor = mGame->getMap()->getItemAt(target);
    auto selectedItem = actor->getSelectedItem();
    ASSERT_TRUE(itemOnTheFloor != selectedItem );
}

TEST_F(TestCGame, HavingBothShieldAndCrossbowChargedWillProvideMoreDamage ) {

    auto actor = mGame->getMap()->getAvatar();
    auto mockEnemy = std::make_shared<MockActor>( 1, 1 );

    mGame->getMap()->addActorAt( mockEnemy, { Knights::kMapSize / 2, 0 } );

    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    actor->turnLeft();
    actor->turnLeft();
    mGame->tick();
    actor->turnLeft();
    actor->turnLeft();
    actor->suggestCurrentItem('y');

    auto shield = (Knights::CStorageItem*)actor->getItemWithSymbol( 'v' ).get();
    auto crossbow = (Knights::CStorageItem*)actor->getItemWithSymbol( 'y' ).get();

    shield->add( 100  );
    crossbow->add( 100 );

    auto crossbowAmmoBefore = crossbow->getAmount();
    auto shieldEnergyBefore = shield->getAmount();
    auto healthBefore = mockEnemy->getHP();

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kUseCurrentItemInInventoryCommand));
    mGame->tick();

    ASSERT_TRUE( actor->getDirection() == Knights::EDirection::kEast);
    ASSERT_EQ(actor->getSelectedItem()->getView(), 'y' );

    auto playerAttack = actor->getAttack();
    auto newHealth = mockEnemy->getHP();

    ASSERT_EQ( healthBefore, newHealth + ( playerAttack * 10) );
    ASSERT_TRUE( crossbowAmmoBefore > crossbow->getAmount());
    ASSERT_TRUE( shieldEnergyBefore > shield->getAmount());
}


TEST_F(TestCGame, HavingCrossbowChargedWillProvideRegularDamage ) {

    auto actor = mGame->getMap()->getAvatar();
    auto mockEnemy = std::make_shared<MockActor>( 1, 1 );

    mGame->getMap()->addActorAt( mockEnemy, { Knights::kMapSize / 2, 0 } );


    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    actor->turnLeft();
    actor->turnLeft();
    mGame->tick();
    actor->turnLeft();
    actor->turnLeft();
    actor->suggestCurrentItem('y');

    auto shield = (Knights::CStorageItem*)actor->getItemWithSymbol( 'v' ).get();
    auto crossbow = (Knights::CStorageItem*)actor->getItemWithSymbol( 'y' ).get();

    crossbow->add( 100 );
    shield->empty();

    auto crossbowAmmoBefore = crossbow->getAmount();
    auto shieldEnergyBefore = shield->getAmount();
    auto healthBefore = mockEnemy->getHP();

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kUseCurrentItemInInventoryCommand));
    mGame->tick();

    ASSERT_TRUE( actor->getDirection() == Knights::EDirection::kEast);
    ASSERT_EQ(actor->getSelectedItem()->getView(), 'y' );

    auto playerAttack = actor->getAttack();
    auto newHealth = mockEnemy->getHP();

    ASSERT_EQ( healthBefore, newHealth + ( playerAttack ) );
    ASSERT_TRUE( crossbowAmmoBefore > crossbow->getAmount());
    ASSERT_EQ( shieldEnergyBefore, shield->getAmount());
}

TEST_F(TestCGame, UsingTheShieldWillReplenishTheHealth ) {
    auto actor = mGame->getMap()->getAvatar();

    actor->turnLeft();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    actor->suggestCurrentItem('v');

    auto shield = (Knights::CStorageItem*)actor->getItemWithSymbol( 'v' ).get();
    shield->add( 100 );

    auto shieldEnergyBefore = shield->getAmount();
    auto healthBefore = actor->getHP();

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kUseCurrentItemInInventoryCommand));
    mGame->tick();

    ASSERT_TRUE( actor->getDirection() == Knights::EDirection::kWest);


    auto newHealth = actor->getHP();

    ASSERT_TRUE( healthBefore < newHealth );
    ASSERT_TRUE( shieldEnergyBefore > shield->getAmount());
}


TEST_F(TestCGame, ShootingTheGateNodeWillOpenAllGates ) {

    auto actor = mGame->getMap()->getAvatar();
    int gatesBefore = countElements('#', mGame->getMap());
    int passagesBefore = countElements('~', mGame->getMap());

    actor->turnRight();
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    actor->suggestCurrentItem('y');

    auto crossbow = (Knights::CStorageItem*)actor->getItemWithSymbol( 'y' ).get();

    crossbow->add( 100 );

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kUseCurrentItemInInventoryCommand));
    mGame->tick();
    mGame->tick();
    int passagesAfter = countElements('~', mGame->getMap());
    int gatesAfter = countElements('#', mGame->getMap());

    ASSERT_TRUE( actor->getDirection() == Knights::EDirection::kEast);
    ASSERT_EQ(actor->getSelectedItem()->getView(), 'y' );

    ASSERT_EQ( gatesBefore, 38 );
    ASSERT_EQ( passagesAfter, 38 );
    ASSERT_EQ( gatesBefore, passagesAfter );
    ASSERT_EQ( gatesAfter, 0 );
    ASSERT_EQ( passagesBefore, 0 );
}

TEST_F(TestCGame, EnsureMonstersWontKillEachOther ) {

    auto actors = mGame->getMap()->getActors();

    int cumulatedHealthBefore = 0;

    for (const auto& actor : actors ) {
        if ( actor->getView() == '@') {
            cumulatedHealthBefore += actor->getHP();
        }
    }

    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kEndTurnCommand));
    mGame->tick();
    mGame->tick();
    mGame->tick();

    int cumulatedHealthAfter = 0;

    for (const auto& actor : actors ) {
        if ( actor->getView() == '@') {
            cumulatedHealthAfter += actor->getHP();
        }
    }

    ASSERT_EQ( cumulatedHealthAfter, cumulatedHealthBefore);
}

TEST_F(TestCGame, EnsureTheProjectionTargetWillChangeBasedOnCharacterItems ) {
    auto actor = mGame->getMap()->getAvatar();
    int gatesBefore = countElements('#', mGame->getMap());
    int passagesBefore = countElements('~', mGame->getMap());

    actor->turnRight();
    auto targetBeforeCrossbow = mGame->getMap()->getTargetProjection( actor );
    ON_CALL(*mMockRenderer, getInput()).WillByDefault(Return(Knights::kPickItemCommand));
    mGame->tick();
    actor->suggestCurrentItem('y');
    auto targetWithCrossbow = mGame->getMap()->getTargetProjection( actor );
    actor->turnRight();
    actor->turnRight();
    mGame->tick();
    actor->suggestCurrentItem('t');
    auto targetWithSword  = mGame->getMap()->getTargetProjection( actor );

    ASSERT_EQ( targetBeforeCrossbow, Knights::Vec2i( 2, 0 ) );
    ASSERT_EQ(targetWithCrossbow, Knights::Vec2i( 31, 0 ) );
    ASSERT_EQ( targetWithSword, Knights::Vec2i( 0, 0 ) );

}
