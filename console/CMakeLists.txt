# CMakeList.txt: CMake-Projekt für "vm-starter". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

project ("vm-starter")
add_subdirectory("tiny-process-library")
add_executable (vm-starter "vm-starter.cpp" res.rc)
target_link_libraries(vm-starter tiny-process-library)