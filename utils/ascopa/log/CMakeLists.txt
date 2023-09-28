set (CMAKE_CXX_STANDARD 11)

add_library(Log STATIC
	log.cpp
	log.h
)

target_include_directories(ASCOPATests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    # need access to private includes for unit-testing RoutingTests
        $<TARGET_PROPERTY:ascopa,INCLUDE_DIRECTORIES>
)

add_test(NAME ASCOPATests
         COMMAND ASCOPATests)
