/**
 * Jni interface class
 */
package com.adam.app.jni.example;

class JNIInterface {
    private static NotifyInterface sNotify = null;

    /* Begin native fields: All of these fields are set by native code. */
    public static int sData1FromNative;

    /* End native fields. */

    public JNIInterface() {
        // TODO Auto-generated constructor stub
        DemoUtil.print(this, "JNIServer...");

    }

    static {
        DemoUtil.print(DemoUtil.TAG, "start load libdemojni.so");
        System.loadLibrary("demojni");
    }

    public String getJNIString() {
        DemoUtil.print(this, "+++ getJNIString +++");
        return _getJNIString();
    }

    public void getCallBackFunc() {
        DemoUtil.print(this, "+++ getCallBackFunc +++");
        _getJNICallbackfunc();
    }

    public void changeJavaDataFromJNI() {
        DemoUtil.print(this, "+++ changeJavaDataFromJNI +++");
        _changeJavaDataFromJNI();
    }

    public void Exit() {
        DemoUtil.print(this, "+++ Exit +++");
        _Exit();
    }

    public final void RegisterCallBack(NotifyInterface notify) {
        DemoUtil.print(this, "RegisterCallBack.....");
        sNotify = notify;
    }

    public int getDataFromJNI() {
        DemoUtil.print(this, "getDataFromJNI.....");
        DemoUtil.print(this, "sData1FromNative = " + sData1FromNative);
        return sData1FromNative;
    }

    /* Begin native method: All of these fields are set by native code. */
    private void nativeCallBackFunc() {
        DemoUtil.print(this, "nativeCallBackFunc.....");

        if (sNotify != null) {
            DemoUtil.print(this, "sNotify != null");
            sNotify.CallBackFun();
        } else
            DemoUtil.print(this, "sNotify == null");
    }

    private void nativeCallBackFuncArg1(int num) {
        DemoUtil.print(this, "nativeCallBackFuncArg1.....");
        DemoUtil.print(this, "num = " + num);
    }

    private void nativeCallBackFuncArg2(byte[] arr) {
        DemoUtil.print(this, "nativeCallBackFuncArg2...");
        for (byte a : arr) {
            DemoUtil.print(this, Byte.toString(a));
        }
    }

    /* End native method. */

    public interface NotifyInterface {

        void CallBackFun();
    }
    
    // Jni function
    private static final native String _getJNIString(); 
    private static final native void _getJNICallbackfunc();
    private static final native void _changeJavaDataFromJNI();
    private static final native void _Exit();

}
