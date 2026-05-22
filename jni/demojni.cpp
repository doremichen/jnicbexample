/*
 * Copyright (c) 2026
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define LOG_TAG "JNIDemo"

#include <assert.h>
#include <jni.h>
#include <android/log.h>

#define __DEBUG__

#ifdef __DEBUG__
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif

static constexpr const char* kClassName = "com/example/app/jnicb/JNIInterface";

struct FieldIds {
    jfieldID data1 = nullptr;
};

static FieldIds gFieldIds;

static jmethodID gNativeCallbackNoArg = nullptr;
static jmethodID gNativeCallbackIntArg = nullptr;
static jmethodID gNativeCallbackByteArrayArg = nullptr;

class JNIContext {
public:
    static JNIContext& Instance() {
        static JNIContext instance;
        return instance;
    }

    void setJNIEnv(JNIEnv* env) {
        env_ = env;
    }

    JNIEnv* getJNIEnv() const {
        return env_;
    }

    void setClass(jclass clazz) {
        if (env_ == nullptr || clazz == nullptr) {
            return;
        }

        if (clazz_ != nullptr) {
            env_->DeleteGlobalRef(clazz_);
        }

        clazz_ = static_cast<jclass>(env_->NewGlobalRef(clazz));
    }

    jclass getClass() const {
        return clazz_;
    }

    void notify() const {
        LOGI("[%s] enter", __FUNCTION__);
        if (env_ == nullptr || clazz_ == nullptr) {
            return;
        }

        jobject jobj = env_->AllocObject(clazz_);
        if (jobj == nullptr) {
            return;
        }

        env_->CallVoidMethod(jobj, gNativeCallbackNoArg);
        env_->DeleteLocalRef(jobj);
        LOGI("[%s] exit", __FUNCTION__);
    }

    void notify(int num) const {
        LOGI("[%s] enter", __FUNCTION__);
        if (env_ == nullptr || clazz_ == nullptr) {
            return;
        }

        jobject jobj = env_->AllocObject(clazz_);
        if (jobj == nullptr) {
            return;
        }

        env_->CallVoidMethod(jobj, gNativeCallbackIntArg, num);
        env_->DeleteLocalRef(jobj);
        LOGI("[%s] exit", __FUNCTION__);
    }

    void notifyWithByteArray() const {
        LOGI("[%s] enter", __FUNCTION__);
        if (env_ == nullptr || clazz_ == nullptr) {
            return;
        }

        const jbyte toCopy[3] = {1, 2, 3};
        const jsize length = sizeof(toCopy) / sizeof(toCopy[0]);
        jbyteArray array = env_->NewByteArray(length);
        if (array == nullptr) {
            return;
        }

        env_->SetByteArrayRegion(array, 0, length, toCopy);

        jobject jobj = env_->AllocObject(clazz_);
        if (jobj != nullptr) {
            env_->CallVoidMethod(jobj, gNativeCallbackByteArrayArg, array);
            env_->DeleteLocalRef(jobj);
        }

        env_->DeleteLocalRef(array);
        LOGI("[%s] exit", __FUNCTION__);
    }

    void changeJavaData1() const {
        LOGI("[%s] enter", __FUNCTION__);
        if (env_ == nullptr || clazz_ == nullptr) {
            return;
        }

        jint data = env_->GetStaticIntField(clazz_, gFieldIds.data1);
        LOGI("[%s]: data[%d]", __FUNCTION__, data);
        env_->SetStaticIntField(clazz_, gFieldIds.data1, data + 122);
        LOGI("[%s] exit", __FUNCTION__);
    }

    void cleanup() {
        if (env_ != nullptr && clazz_ != nullptr) {
            env_->DeleteGlobalRef(clazz_);
            clazz_ = nullptr;
        }
        env_ = nullptr;
    }

private:
    JNIContext() : env_(nullptr), clazz_(nullptr) {}
    JNIContext(const JNIContext&) = delete;
    JNIContext& operator=(const JNIContext&) = delete;

    JNIEnv* env_;
    jclass clazz_;
};

static jstring getJNIString(JNIEnv* env, jobject /*clazz*/) {
    return env->NewStringUTF("This is JNI Demo Str");
}

static void getJNICallBackfunc(JNIEnv* env, jobject /*clazz*/) {
    LOGI("[%s] enter", __FUNCTION__);
    JNIContext::Instance().notify();
    JNIContext::Instance().notify(100);
    JNIContext::Instance().notifyWithByteArray();
    LOGI("[%s] exit", __FUNCTION__);
}

static void changeJavaDataFromJNI(JNIEnv* env, jobject /*clazz*/) {
    LOGI("[%s] enter", __FUNCTION__);
    JNIContext::Instance().changeJavaData1();
    LOGI("[%s] exit", __FUNCTION__);
}

static void finish(JNIEnv* env, jobject /*clazz*/) {
    (void)env;
    JNIContext::Instance().cleanup();
}

static const JNINativeMethod gMethods[] = {
    {"_getJNIString", "()Ljava/lang/String;", reinterpret_cast<void*>(getJNIString)},
    {"_getJNICallbackfunc", "()V", reinterpret_cast<void*>(getJNICallBackfunc)},
    {"_changeJavaDataFromJNI", "()V", reinterpret_cast<void*>(changeJavaDataFromJNI)},
    {"_Exit", "()V", reinterpret_cast<void*>(finish)},
};

static int registerMethods(JNIEnv* env) {
    jclass clazz = env->FindClass(kClassName);
    if (clazz == nullptr) {
        LOGE("Can't find class %s", kClassName);
        return -1;
    }

    if (env->RegisterNatives(clazz, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK) {
        LOGE("Failed registering methods for %s", kClassName);
        env->DeleteLocalRef(clazz);
        return -1;
    }

    gFieldIds.data1 = env->GetStaticFieldID(clazz, "sData1FromNative", "I");
    if (gFieldIds.data1 == nullptr) {
        LOGE("[%s]: failed to get field ID", __FUNCTION__);
        env->DeleteLocalRef(clazz);
        return -1;
    }

    gNativeCallbackNoArg = env->GetMethodID(clazz, "nativeCallBackFunc", "()V");
    if (gNativeCallbackNoArg == nullptr) {
        LOGE("[%s]: failed to get method ID", __FUNCTION__);
        env->DeleteLocalRef(clazz);
        return -1;
    }

    gNativeCallbackIntArg = env->GetMethodID(clazz, "nativeCallBackFuncArg1", "(I)V");
    if (gNativeCallbackIntArg == nullptr) {
        LOGE("[%s]: failed to get method ID", __FUNCTION__);
        env->DeleteLocalRef(clazz);
        return -1;
    }

    gNativeCallbackByteArrayArg = env->GetMethodID(clazz, "nativeCallBackFuncArg2", "([B)V");
    if (gNativeCallbackByteArrayArg == nullptr) {
        LOGE("[%s]: failed to get method ID", __FUNCTION__);
        env->DeleteLocalRef(clazz);
        return -1;
    }

    JNIContext::Instance().setJNIEnv(env);
    JNIContext::Instance().setClass(clazz);
    env->DeleteLocalRef(clazz);

    return 0;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = nullptr;
    jint result = -1;
    LOGI("[%s] enter", __FUNCTION__);

    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_4) != JNI_OK) {
        LOGE("[%s] ERROR: GetEnv failed", __FUNCTION__);
        goto fail;
    }
    assert(env != nullptr);

    if (registerMethods(env) != 0) {
        LOGE("[%s] ERROR: native registration failed", __FUNCTION__);
        goto fail;
    }


fail:
    return result;
}
