#include <jni.h>
#include <vector>
#include <android/log.h>
#include <opencv2/opencv.hpp>
#include "canny_processor.h"

#define TAG "NativeLib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

static CannyProcessor* g_processor = nullptr;

void initProcessor() {
    if (g_processor == nullptr) {
        g_processor = new CannyProcessor(50.0, 150.0, 5);
        LOGD("Processor initialized");
    }
}

std::vector<uint8_t> jbyteArrayToVector(JNIEnv* env, jbyteArray array) {
    jsize length = env->GetArrayLength(array);
    std::vector<uint8_t> vec(length);
    env->GetByteArrayRegion(array, 0, length, reinterpret_cast<jbyte*>(vec.data()));
    return vec;
}

jbyteArray vectorToJbyteArray(JNIEnv* env, const std::vector<uint8_t>& vec) {
    jbyteArray array = env->NewByteArray(vec.size());
    if (array == nullptr) return nullptr;
    env->SetByteArrayRegion(array, 0, vec.size(), reinterpret_cast<const jbyte*>(vec.data()));
    return array;
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_edgedetect_NativeLib_processFrame(
        JNIEnv* env, jobject, jbyteArray nv21Data, jint width, jint height) {
    
    initProcessor();
    
    try {
        std::vector<uint8_t> nv21Vec = jbyteArrayToVector(env, nv21Data);
        cv::Mat gray;
        CannyProcessor::nv21ToGray(nv21Vec, width, height, gray);
        
        cv::Mat rgba;
        g_processor->process(gray, rgba);
        
        std::vector<uint8_t> rgbaVec(rgba.data, rgba.data + rgba.total() * rgba.channels());
        return vectorToJbyteArray(env, rgbaVec);
    } catch (...) {
        LOGD("Exception in processFrame");
        return nullptr;
    }
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_edgedetect_NativeLib_convertNV21ToRGBA(
        JNIEnv* env, jobject, jbyteArray nv21Data, jint width, jint height) {
    
    try {
        std::vector<uint8_t> nv21Vec = jbyteArrayToVector(env, nv21Data);
        cv::Mat rgba;
        CannyProcessor::nv21ToRGBA(nv21Vec, width, height, rgba);
        
        std::vector<uint8_t> rgbaVec(rgba.data, rgba.data + rgba.total() * rgba.channels());
        return vectorToJbyteArray(env, rgbaVec);
    } catch (...) {
        return nullptr;
    }
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("Native library loaded");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved) {
    if (g_processor != nullptr) {
        delete g_processor;
        g_processor = nullptr;
    }
}
