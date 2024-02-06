/**
 * Main UI activity
 */
package com.example.app.jnicb;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.app.jnicb.R;

public class JNIDemoActivity extends Activity {
    /** Called when the activity is first created. */
    private JNIInterface mJniInterface;

    private TextView mShow = null;

    private final NotifyCb mNotify = new NotifyCb();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        DemoUtil.print(this, "onCreate...");

        mShow = (TextView) findViewById(R.id.tv_show1);

        mJniInterface = new JNIInterface();
        mJniInterface.RegisterCallBack(mNotify);

    }

    /**
     * 
     * The method is invoked when press the onCallBackFunc button
     * @param v
     */
    public void onCallBack(View v) {
        mJniInterface.getCallBackFunc();
    }

    /**
     * 
     * The method is invoked when press the JNI function test button
     * @param v
     */
    public void onJNITest(View v) {
        Toast.makeText(this, mJniInterface.getJNIString(), Toast.LENGTH_LONG).show();
    }

    /**
     * 
     * The method is invoked when press the Update data button
     * @param v
     */
    public void onDataJNITest(View v) {
        mJniInterface.changeJavaDataFromJNI();
        mShow.setText("The data " + String.valueOf(mJniInterface.getDataFromJNI())
                + " is from JNI.");
    }

    /**
     * 
     * The method is invoked when press the Exit button
     * @param v
     */
    public void onExit(View v) {
        mJniInterface.Exit();
        finish();
    }

    /**
     * 
     * Notitfy from JNI Interface
     */
    private final class NotifyCb implements JNIInterface.NotifyInterface {

        public void CallBackFun() {
            DemoUtil.print(this, "CallBackFun...");

        }

    }

}