# EdgeDetectApp

Hi! I'm Tushit Maheshwari — a final year B.Tech student at PSIT Kanpur (Roll No: 2201641530188). I built this project as a small, hands-on experiment to learn more about real-time image processing on Android using OpenCV, JNI and OpenGL ES. I’m quite passionate about computer vision and mobile graphics, so I decided to try implementing a real-time Canny edge detector that runs on camera frames and shows the result with hardware-accelerated rendering.

This README explains what the app does, how to set it up, and some notes from someone who has been tinkering late nights in the lab :)

---

## What this project does (in simple words)

EdgeDetectApp captures camera frames in real time on an Android device, runs the Canny edge detector (from OpenCV) using native C++ (via JNI), and renders the result using OpenGL ES for smooth, fast output. You can toggle between the raw camera preview and the edge-detected view, and there is a small FPS counter so you can see performance while testing.

There is also a simple TypeScript web viewer included to visualize processed frames or to demonstrate the algorithm on the web (mostly for demos and comparison).

---

## Features

- Real-time camera processing on Android
- Canny edge detection pipeline implemented in native C++ (JNI)
- Hardware-accelerated rendering with OpenGL ES
- Toggle between raw preview and edge view
- Simple FPS counter for performance measurement
- A small TypeScript web viewer for demos

---

## Why I did this

As a final year student, I wanted a project that touches a few important areas:
- Mobile development (Android)
- Native programming (C++ / JNI)
- Computer vision basics (OpenCV Canny)
- Graphics (OpenGL ES)
Combining all of these helped me understand end-to-end flow from camera capture to rendering.

---

## Prerequisites

Before building, make sure you have:

- Android Studio (latest stable recommended)
- Android NDK installed (check Android Studio SDK Manager)
- OpenCV Android SDK (download from OpenCV website)  
  Note: The app expects you to update the OpenCV path in the CMakeLists file (see below).
- For the web viewer:
  - Node.js and npm (v14+ recommended)

---

## Quick setup (step-by-step)

1. Clone the repo:
   ```bash
   git clone https://github.com/Tushit-Maheshwari/EdgeDetectApp.git
   cd EdgeDetectApp
   ```

2. Download the OpenCV Android SDK (if you don’t have it already).
   - You can get it from https://opencv.org/releases/ -> Android packages

3. Update OpenCV path:
   - Open `app/src/main/cpp/CMakeLists.txt`
   - Change the OpenCV_ROOT or include path variable to point to your local OpenCV Android SDK location. For example:
     ```
     set(OpenCV_DIR "/home/username/Downloads/OpenCV-android/sdk")
     ```
   - Make sure the path points to the `sdk` folder that contains `java` and `native` directories.

4. Open project in Android Studio:
   - File -> Open -> select project folder
   - Let Gradle sync and CMake configure. If CMake / NDK versions mismatch, change Android Studio SDK/NDK settings accordingly.

5. Build & Run:
   - Prefer testing on a real device (camera and performance are better).
   - Connect device, enable USB debugging, and run the app from Android Studio.
   - Grant camera permission when prompted.

6. Web viewer (optional):
   ```bash
   cd web
   npm install
   npm run build
   npm run serve
   ```
   - The web viewer is a lightweight demo to visualize or test sample frames.

---

## How the app works (high-level)

1. Camera frames are captured in Java/Kotlin (Android Camera2 or Camera API).
2. Frames are passed to native C++ code via JNI.
3. In native code:
   - Frames are converted to OpenCV Mat format
   - Canny edge detection is applied
   - The processed frame (edges) is passed back as a texture-friendly buffer
4. OpenGL ES is used to render the final frames on screen with good performance.
5. A small FPS counter and a mode toggle let you switch and observe performance.

This pipeline keeps heavy processing in native code for speed, and uses GPU for rendering to keep UI smooth.

---

## Tips & troubleshooting (what I faced and fixed)

- OpenCV path errors:
  - Most build problems come from wrong OpenCV path in CMakeLists. Double-check the path and that the SDK layout is correct.
- NDK / CMake version:
  - If CMake fails, match the NDK/CMake versions used by project or update project settings in Android Studio.
- Permissions:
  - If camera shows black screen, ensure camera permission is granted and the device camera is not used by another app.
- Testing on emulator:
  - Emulators often have poor camera performance. Use a real device for reliable FPS and camera feed.
- Debugging JNI:
  - Use logcat and __android_log_print in native code to print useful info.
- Performance:
  - If FPS is low, reduce frame resolution or optimize the Canny parameters. Also ensure GPU rendering path is active.

---

## How you can contribute

This repo is small and experimental, but contributions are welcome. Ideas:
- Add adaptive thresholding or other edge filters
- Improve Camera2 support for more devices
- Add unit tests or integration tests
- Improve web viewer UX and connection to Android app (for remote preview)

If you want to contribute, please open an issue or a pull request. I’ll try to respond, but I’m a student with limited time — still happy to collaborate!

---

## Acknowledgements & References

- OpenCV project and documentation — for algorithms and Android SDK
- Android docs (Camera2, NDK, OpenGL ES) — for integration ideas
- StackOverflow and blog posts I consulted during development

---

## License

This project is shared for educational purposes. Feel free to use it as a learning reference. (If you want a formal license, we can add one — MIT is a common choice.)

---

## Final notes (from me)

Thanks for looking into my project! I built this as a learning exercise and to better understand native-mobile CV workflows. If you try it out and find it useful or have suggestions, please raise an issue.

— Tushit Maheshwari  
B.Tech Final Year, PSIT Kanpur  
Roll No: 2201641530188  
Passionate about computer vision and mobile development
