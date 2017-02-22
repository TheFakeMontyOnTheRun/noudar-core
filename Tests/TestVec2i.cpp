//
// Created by monty on 16/02/17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Vec2i.h"

using testing::Eq;

TEST( Vec2iTests, equalityForEqualMembers ) {

	auto N = Knights::Vec2i{ 0, -1 };
	auto offset = Knights::mapOffsetForDirection( Knights::EDirection::kNorth );
	ASSERT_EQ( N.x, offset.x );
	ASSERT_EQ( N.y, offset.y );
}