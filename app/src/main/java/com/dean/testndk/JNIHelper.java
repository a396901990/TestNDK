package com.dean.testndk;

import android.support.annotation.Keep;
import android.util.Log;

/**
 * Created by DeanGuo on 7/8/16.
 */
public class JNIHelper {

    @Keep
    private void updateStatus(String msg) {
        if (msg.toLowerCase().contains("error")) {
            Log.e("JniHandler", "Native Err: " + msg);
        } else {
            Log.i("JniHandler", "Native Msg: " + msg);
        }
    }

    public static native String getStringFromNative();
}
