#include <jni.h>
#include <android/log.h>
#include <malloc.h>
#include <string.h>
#include "gif_lib.h"
#include <android/bitmap.h>

#define TAG "JNITEST"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

typedef struct GifBean {
    int currentFrame;
    int *dealys;
    int totalFrame;
} GifBean;
extern "C"

{

JNIEXPORT jlong JNICALL
Java_cgw_gifview_com_GifPlayer_openGif(JNIEnv *env, jobject instance, jstring filePath_) {

    const char *filePath = env->GetStringUTFChars(filePath_, 0);
    int errorCode = -1;
    //打开 gif 文件
    GifFileType *gifFile = DGifOpenFileName(filePath, &errorCode);
    //如果打开文件失败 则 errorCode 会被重新赋值 则说明打开文件失败
    //所以如果android 层返回的是 -1 说明打开文件失败
    if (errorCode != -1)
        return -1;

    //初始化 gifFile
    DGifSlurp(gifFile);

    //从 gifFileTyype 取出图像数据 宽高、帧数、每帧延迟时间等等 然后用一个结构体封装起来
    GifBean *gifBean = (GifBean *) malloc(sizeof(GifBean));
    memset(gifBean, 0, sizeof(GifBean));
    gifBean->totalFrame = gifFile->ImageCount;
//
//    /* gif 文件相关
//    * 颜色值：
//    * gif 文件的所有帧数据存放在 GifFileType 的 SaveImage 结构体中（SaveImage 是一个数组 存放每一帧图片的数据）
//    * SaveImage 中的变量 RasterBits（结构体 GifByteType）rgb颜色值栅格化后的 byte 数据
//    * SaveImage 中的变量 ImageDesc（结构体 GifImageDesc） 保存了图片的像素点的开始位置 （）
//    *                    ImageDesc 中的变量 ColorMap（结构体 ColorMapObject）存放了每一帧颜色值相关数据 。
//    *                                       ColorMap 里面的 Colors（结构体 GifColorType）存放的就是具体的 rgb颜色值
//    *ColorMap 是存放具体 rgb 颜色值所以要从 ColorMap 里面取数据它的 key 就是栅格化后的 byte 数据 即 RasterBits
//    *
//            *每帧间隔时间：
//    * 时间间隔存放在图形扩展块中
//    *SaveImage 中的变量 ExtensionBlockCount 存放的就是几种扩展相关信息
//    *                   ExtensionBlockCount 中变量 Function 表示的是当前扩展块存放的是什么信息
//    * 而存放 间隔时间的扩展快 Function 的值是 GRAPHICS_EXT_FUNC_CODE
//                                * /
//

    //每一帧延迟时间分配空间
    gifBean->dealys = (int *) malloc(sizeof(int) * gifBean->totalFrame);
    memset(gifBean->dealys, 0, sizeof(int) * gifBean->totalFrame);

    //求每一帧的延迟时间
    ExtensionBlock *block;
    for (int i = 0; i < gifFile->ImageCount; ++i) {
        //循环取出每一帧
        SavedImage savedImage = gifFile->SavedImages[i];
        for (int j = 0; j < savedImage.ExtensionBlockCount; ++j) {
            //匹配图形扩展块
            if (savedImage.ExtensionBlocks[j].Function == GRAPHICS_EXT_FUNC_CODE) {
                block = &savedImage.ExtensionBlocks[j];
                break;
            }
        }
        //算出每一帧的延迟时间 放到 dealys数组中
        if (block) {
            // ExtensionBlock 里的第2、3个字节存放的是时间数据
            int frame_delay = 10 * (block->Bytes[2] << 8 | block->Bytes[1]);
            gifBean->dealys[i] = frame_delay;
        }
    };
    //释放指针
    env->ReleaseStringUTFChars(filePath_, filePath);
    return (jlong) gifFile;
}


JNIEXPORT void JNICALL
Java_cgw_gifview_com_GifPlayer_draw(JNIEnv *env, jclass type,jlong giffile,jobject bitmap) {

    //拿出 gifbean
    GifFileType *gifFileType = (GifFileType *) giffile;
    GifBean *gifBean = (GifBean *) gifFileType->UserData;

    //获取当前帧
    SavedImage savedImage = gifFileType->SavedImages[gifBean->currentFrame];
    //从 savedImage 取出图片相关信息
    GifImageDesc desc = savedImage.ImageDesc;




    //从 savedImage 取出栅格化的颜色数据
    GifByteType *rasterBits  = savedImage.RasterBits;









    //解析出像素数组  一幅图片--》二维 像素数组
    void *pixels;//入参出参变量
    AndroidBitmap_lockPixels(env, bitmap, &pixels);




}


JNIEXPORT jint JNICALL
Java_cgw_gifview_com_GifPlayer_getWidth(JNIEnv *env, jclass type, jlong gifFile) {
    GifFileType *gifFileType = (GifFileType *) gifFile;
    return gifFileType->SWidth;

}
JNIEXPORT jint JNICALL
Java_cgw_gifview_com_GifPlayer_getHeight(JNIEnv *env, jclass type, jlong gifFile) {
    GifFileType *gifFileType = (GifFileType *) gifFile;
    return gifFileType->SHeight;

}

}

