### Code Architecture ###

1. Core code

-- tiny.\*

2. Test code

-- dbtest.cc, basic function test
-- threaded\_test.cc, use four threads to simulate high concurrency scenorio

3. Utility code

-- generator.cc, generate (key,value) data file

### About Test ###

This project uses CMake as build system with uint test module included.
The data file size variable is written in the CMakeLists.txt as $DATA\_SIZE,
adjust this variable to test concurrent random read in varing data size.


