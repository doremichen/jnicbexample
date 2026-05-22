# JNI Callback Demo

This repository contains a simple Android JNI example demonstrating:

- native methods registered with `RegisterNatives`
- calling back into Java from C++
- using `jbyteArray`, static fields, and method IDs
- a small Java UI wrapper for triggering native functions

## Project Structure

- `jni/demojni.cpp` - JNI implementation and native callback logic
- `src/com/example/app/jnicb/JNIInterface.java` - Java JNI interface and callback handlers
- `src/com/example/app/jnicb/JNIDemoActivity.java` - sample Android activity UI
- `src/com/example/app/jnicb/DemoUtil.java` - simple logging helper
- `AndroidManifest.xml` - Android application manifest

## Build

This project appears to use the Android NDK build environment.

To build the native library and app, use the Android build tools configured for your environment.

For example, if using `ndk-build`:

```sh
ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./jni/Android.mk
```

Or if using `Android.bp` and a supported build system, follow your platform's standard build flow.

## License

This project is provided under the MIT License. See the source files for license headers.
