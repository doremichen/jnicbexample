#define LOG_TAG "AtkJNIDemo"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "jni.h"
#include <android/log.h>

#define __DEBUG__

#ifdef __DEBUG__
#define LOGV(...) __android_log_print( ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__ )
#define LOGD(...) __android_log_print( ANDROID_LOG_DEBUG,  LOG_TAG, __VA_ARGS__ )
#define LOGI(...) __android_log_print( ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__ )
#define LOGW(...) __android_log_print( ANDROID_LOG_WARN,  LOG_TAG, __VA_ARGS__ )
#define LOGE(...) __android_log_print( ANDROID_LOG_ERROR,  LOG_TAG, __VA_ARGS__ )
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif

#ifdef __TEST__
//jni member
jmethodID gmid;
JNIEnv *gJNIenv;
#endif

//Java full name qualifier
static const char* const kClassName = "com/altek/app/JNIServer";

//Field Id
struct FieldIds {
    // members
    jfieldID mId1;
};

static FieldIds gFieldIds;

//Method Id
static jmethodID	method_nativeCallBackFunc;
static jmethodID    method_nativeCallBackFuncArg1;
static jmethodID    method_nativeCallBackFuncArg2;

//class ALTEKJNIContext
class ALTEKJNIContext {
public:
	//Singleton
	static ALTEKJNIContext *instance;
	static ALTEKJNIContext *getALTEKJNIContext()
	{
		if(!instance) {
			instance = new ALTEKJNIContext;
		}

		return instance;
	}

	//JNI env
	void setJNIEnv(const JNIEnv& env)
	{
		atkCtx_env = const_cast<JNIEnv *>(&env);
	}

	JNIEnv* getJNIEnv() const
	{
		return atkCtx_env;
	}

	// java class
	void setclass(const jclass& clazz)
	{
		atkCtx_clazz = clazz;
	}

	jclass getclass() const
	{
		return atkCtx_clazz;
	}

	//Notify app layer from native layer
	void notify()
	{
		LOGI("[%s] enter\n", __FUNCTION__);
	    jobject jobj;

	    jobj = atkCtx_env->AllocObject(atkCtx_clazz);

	    atkCtx_env->CallVoidMethod(jobj, method_nativeCallBackFunc);

	    LOGI("[%s] exit\n", __FUNCTION__);
	}

	void notify(const int &num)
	{
		LOGI("[%s] enter\n", __FUNCTION__);
		jobject jobj;

		jobj = atkCtx_env->AllocObject(atkCtx_clazz);

		atkCtx_env->CallVoidMethod(jobj, method_nativeCallBackFuncArg1, num);

		LOGI("[%s] exit\n", __FUNCTION__);
	}

	void notifyWithByteArray()
	{
		LOGI("[%s] enter\n", __FUNCTION__);
		jobject jobj;
		jbyte toCopy[3] = {1, 2, 3};
		int length = sizeof(toCopy);
		jbyteArray array = atkCtx_env->NewByteArray(length);
		atkCtx_env->SetByteArrayRegion(array, 0, 3, toCopy);

		jobj = atkCtx_env->AllocObject(atkCtx_clazz);
		atkCtx_env->CallVoidMethod(jobj, method_nativeCallBackFuncArg2, array);
		LOGI("[%s] exit\n", __FUNCTION__);
	}

	void changeJavaData1()
	{
		LOGI("[%s] enter\n", __FUNCTION__);
		jint data = atkCtx_env->GetStaticIntField(atkCtx_clazz, gFieldIds.mId1);
		LOGI("[%s]: data[%d]\n", __FUNCTION__, data);
		data = data + 122;
		atkCtx_env->SetStaticIntField(atkCtx_clazz, gFieldIds.mId1, data);
		LOGI("[%s] exit\n", __FUNCTION__);
	}
private:
	ALTEKJNIContext():atkCtx_env(NULL),atkCtx_clazz(0){};

	JNIEnv		*atkCtx_env;
	jclass		atkCtx_clazz;

	//Do not need to implement.
	ALTEKJNIContext(const ALTEKJNIContext&);
	//Do not need to implement.
	ALTEKJNIContext& operator=(const ALTEKJNIContext&);


};

ALTEKJNIContext *ALTEKJNIContext::instance = NULL;

#ifdef __TEST__
void notify()
{
	  LOGI("+++ notify +++");
	  static const char* const kClassName =
        "com/altek/app/JNIServer";

    jclass clazz;
    jobject jobj;

    /* look up the class */
    clazz = gJNIenv->FindClass(kClassName);
    if (clazz == NULL) {
        LOGE("Can't find class %s\n", kClassName);
        return;
    }

        gmid = gJNIenv->GetMethodID(clazz, "nativeCallBackFunc", "()V");

        if(!gmid) {
					LOGI("nativeCallBackFunc: failed to get method ID");
					return;
					}


        jobj = gJNIenv->AllocObject(clazz);

       gJNIenv->CallVoidMethod(jobj, gmid);

}
#endif

//Jni function implement
static jstring getJNIString(JNIEnv *env, jobject clazz)
{
	jstring str = NULL;

	const char* value = "Doremi JNI Demo Str";

	str = env->NewStringUTF(value);	
	return str;
}

static void getJNICallBackfunc(JNIEnv *env, jobject clazz)
{
	LOGI("[%s] enter\n", __FUNCTION__);
//	ALTEKJNIContext* context =  new ALTEKJNIContext;
	ALTEKJNIContext* context =  ALTEKJNIContext::getALTEKJNIContext();
#ifdef __TEST__
	notify();
#else
	context->notify();
//	context->notify(100);
//	context->notifyWithByteArray();
#endif
    LOGI("[%s] exit\n", __FUNCTION__);
}

static void changeJavaDataFromJNI(JNIEnv *env, jobject clazz)
{
	LOGI("[%s] enter\n", __FUNCTION__);
	ALTEKJNIContext* context =  ALTEKJNIContext::getALTEKJNIContext();
	context->changeJavaData1();
}


static void finish(JNIEnv *env, jobject clazz)
{
	ALTEKJNIContext* context =  ALTEKJNIContext::getALTEKJNIContext();

	if(!context) {
		delete context;
		context = NULL;
	}
}

//=====================================================================================
/*
 * Array of methods.
 *
 * Each entry has three fields: the name of the method, the method
 * signature, and a pointer to the native implementation.
 */
static const JNINativeMethod gMethods[] = {
    {"_getJNIString", "()Ljava/lang/String;", (void*)getJNIString},
    {"_getJNICallbackfunc", "()V", (void*)getJNICallBackfunc},
    {"_changeJavaDataFromJNI", "()V", (void*)changeJavaDataFromJNI},
    {"_Exit", "()V", (void*)finish},
};

static int registerMethods(JNIEnv* env) {

    jclass clazz;

    ALTEKJNIContext* context =  ALTEKJNIContext::getALTEKJNIContext();

    /* look up the class */
    clazz = env->FindClass(kClassName);
    if (clazz == NULL) {
        LOGE("Can't find class %s\n", kClassName);
        return -1;
    }

    /* register all the methods */
    if (env->RegisterNatives(clazz, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
    {
        LOGE("Failed registering methods for %s\n", kClassName);
        return -1;
    }
    
#ifdef __TEST__
    gJNIenv = env;
#else

    //get field id object
    gFieldIds.mId1 = env->GetStaticFieldID(clazz, "mData1FromNative", "I");   //integer data

    //get method id object
    method_nativeCallBackFunc = env->GetMethodID(clazz, "nativeCallBackFunc", "()V");

  	if(!method_nativeCallBackFunc) {
  		LOGE("[%s]: failed to get method ID", __FUNCTION__);
  		return -1;
  	}

  	method_nativeCallBackFuncArg1 = env->GetMethodID(clazz, "nativeCallBackFuncArg1", "(I)V");

  	if(!method_nativeCallBackFuncArg1) {
  		LOGE("[%s]: failed to get method ID", __FUNCTION__);
  	  	return -1;
  	}

  	method_nativeCallBackFuncArg2 = env->GetMethodID(clazz, "nativeCallBackFuncArg2", "([B)V");

  	if(!method_nativeCallBackFuncArg2) {
  		LOGE("[%s]: failed to get method ID", __FUNCTION__);
  	  	return -1;
  	}

    context->setJNIEnv(*env);
    context->setclass(clazz);



#endif
    /* fill out the rest of the ID cache */
    return 0;
}

/*
 * This is called by the VM when the shared library is first loaded.
 */
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;
	LOGI("[%s] enter\n", __FUNCTION__);

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("[%s] ERROR: GetEnv failed\n", __FUNCTION__);
        goto fail;
    }
    assert(env != NULL);

    if (registerMethods(env) != 0) {
        LOGE("[%s] ERROR: PlatformLibrary native registration failed\n", __FUNCTION__);
        goto fail;
    }

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

fail:
    return result;
}
