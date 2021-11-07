include(FetchContent)

FetchContent_Declare(
  expected_fc
  GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
  GIT_TAG aa59067ec932d3861b84113249bf88749150077d # v0.5.0
  SOURCE_DIR ${THIRD_PARTY_SOURCE_DIR}/expected)

if(NOT expected_fc)
  FetchContent_Populate(expected_fc)
endif()

add_subdirectory(${expected_fc_SOURCE_DIR} ${CMAKE_BINARY_DIR}/expected)
