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

package com.example.app.jnicb;

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
