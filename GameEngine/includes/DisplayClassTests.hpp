#ifndef _TESTING // Should be defineds by Solution options.... tricks intellisense
#include "catch.hpp" 
#endif

#ifdef RUN_TESTS

#include <chrono>
#include <thread>
#include "..\Display\Display.h"

using namespace GameEngine::DisplayM;

TEST_CASE("Test Display class")
{
	REQUIRE_NOTHROW( display.init() );
	REQUIRE_NOTHROW( display.exists() == true);

	SECTION("Display not visible, should return false when checked.")
	{
		REQUIRE( display.shown() == false);
	}

	SECTION("Show display, should now report shown.")
	{
		display.showDisplay();
		REQUIRE( display.shown() == true);
	}
	SECTION("Default size is 1280 by 720.")
	{
		display.showDisplay();
		CHECK( display.shown() == true );
		CHECK( display.width() == 1280 );
		CHECK( display.height() == 720 );
	}
	SECTION("Size should report correctly")
	{
		int width, height;
		glfwGetWindowSize(display.window(), &width, &height);
		CHECK(display.width() == width);
		CHECK(display.height() == height);
	}

	//SECTION("Display resizes properly")
	//{
	//	display.showDisplay();
	//	CHECK(display.shown() == true);
	//		
	//	display.resize(640, 480);
	//	std::this_thread::sleep_for(std::chrono::seconds(1));
	//	CHECK(display.width() == 640);
	//	CHECK(display.height() == 480);
	//}
	REQUIRE_NOTHROW( display.closeDisplay() );
}

#endif