set (CMAKE_CXX_STANDARD 11)

add_executable(ASCOPATests
    main.cpp
    ascopaunittests.h
    ascopaunittests.cpp
)

target_link_libraries(ASCOPATests
    ascopa
    Log
    UnitTest
)

target_include_directories(ASCOPATests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../log
    # need access to private includes for unit-testing RoutingTests
        $<TARGET_PROPERTY:ascopa,INCLUDE_DIRECTORIES>
)

add_test(NAME ASCOPATests
         COMMAND ASCOPATests)
