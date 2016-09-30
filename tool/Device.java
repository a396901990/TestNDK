package org.cocos2dx.ext;

import java.util.Locale;

import org.apache.commons.lang.StringUtils;
import org.hcg.util.GameContext;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.telephony.TelephonyManager;
import android.text.ClipboardManager;
import android.util.Log;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.*;
import android.accounts.Account;
import android.accounts.AccountManager;

public class Device {

	private static ClipboardManager clipboard = null;
	private static Context _context = null;
	private static String startType = "";//mf add
    private static String gotoType = "";
	
	public static void init(Context ctx) {
		_context = ctx;
		clipboard = (ClipboardManager) ctx
				.getSystemService(Context.CLIPBOARD_SERVICE);
	}
	
	public static void setStartType(String str){//mf add
		startType = str;
	}
    
    public static void setGotoType(String str){
        gotoType = str;
    }

	public static String getLanguage() {
		String sLang = Locale.getDefault().getLanguage();
		if (sLang.compareTo("zh") == 0)
			return Locale.getDefault().toString().equals("zh_CN") ? "zh-Hans"
					: "zh-Hant";
		return sLang;
	}

	public static String getOSVersion() {
		String osVersion = "" + Build.VERSION.SDK_INT;
		Log.d("WarZ","osVersion："+ osVersion);
		return osVersion;
	}

	public static String clipboardGetText() {
		try {
			return clipboard.getText().toString();
		} catch (Exception e) {
		//	Tracker.reportException(Jni.getGameActivity(), e);
		}
		return "";
	}

	public static void clipboardSetText(final String text) {
		Jni.getGameActivity().runOnUiThread(new Runnable() {
			public void run() {
				try {
					clipboard.setText(text);
				} catch (Exception e) {
				//	Tracker.reportException(Jni.getGameActivity(), e);
				}
			}
		});
	}
	
	public static String getHandSetInfo() {
		try {
			String network = "unknown";
			TelephonyManager tm = (TelephonyManager) _context.getSystemService(Context.TELEPHONY_SERVICE);
	        ConnectivityManager connectivityManager = (ConnectivityManager) _context.getSystemService(Context.CONNECTIVITY_SERVICE);
	        NetworkInfo activeNetInfo = connectivityManager.getActiveNetworkInfo();
	        if (activeNetInfo != null) {
	        	if(activeNetInfo.getType() == ConnectivityManager.TYPE_WIFI) {
	        		network = "Wifi";
	        	} else if (activeNetInfo.getType() == ConnectivityManager.TYPE_MOBILE) {
	        		switch (tm.getNetworkType()) {
		                case TelephonyManager.NETWORK_TYPE_GPRS:
		                case 16://TelephonyManager.NETWORK_TYPE_GSM
		                case TelephonyManager.NETWORK_TYPE_EDGE:
		                case TelephonyManager.NETWORK_TYPE_CDMA:
		                case TelephonyManager.NETWORK_TYPE_1xRTT:
		                case TelephonyManager.NETWORK_TYPE_IDEN:
		                	network = "2G";
		                	break;
		                case TelephonyManager.NETWORK_TYPE_UMTS:
		                case TelephonyManager.NETWORK_TYPE_EVDO_0:
		                case TelephonyManager.NETWORK_TYPE_EVDO_A:
		                case TelephonyManager.NETWORK_TYPE_HSDPA:
		                case TelephonyManager.NETWORK_TYPE_HSUPA:
		                case TelephonyManager.NETWORK_TYPE_HSPA:
		                case TelephonyManager.NETWORK_TYPE_EVDO_B:
		                case TelephonyManager.NETWORK_TYPE_EHRPD:
		                case TelephonyManager.NETWORK_TYPE_HSPAP:
		                case 17://TelephonyManager.NETWORK_TYPE_TD_SCDMA
		                	network = "3G";
		                	break;
		                case TelephonyManager.NETWORK_TYPE_LTE:
		                case 18://TelephonyManager.NETWORK_TYPE_IWLAN
		                	network = "4G";
		                	break;
		                default:
		                	break;
	                }
	        	}
	        }
		    String handSetInfo = 
		    	      "Model:" + android.os.Build.MODEL +   
		    	      ",SDKVersion:" + android.os.Build.VERSION.SDK +   
		    	      ",SYSVersion:" + android.os.Build.VERSION.RELEASE
		    	      + ",Brand:" + android.os.Build.BRAND
		    	      + ",SimProvider:" + tm.getSimOperator()
		    	      + ",NetWork:" + network
		    	      ;
		    
		    Log.i(Jni.LOG_TAG, "-------HandSetInfo:" + handSetInfo);
		    return handSetInfo; 
		} catch (Exception e) {
		//	Tracker.reportException(Jni.getGameActivity(), e);
		}
		return "";
	}
	
	public static String getStartType() {//mf add
		try {
		    Log.i(Jni.LOG_TAG, "-------getStartType:" + startType);
		    return startType; 
		} catch (Exception e) {
	//		Tracker.reportException(Jni.getGameActivity(), e);
		}
		return "";
	}
    
    public static String getGotoType() {
        try {
            Log.i(Jni.LOG_TAG, "-------getGotoType:" + gotoType);
            return gotoType;
        } catch (Exception e) {
            //		Tracker.reportException(Jni.getGameActivity(), e);
        }
        return "";
    }
	
	public static String getVersionName() {
		try {
			String pName = Jni.getGameActivity().getPackageName();
			PackageInfo pinfo = null;
			pinfo = Jni.getGameActivity().getPackageManager()
					.getPackageInfo(pName, PackageManager.GET_CONFIGURATIONS);
			String versionName = pinfo.versionName;
			Log.i(Jni.LOG_TAG, "-------versionName:" + versionName);
			return versionName;
		} catch (Exception e) {
	//		Tracker.reportException(Jni.getGameActivity(), e);
		}
		return "";
	}

	public static String getVersionCode() {
		try {
			String pName = Jni.getGameActivity().getPackageName();
			PackageInfo pinfo = null;
			pinfo = Jni.getGameActivity().getPackageManager()
					.getPackageInfo(pName, PackageManager.GET_CONFIGURATIONS);
			int versionCode = pinfo.versionCode;
			Log.i(Jni.LOG_TAG, "-------versionCode:" + versionCode);
			return String.valueOf(versionCode);
		} catch (Exception e) {
		//	Tracker.reportException(Jni.getGameActivity(), e);
		}
		return "";
	}
	
	public static String getAccountInfo()
	{
		AccountManager accountManager = AccountManager.get(_context);
		Account[] accounts = accountManager.getAccountsByType("com.google");
		for(Account account : accounts)
		{
			return account.name;
		}
		return "";
	}

	public static String getUid() {
		String deviceId = Udid.getUid();
		String loginUserId = GameContext.getGamePublisher().getLoginUserId();
		if(StringUtils.isNotBlank(loginUserId)){
			return loginUserId;
		}
		return deviceId;
	}

	public static String getStaticUid(){
		return Udid.getSUid();
	}

	public static String getAllAccountInfo()
	{
		return Udid.getAccountManagerInfo();
	}
	
	public static String getChannel(){
		return "Android";
	}
	public static boolean hasEnoughSpace(int needSize) {
		Log.i(Jni.LOG_TAG, "-------need size:" + needSize);
		StatFs sf = new StatFs(_context.getCacheDir().getAbsolutePath());
		long freesize = sf.getAvailableBlocks() / 1024 ;
		freesize = freesize * sf.getBlockSize();
		Log.i(Jni.LOG_TAG, "-------free size:" + freesize);
		if(needSize > freesize){
			return false;
		}
		return true;
	}
}
