/**
 * This is util tool
 */
package com.example.app.jnicb;

import android.util.Log;

public final class DemoUtil {

    // control debug message
    private static final boolean LOGD = true;
    public static final String TAG = "JNIDemo";

    public static void print(String tag, String str) {
        if (LOGD) {
            Log.i(tag, str);
        }
    }

    public static void print(Object obj, String str) {
        if (LOGD) {
            Log.i(TAG, obj.getClass().getSimpleName() + " " + str);
        }
    }
}
