cmake_minimum_required(VERSION 3.13)
if (DEFINED MCU)
	# Setting up the toolchain
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/cortex.cmake")
endif()
# Project information
project(Ams5915
	VERSION 2.0.0
	DESCRIPTION "AMS5915 sensor driver"
	LANGUAGES CXX
)
if (DEFINED MCU)
	# Grab the processor and set up definitions and compile options
	include(${CMAKE_SOURCE_DIR}/cmake/config_mcu.cmake)
	configMcu(${MCU})
	include(FetchContent)
	# Fetch core
	FetchContent_Declare(
		core
		GIT_REPOSITORY 	https://github.com/bolderflight/core.git
		GIT_TAG v2.0.4
	)
	FetchContent_MakeAvailable(core)
	# Add the library target
	add_library(ams5915
		include/ams5915/ams5915.h
	)
	# Link libraries
	target_link_libraries(ams5915
		PUBLIC
			core
	)
	# Setup include directories 
	target_include_directories(ams5915 PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
endif()

# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	if (DEFINED MCU)
		# Add the spi example target
		add_executable(ams5915_example examples/ams5915_example.cc)
		# Add the includes
		target_include_directories(ams5915_example PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>
		)
		# Link libraries to the example target
		target_link_libraries(ams5915_example
			PRIVATE 
				ams5915
		)
		# Add hex and upload targets
		include(${CMAKE_SOURCE_DIR}/cmake/flash_mcu.cmake)
		FlashMcu(ams5915_example ${MCU})
	endif()
endif()
