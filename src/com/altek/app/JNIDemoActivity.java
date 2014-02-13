package com.altek.app;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class JNIDemoActivity extends Activity {
    /** Called when the activity is first created. */
   
	private static final String TAG = "JNIDemoActivity";
	
	private JNIServer jniSvr;

	private TextView tvShow1 = null;
	
	private final NotifyCb ncb = new NotifyCb();
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        DemoUtil.DEBUGI(TAG,"onCreate...");
        
        tvShow1 = (TextView)findViewById(R.id.tv_show1);
        
        jniSvr = new JNIServer(this);
        jniSvr.RegisterCallBack(ncb);
        
        
    }
	
   public void onCallBack(View v) {
       jniSvr.getCallBackFunc();
   }
	
   
   public void onJNITest(View v) {
       Toast.makeText(this, jniSvr.getJNIString(), Toast.LENGTH_LONG).show();
   }

   public void onDataJNITest(View v) {
       jniSvr.changeJavaDataFromJNI();
       tvShow1.setText("The data " + String.valueOf(jniSvr.getDataFromJNI()) + " is from JNI.");
   }
   
   public void onExit(View v) {
       jniSvr.Exit();
       finish();
   }
	
   private final class NotifyCb implements JNIServer.NotifyInterface{

	public void CallBackFun() {
		// TODO Auto-generated method stub
	    DemoUtil.DEBUGI(TAG, "CallBackFun...");
		
		
	}
	   
   }	

}