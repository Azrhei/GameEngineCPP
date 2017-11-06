#pragma once

#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "..\Utility\common.hpp"

int main(int argc, char* argv[]) {
	// global setup...
	glfwInit();

	glewExperimental = GL_TRUE;
	glewInit();

	int result = Catch::Session().run(argc, argv);

	// global clean-up...
	glfwTerminate();
	std::cin.get();
	return result;
}
#endif /* UNIT_TESTS_H */
