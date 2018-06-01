#include <jni.h>
#include <android/log.h>
#include "gif_lib.h"

#define TAG "JNITEST"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
extern "C"

{

JNIEXPORT jlong JNICALL
Java_cgw_gifview_com_GifPlayer_openGif(JNIEnv *env, jobject instance, jstring filePath_) {

    const char *filePath = env->GetStringUTFChars(filePath_, 0);
    int errorCode  = -1 ;
    //打开 gif 文件
    GifFileType *gifFile =DGifOpenFileName(filePath,&errorCode);
    //如果打开文件失败 则 errorCode 会被重新赋值 则说明打开文件失败
    //所以如果android 层返回的是 -1 说明打开文件失败
    if ( errorCode != -1)
        return -1 ;

    //初始化 gifFile
    DGifSlurp(gifFile);




    return 0 ;
}




}