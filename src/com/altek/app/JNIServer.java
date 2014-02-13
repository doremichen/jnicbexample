package com.altek.app;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

class JNIServer {

	private static final String TAG = "JNIServer";
	
	private static Context jni_svr;	
	private static NotifyInterface mNCB =  null;

	/* Begin native fields: All of these fields are set by native code. */
	public static int mData1FromNative;	
	/* End native fields. */
	
	public JNIServer(Context context) {
		// TODO Auto-generated constructor stub
	    DemoUtil.DEBUGI(TAG, "JNIServer...");
		jni_svr = context;
	
	}

	
	static {
	    DemoUtil.DEBUGI(TAG, "start load libaltekjni.so");
		System.loadLibrary("altekjni");
	}
	
	public String getJNIString(){
	    DemoUtil.DEBUGI(TAG, "+++ getJNIString +++");
		return _getJNIString();
	}
	
	public void getCallBackFunc(){
	    DemoUtil.DEBUGI(TAG, "+++ getCallBackFunc +++");
		_getJNICallbackfunc();
	}
	
	public void changeJavaDataFromJNI(){
        DemoUtil.DEBUGI(TAG, "+++ changeJavaDataFromJNI +++");
        _changeJavaDataFromJNI();
    }
	
	
	public void Exit(){
	    DemoUtil.DEBUGI(TAG, "+++ Exit +++");
	    _Exit();
	}
	
	public final void RegisterCallBack (NotifyInterface cb) {
	    DemoUtil.DEBUGI(TAG, "RegisterCallBack.....");
		mNCB = cb;		
	}
	
	public int getDataFromJNI() {
	    DemoUtil.DEBUGI(TAG, "getDataFromJNI.....");
	    DemoUtil.DEBUGI(TAG, "mData1FromNative = " + mData1FromNative);
	    return mData1FromNative;
	}
	
	
	/* Begin native method: All of these fields are set by native code. */
	private void nativeCallBackFunc() {
	    DemoUtil.DEBUGI(TAG, "nativeCallBackFunc.....");

		if(mNCB != null){
		    DemoUtil.DEBUGI(TAG, "mNCB != null");
			mNCB.CallBackFun();
		}			
		else
		    DemoUtil.DEBUGI(TAG, "mNCB == null");
	}
	
	
	private void nativeCallBackFuncArg1(int num) {
	    DemoUtil.DEBUGI(TAG, "nativeCallBackFuncArg1.....");
	    DemoUtil.DEBUGI(TAG, "num = " + num);	    
	}
	
	private void nativeCallBackFuncArg2(byte[] arr) {
	    DemoUtil.DEBUGI(TAG, "nativeCallBackFuncArg2...");
        for (byte a : arr) {
            DemoUtil.DEBUGI(TAG, Byte.toString(a));
        }
	}
	/* End native method. */
	
	public interface NotifyInterface {
		
		void CallBackFun();
	}
	
	
	private static final native String _getJNIString();   //call jni function return string.	
	private static final native void _getJNICallbackfunc();   //Call Back Test 
	private static final native void _changeJavaDataFromJNI(); //change java data from JNI
	private static final native void _Exit();
	
}
