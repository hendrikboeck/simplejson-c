CMAKE_BUILD_SYSTEM = "MinGW Makefiles"


build_windows:
	cmake . -Bbuild -G "${CMAKE_BUILD_SYSTEM}" -DCMAKE_BUILD_TYPE=Release

build_unixlike:
	cmake . -Bbuild -G "${CMAKE_BUILD_SYSTEM}" -DCMAKE_BUILD_TYPE=Release
	cmake --build build