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
	
	
	public void Exit(){
	    DemoUtil.DEBUGI(TAG, "+++ Exit +++");
	    _Exit();
	}
	
	public final void RegisterCallBack (NotifyInterface cb) {
	    DemoUtil.DEBUGI(TAG, "RegisterCallBack.....");
		mNCB = cb;		
	}
	
	
	public void nativeCallBackFunc() {
	    DemoUtil.DEBUGI(TAG, "nativeCallBackFunc.....");

		if(mNCB != null){
		    DemoUtil.DEBUGI(TAG, "mNCB != null");
			mNCB.CallBackFun();
		}			
		else
		    DemoUtil.DEBUGI(TAG, "mNCB == null");
	}
	
	
	public void nativeCallBackFuncArg1(int num) {
	    DemoUtil.DEBUGI(TAG, "nativeCallBackFuncArg1.....");
	    DemoUtil.DEBUGI(TAG, "num = " + num);	    
	}
	
	public void nativeCallBackFuncArg2(byte[] arr) {
	    DemoUtil.DEBUGI(TAG, "nativeCallBackFuncArg2...");
        for (byte a : arr) {
            DemoUtil.DEBUGI(TAG, Byte.toString(a));
        }
	}
	
	
	public interface NotifyInterface {
		
		void CallBackFun();
	}
	
	
	private static final native String _getJNIString();   //call jni function return string.	
	private static final native void _getJNICallbackfunc();   //Call Back Test 
	private static final native void _Exit();
	
}
