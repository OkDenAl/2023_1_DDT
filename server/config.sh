pip install conan
conan profile detect --force
#-------------
mkdir "build"
cd build/
#------------
conan install . --build=missing -s build_type=Debug
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
