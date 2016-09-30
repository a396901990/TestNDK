#include <string>
#include "CCDevice.h"
#include "CCTypesExt.h"
#include "CCSafeNotificationCenter.h"
#include "SimpleCommand.h"

#include "BASHA1.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <spine/Json.h>
#endif  // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

using namespace std;

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

string g_theBranchLinkData("");
string g_theBranchLinkUrl("");
int    g_nFBLikeResult = -1;

string _package_name("");
string _package_sign("");

NS_CC_EXT_BEGIN

string CCDevice::base64DEcode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}


string CCDevice::getPackageName() {
    return _package_name;
}

string CCDevice::getPackageSign() {
    return _package_sign;
}



void CCDevice::testNetworkAndSendToHelpshift(std::string strUser, std::string strHost)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "testNetwork", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        CCLOGFUNC("jni: no testNetwork method");
        return;
    }
    jstring jtag=minfo.env->NewStringUTF(strUser.c_str());
    jstring jmsg=minfo.env->NewStringUTF(strHost.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jtag, jmsg);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(jtag);
    minfo.env->DeleteLocalRef(jmsg);
#endif
}

void CCDevice::sendTraceLogToHelpshift(std::string tag, std::string msg)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "sendTraceLogToHelpshift", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        CCLOGFUNC("jni: no sendTraceLogToHelpshift method");
        return;
    }
    jstring jtag=minfo.env->NewStringUTF(tag.c_str());
    jstring jmsg=minfo.env->NewStringUTF(msg.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jtag, jmsg);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(jtag);
    minfo.env->DeleteLocalRef(jmsg);
#endif
}

int CCDevice::getNetworkStatus()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo minfo;
    if(cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                               "org/hcg/IF/IF",
                                               "getNetWorkType",
                                               "()I"))
    {
        return minfo.env->CallStaticIntMethod(minfo.classID,
                                                  minfo.methodID);
    }
    
#endif
    return 0;
}

void CCDevice::initAppsFlyer()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "firstOpenAppsflyer", "()V")) {
        CCLOGFUNC("jni: no testNetwork method");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::clearApplicationData()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "clearApplicationData", "()V")) {
        CCLOGFUNC("jni: no testNetwork method");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::getPingResult(std::string strHost)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "getPingResult", "(Ljava/lang/String;)V")) {
        CCLOGFUNC("jni: no testNetwork method");
        return;
    }
    jstring jhost=minfo.env->NewStringUTF(strHost.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jhost);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(jhost);
#endif
}

void CCDevice::rateApp()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "com/elextech/ccgoe/RateUtil", "rate", "()V") ) {
        CCLOG("jni: no method");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif  // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
}

string CCDevice::getDeviceModel()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/lib/Cocos2dxHelper", "getDeviceModel", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "unknown";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "unknown";
#endif
}

string CCDevice::getCountry() {
    static string ret;
    if (!ret.empty())
        return ret;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getCountry", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
    return "CN";
#endif
}

string CCDevice::getLanguage()
{
    static string ret;
    if (!ret.empty())
        return ret;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getLanguage", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "zh";
#endif
}

string CCDevice::getChannel()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getChannel", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "unimplemented";
#endif
}

string CCDevice::getDeviceUid()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getUid", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "unimplemented";
#endif
}

string CCDevice::getOldDeviceId()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getStaticUid", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    CCLOG("xzz getOldDeviceId == %s",ret.c_str());
    return ret;
#else
    return "";
#endif
}

string CCDevice::getAllAccountInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getAllAccountInfo", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    CCLOG("xzz getAllAccountInfo == %s",ret.c_str());
    return ret;
#else
    return "";
#endif
}



string CCDevice::base64Encode(const std::string &str){
//    return "";
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    int in_len = str.length();
    char const* bytes_to_encode = str.c_str();

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
            ret += '=';

    }

    return ret;
}

string CCDevice::getOSVersion()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getOSVersion", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    string _ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(retFromJava);
    // add "Android" prefix
    string ret = "Android";
    ret.append(_ret);
    return ret;
#else
	return "unknown";
#endif
}

void CCDevice::sendMail(const string &address,const string &title,const string &content)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "sendMail", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
    jstring jaddress=minfo.env->NewStringUTF(address.c_str());
    jstring jtitle=minfo.env->NewStringUTF(title.c_str());
    jstring jcontent=minfo.env->NewStringUTF(content.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jaddress,jtitle,jcontent);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(jaddress);
    minfo.env->DeleteLocalRef(jtitle);
    minfo.env->DeleteLocalRef(jcontent);
#else
#endif
}

string CCDevice::getVersionName()
{
    static string ret;
    if (!ret.empty())
        return ret;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getVersionName", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "unimplemented";
#endif
}

string CCDevice::getHandSetInfo()
{
    static string ret;
    if (!ret.empty())
        return ret;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getHandSetInfo", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "unimplemented";
#endif
}

string CCDevice::getVersionCode()
{
    static string ret;
    if (!ret.empty())
        return ret;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getVersionCode", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
	return "unimplemented";
#endif
}

void CCDevice::openURL(const string &url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "showWebView", "(Ljava/lang/String;)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    jstring jevent=minfo.env->NewStringUTF(url.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jevent);
    minfo.env->DeleteLocalRef(jevent);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

string CCDevice::clipboardGetText()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "clipboardGetText", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }

    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
    return "";
#endif
}

void CCDevice::clipboardSetText(const string &text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "clipboardSetText", "(Ljava/lang/String;)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    jstring jevent=minfo.env->NewStringUTF(text.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jevent);
    minfo.env->DeleteLocalRef(jevent);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::updateVersion(const std::string &msg, const std::string &urlCDN)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //1. 获取activity静态对象
    JniMethodInfo minfo;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    jobject activityObj;
    if(JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/ext/CppCallJava","gotoMarket","(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring jurl = minfo.env->NewStringUTF(msg.c_str());
        jstring jurlCDN = minfo.env->NewStringUTF(urlCDN.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jurl, jurlCDN);
        minfo.env->DeleteLocalRef(jurl);
        minfo.env->DeleteLocalRef(jurlCDN);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

string CCDevice::getAccountInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getAccountInfo", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }

    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
    return "";
#endif
}

void CCDevice::pushNotice(int type,int time, std::string body,std::string soundKey,std::string pushType)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "pushNotification", "(IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    jstring jbody=minfo.env->NewStringUTF(body.c_str());
    jstring jsoundKey=minfo.env->NewStringUTF(soundKey.c_str());
    jstring jpushType=minfo.env->NewStringUTF(pushType.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, type, time, jbody, jsoundKey, jpushType);
    minfo.env->DeleteLocalRef(jbody);
    minfo.env->DeleteLocalRef(jsoundKey);
    minfo.env->DeleteLocalRef(jpushType);
    minfo.env->DeleteLocalRef(minfo.classID);
}

//void CCDevice::pushNoticeAddPos(int type,int pos,int time, std::string body,std::string soundKey)
//{
//    pushNotice(type, time, body, soundKey);

//    JniMethodInfo minfo;
//    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "pushNotificationAddPos", "(IIILjava/lang/String;Ljava/lang/String;)V") ) {
//        CCLOGFUNC("jni: no method");
//        return;
//    }
//
//    jstring jbody=minfo.env->NewStringUTF(body.c_str());
//    jstring jsoundKey=minfo.env->NewStringUTF(soundKey.c_str());
//    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, type, time, pos, jbody, jsoundKey);
//    minfo.env->DeleteLocalRef(jbody);
//    minfo.env->DeleteLocalRef(jsoundKey);
//    minfo.env->DeleteLocalRef(minfo.classID);
//}

void CCDevice::cancelNotice(int type)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "cancelNotification", "(I)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, type);
    minfo.env->DeleteLocalRef(minfo.classID);
}

string CCDevice::getPushRecordData(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "getPushRecordData", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#endif
}

string CCDevice::getPushTypeData(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "getPushTypeData", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#endif
}

void CCDevice::setPushTypeData(const string &pushTypeData)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "setPushTypeData", "(Ljava/lang/String;)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }
    jstring jpushTypeData=minfo.env->NewStringUTF(pushTypeData.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jpushTypeData);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(jpushTypeData);
}

string CCDevice::getGotoType(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getGotoType", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
    return "";
#endif
}

void CCDevice::setGotoType(const string &gotoType)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "setGotoType", "(Ljava/lang/String;)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }
    jstring jGotoType=minfo.env->NewStringUTF(gotoType.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jGotoType);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(jGotoType);
}

string CCDevice::getPushClickData(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "getPushClickData", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#endif
}

void CCDevice::clearPushCache(){
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "clearPushCache", "()V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void CCDevice::finishGame(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "finishGame", "()V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

string CCDevice::getStartType()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "getStartType", "()Ljava/lang/String;") ) {
        CCLOGFUNC("jni: no method");
        return "";
    }

    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);
    return ret;
#else
    return "";
#endif
}

//void CCDevice::setTestinUser(std::string userInfo)
//{
//    JniMethodInfo minfo;
//    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "setTestinUser", "(Ljava/lang/String;)V") ) {
//        CCLOGFUNC("jni: no method");
//        return;
//    }
//
//    jstring juserInfo=minfo.env->NewStringUTF(userInfo.c_str());
//    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, juserInfo);
//    minfo.env->DeleteLocalRef(minfo.classID);
//}

void CCDevice::doPlatformLogin(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "com/clash/of/jni/Jni", "doPlatformLogin", "()V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::doPlatformQuit(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "com/clash/of/jni/Jni", "doPlatformQuit", "()V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::doPlatformCollectUserInfo(const string &userId,const string &userName,const string &userLevel){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "doSetHelpShiftUserInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
    jstring juserId=minfo.env->NewStringUTF(userId.c_str());
    jstring juserName=minfo.env->NewStringUTF(userName.c_str());
    jstring juserLevel=minfo.env->NewStringUTF(userLevel.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,juserId,juserName,juserLevel);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(juserId);
    minfo.env->DeleteLocalRef(juserName);
    minfo.env->DeleteLocalRef(juserLevel);
#else
#endif
}

void CCDevice::GooglePlusLogin(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "com/clash/of/util/MyGooglePlusUtil", "GooglePlusLogin", "()V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::GooglePlusLogout(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "com/clash/of/util/MyGooglePlusUtil", "GooglePlusLogout", "()V")) {
        CCLOGFUNC("jni: no method");
        return;
    }
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

bool CCDevice::GooglePlusIsLogin(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "com/clash/of/util/MyGooglePlusUtil", "GooglePlusIsLogin", "()Z")) {
        CCLOGFUNC("jni: no method");
        return false;
    }
	jboolean isLogin =  minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
	minfo.env->DeleteLocalRef(minfo.classID);
    if(isLogin){
        CCLOG("google login sucess!");
        return true;
    }
    CCLOG("google login fail!");
    return false;
#endif
}

string CCDevice::getPublishRegion()
{
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "getPublishRegion", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }

    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);

    CCLOG("<<<<<<<<<<< publish Region = [%s] >>>>>>>>>>>", ret.c_str());

    return ret;

}

void CCDevice::login_Platform(int platform)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "login_Platform", "(I)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, platform);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void CCDevice::login_Platform_InChildThread(int platform)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "login_Platform_InChildThread", "(I)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, platform);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void CCDevice::logout_Platform(int platform)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "logout_Platform", "(I)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }

    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, platform);
    minfo.env->DeleteLocalRef(minfo.classID);
}

bool CCDevice::isAvailable_Platform(int platform)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "isAvailable_Platform", "(I)Z") ) {
        CCLOGFUNC("jni: no method");
        return false;
    }

    jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,platform);
    minfo.env->DeleteLocalRef(minfo.classID);
    return ret;

}
bool CCDevice::isHaveGetAccountsPermission(int platform)
{
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "isHaveAccountsPermission", "(I)Z") ) {
        CCLOGFUNC("jni: no method");
        return false;
    }

    jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,platform);
    minfo.env->DeleteLocalRef(minfo.classID);
    return ret;

}
bool CCDevice::isConnected_Platform(int platform)
{
    CCLOG("call isConnected_Platform:%d",platform);

    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "isConnected_Platform", "(I)Z") ) {
        CCLOGFUNC("jni: no method");
        return false;
    }

    jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,platform);
    minfo.env->DeleteLocalRef(minfo.classID);
    if (ret) {
        CCLOG("isConnected_Platform:true");
    }else{
        CCLOG("isConnected_Platform:false");
    }

    return ret;

}

cocos2d::CCDictionary* CCDevice::getLoginedInfo_Platform(int platform){
    CCLOG("getLoginedInfo_Platform :%d", platform);

    cocos2d::CCDictionary* dict = cocos2d::CCDictionary::create();
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "getLoginedInfo_Platform", "(I)Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return dict;
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,platform);
    minfo.env->DeleteLocalRef(minfo.classID);
    string jsonStr=JniHelper::jstring2string(retFromJava);
    CCLOG("getLoginedInfo_Platform jsonStr :%s", jsonStr.c_str());
    minfo.env->DeleteLocalRef(retFromJava);

    Json *jsonObj = Json_create(jsonStr.c_str());
    if( !jsonObj )
        return dict;

    string _is_connect=Json_getString(jsonObj, "is_connect", "");
    string _userName=Json_getString(jsonObj, "userName", "");
    string _userId=Json_getString(jsonObj, "userId", "");
    Json_dispose(jsonObj);
//    Json::Value jsonObj;
//    Json::Reader reader;
//    reader.parse(jsonStr, jsonObj);
    if (_userName != ""){//有数据
//        string  userName=jsonObj["userName"].asCString();
        dict->setObject(CCString::create(_userName),"userName");
    }
    if (_userId != ""){//有数据
//        string  userId=jsonObj["userId"].asCString();
        dict->setObject(CCString::create(_userId),"userId");
    }
    if (_is_connect != ""){//有数据
//        bool is_connect  =jsonObj["is_connect"].asBool();
        dict->setObject(CCString::create(_is_connect),"is_connect");
    }

    return dict;

}
bool CCDevice::hasEnoughSpace(int needSize)
{
    CCLOG("device need space:%d",needSize);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/Device", "hasEnoughSpace", "(I)Z") ) {
        CCLOGFUNC("jni: no method");
        return false;
    }

    jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,needSize);
    minfo.env->DeleteLocalRef(minfo.classID);
    return ret;
#endif
    return false;
}

void CCDevice::onUploadPhoto(int uid, int srcCode, int idx)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "onUploadPhoto", "(III)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }
    jint juid = (jint)uid;
    jint jsrcCode = (jint)srcCode;
    jint jidx = (jint)idx;

    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, juid, jsrcCode,jidx);
    minfo.env->DeleteLocalRef(minfo.classID);

#endif
}

std::string CCDevice::getSDcardPath()
{
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "getSDcardPath", "()Ljava/lang/String;")) {
        CCLOGFUNC("jni: no method");
        return "";
    }

    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    string ret=JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(retFromJava);

    CCLOG("<<<<<<<<<<< publish Region = [%s] >>>>>>>>>>>", ret.c_str());

    return ret;
}

void CCDevice::sendEvent(std::string code) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/IF/Jni", "sendEvent", "(Ljava/lang/String;)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }
    jstring jcode=minfo.env->NewStringUTF(code.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jcode);
    minfo.env->DeleteLocalRef(jcode);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void CCDevice::createBranchLinkUrl(std::string json)
{
    CCLog("call android.createBranchLinkUrl");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava", "createBranchLinkUrl", "(Ljava/lang/String;)V")) {
        CCLog("jni: no method - CppCallJava.createBranchLinkUrl");
        return;
    }
    CCLog("call jni method - CppCallJava.createBranchLinkUrl start");
    jstring theJson = minfo.env->NewStringUTF(json.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, theJson);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(theJson);
    CCLog("call jni method - CppCallJava.createBranchLinkUrl end");
#endif
}

bool CCDevice::isExternalStoragePermissionAvailable(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo minfo;
    if(cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                               "org/hcg/IF/IF",
                                               "isExternalStoragePermissionAvailable",
                                               "()Z"))
    {
        bool val = (bool)minfo.env->CallStaticBooleanMethod(minfo.classID,
                                                  minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
        return val;
    }
    
#endif
    return false;
}

bool CCDevice::isCameraPermissionAvailable(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo minfo;
    if(cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                               "org/hcg/IF/IF",
                                               "isCameraPermissionAvailable",
                                               "()Z"))
    {
        bool val = (bool)minfo.env->CallStaticBooleanMethod(minfo.classID,
                                                  minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
        return val;
    }
    
#endif
    return false;
}

bool CCDevice::isMycardPermissionAvailable(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo minfo;
    if(cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                               "org/hcg/IF/IF",
                                               "isMycardPermissionAvailable",
                                               "()Z"))
    {
        bool val = (bool)minfo.env->CallStaticBooleanMethod(minfo.classID,
                                                  minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
        return val;
    }
    
#endif
    return false;
}

bool CCDevice::isLimitAdTrackingEnabled(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo minfo;
    if(cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                               "org/hcg/IF/IF",
                                               "isLimitAdTrackingEnabled",
                                               "()Z"))
    {
        bool val = (bool)minfo.env->CallStaticBooleanMethod(minfo.classID,
                                                            minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
        return val;
    }
    
#endif
    return false;
}

std::string CCDevice::getEllipsisString(const std::string& src, const std::string& fontname, const float fontsize, float width) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    std::string ret;

    cocos2d::JniMethodInfo t;
    std::string signature = "(Ljava/lang/String;Ljava/lang/String;FF)Ljava/lang/String;";
    if (cocos2d::JniHelper::getStaticMethodInfo(t, "org.cocos2dx.lib.Cocos2dxBitmap", "getStringWithEllipsis", signature.c_str())) {
        jstring jstrSrc = t.env->NewStringUTF(src.c_str());
        jstring jstrFontName = t.env->NewStringUTF(fontname.c_str());
        jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jstrSrc, jstrFontName, width, fontsize);
        ret = cocos2d::JniHelper::jstring2string(jret);
        t.env->DeleteLocalRef(jstrSrc);
        t.env->DeleteLocalRef(jstrFontName);
        t.env->DeleteLocalRef(jret);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
#endif
    return "";
}

size_t CCDevice::getMemUsage() {
    cocos2d::JniMethodInfo t;
    const char* signature = "()J";
    if (cocos2d::JniHelper::getStaticMethodInfo(t, "android/os/Debug", "getNativeHeapAllocatedSize", signature)) {
        size_t ret = t.env->CallStaticLongMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        return ret;
    }
    return -1L;
}

float CCDevice::getDefaultBrightness() {
    cocos2d::JniMethodInfo t;
    const char* signature = "()F";
    if (cocos2d::JniHelper::getStaticMethodInfo(t, "org/hcg/IF/IF", "getDefaultBrightness", signature)) {
        float ret = t.env->CallStaticFloatMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        return ret;
    }
    return 1.0f;
}

void CCDevice::setBrightness(float val) {
    cocos2d::JniMethodInfo t;
    const char* signature = "(F)V";
    if (cocos2d::JniHelper::getStaticMethodInfo(t,"org/hcg/IF/IF", "setBrightness", signature)) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, val);
        t.env->DeleteLocalRef(t.classID);
        return;
    }
    return;
}

#ifdef __cplusplus
extern "C" {
#endif

   JNIEXPORT void JNICALL Java_org_hcg_IF_IF_initPackageData(JNIEnv* env, jobject thiz) {

        // this.getPackageManager()
        jclass cls = env->GetObjectClass(thiz);
        jmethodID mid = env->GetMethodID(cls, "getPackageManager", "()Landroid/content/pm/PackageManager;");
        jobject packageManager = env->CallObjectMethod(thiz, mid);

        // this.getPackageName()
        mid = env->GetMethodID(cls, "getPackageName", "()Ljava/lang/String;");
        jstring packageName = (jstring) env->CallObjectMethod(thiz, mid);

        // packageManager->getPackageInfo(packageName, GET_SIGNATURES);
        cls = env->GetObjectClass(packageManager);
        mid = env->GetMethodID(cls, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
        jint flags = 0x00000040;//GET_SIGNATURES;
        jobject packageInfo = env->CallObjectMethod(packageManager, mid, packageName, flags);

        // packageInfo->signatures
        cls = env->GetObjectClass(packageInfo);
        jfieldID fid = env->GetFieldID(cls, "signatures", "[Landroid/content/pm/Signature;");
        jobjectArray signatures = (jobjectArray)env->GetObjectField(packageInfo, fid);

        // signatures[0]
        jobject signature = env->GetObjectArrayElement(signatures, 0);

        // signature->toCharsString()
        cls = env->GetObjectClass(signature);
        mid = env->GetMethodID(cls, "toCharsString", "()Ljava/lang/String;");
        jstring theCharsString = (jstring)env->CallObjectMethod(signature, mid);

        // signature->hashCode()
        mid = env->GetMethodID(cls, "hashCode", "()I");
        int hash_code = env->CallIntMethod(signature, mid);

        char strRet[32] = {0};
        sprintf(strRet, "%x.", hash_code);
        std:string theSignCode(strRet);

        const char* theCharsStringC = env->GetStringUTFChars(theCharsString, 0 );
        theSignCode.append(theCharsStringC);
        env->ReleaseStringUTFChars(theCharsString, theCharsStringC);

        BASHA1 sha;
        sha.addBytes(theSignCode.c_str(), theSignCode.length());
        theSignCode = sha.getDigest();


        _package_name = cocos2d::JniHelper::jstring2string(packageName);
        _package_sign = theSignCode;

    }

   JNIEXPORT void JNICALL Java_org_hcg_IF_IF_onGetBranchLinkData(JNIEnv* env, jobject thiz, jstring msg)
    {
        g_theBranchLinkData = cocos2d::JniHelper::jstring2string(msg);
        CCLog("theBranchLinkData: %s", g_theBranchLinkData.c_str());
        if(g_theBranchLinkData.size() <= 250) {
            CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("BranchLinkData");
            CCUserDefault::sharedUserDefault()->setStringForKey("BranchLinkData", g_theBranchLinkData.c_str());
            CCUserDefault::sharedUserDefault()->flush();
        }
    }

   JNIEXPORT void JNICALL Java_org_hcg_IF_IF_nativeNetworkAvailable(JNIEnv* env, jobject thiz) {
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("NetworkAvailable");
        CCLog("Network state available posted !");
    }

   JNIEXPORT void JNICALL Java_org_cocos2dx_ext_CppCallJava_onBranchLinkUrlCreated(JNIEnv* env, jobject thiz, jstring url)
    {
        g_theBranchLinkUrl = cocos2d::JniHelper::jstring2string(url);
        CCLog("[0]theBranchLinkUrl: %s", g_theBranchLinkUrl.c_str());
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("BranchLinkUrl");
    }

    // status (0, Success; 1, fail; 2: cancel; -1: error)
   JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_FBLikeResult(JNIEnv* env, jobject thiz, jint status) {
        CCLog("FBLikeResult: %d", status);
        g_nFBLikeResult = status;
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("FBLikeResult");
    }

#ifdef __cplusplus
}
#endif


NS_CC_EXT_END
