# CMake generated Testfile for 
# Source directory: /home/eric/github/gap-buffer
# Build directory: /home/eric/github/gap-buffer/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[GapBufferTests]=] "/home/eric/github/gap-buffer/cmake-build-debug/gbtest")
set_tests_properties([=[GapBufferTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/eric/github/gap-buffer/CMakeLists.txt;33;add_test;/home/eric/github/gap-buffer/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
