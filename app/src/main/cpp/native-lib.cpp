#include <jni.h>
#include <android/log.h>
#include <malloc.h>
#include <string.h>
#include "gif_lib.h"

#define TAG "JNITEST"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

typedef struct GifBean{
    int currentFrame ;
    int *dealays ;
    int totalFrame ;
} GifBean;
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

    //从 gifFileTyype 取出图像数据 宽高、帧数、每帧延迟时间等等 然后用一个结构体封装起来
    GifBean  *gifBean = (GifBean *) malloc(sizeof(GifBean));
    memset( gifBean,0, sizeof(GifBean));
    gifBean->totalFrame = gifFile->ImageCount ;

    //每一帧延迟时间分配空间
    gifBean->dealays = (int *) malloc(sizeof(int)*gifBean->totalFrame);
    memset(gifBean->dealays,0, sizeof(int)*gifBean->totalFrame);

    //求每一帧的延迟时间

    /* gif 文件相关结构
     * 简单介绍下 gif 文件结构
     *
     *
     * 颜色值：
     * gif 文件的所有帧数据存放在 GifFileType 的 SaveImage 结构体中（SaveImage 是一个数组 存放每一帧图片的数据）
     * SaveImage 中的变量 RasterBits（结构体 GifByteType）rgb颜色值栅格化后的 byte 数据
     * SaveImage 中的变量 ImageDesc（结构体 GifImageDesc） 保存了图片的像素点的开始位置 （）
     *                    ImageDesc 中的变量 ColorMap（结构体 ColorMapObject）存放了每一帧颜色值相关数据 。
     *                                       ColorMap 里面的 Colors（结构体 GifColorType）存放的就是具体的 rgb颜色值
     *ColorMap 是存放具体 rgb 颜色值所以要从 ColorMap 里面取数据它的 key 就是栅格化后的 byte 数据 即 RasterBits
     *
     *每帧间隔时间：
     * 时间间隔存放在图形扩展中
     *SaveImage 中的变量 ExtensionBlockCount 存放的就是几种扩展相关信息
     *
     *
     * /










    return 0 ;
}




}