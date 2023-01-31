project(basic_classes)

add_library (QClass TSQueue.hpp)
#set(OBJECT_FILES TSQueue.hpp)

target_link_libraries(QClass pthread)
set_target_properties(QClass PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (QClass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(QClass ${QClass})
include_directories(${PROJECT_SOURCE_DIR}/include)
#add_custom_target(QClass ALL
#    COMMAND ar rcs libQClass.a ${OBJECT_FILES}
#    DEPENDS ${OBJECT_FILES}
#)
