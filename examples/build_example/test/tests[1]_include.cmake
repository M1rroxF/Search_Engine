if(EXISTS "D:/forWork/projects/C++ - Standart/Current/Search Engine/examples/build_example/test/tests[1]_tests.cmake")
  include("D:/forWork/projects/C++ - Standart/Current/Search Engine/examples/build_example/test/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
