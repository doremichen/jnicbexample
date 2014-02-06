package com.altek.app;

import android.util.Log;

public final class DemoUtil {

    //control debug message
    private static final boolean isDebug = true;
    
    public static void DEBUGI(String TAG, String str) {
        if(isDebug)
            Log.i(TAG, str);
    }
    
    
}
