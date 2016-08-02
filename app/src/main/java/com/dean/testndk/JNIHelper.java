package com.dean.testndk;

/**
 * Created by DeanGuo on 7/8/16.
 */
public class JNIHelper {

    public static native String getStringFromNative();
    public static native int[] doOrder(int[] nums);
}
