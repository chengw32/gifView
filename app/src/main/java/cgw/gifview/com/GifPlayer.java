package cgw.gifview.com;

import android.graphics.Bitmap;

import java.net.PortUnreachableException;

/**
 * Author chen_gw
 * Date 2018/5/21 11:48
 * DES :
 */
public class GifPlayer {
    public static native long openGif(String filePath);
    public static native void draw(long gifFile,Bitmap bitmap);
    public static native int getWidth(long gifFile);
    public static native int getHeight(long gifFile);
}
