cmake -E make_directory "build-android" && cmake -E chdir "build-android" cmake --build ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/android-toolchain/android.toolchain.cmake -DANDROID_NDK=${ndk_path} -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" 
