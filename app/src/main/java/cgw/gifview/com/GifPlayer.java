package cgw.gifview.com;

import java.net.PortUnreachableException;

/**
 * Author chen_gw
 * Date 2018/5/21 11:48
 * DES :
 */
public class GifPlayer {
    public static native long openGif(String filePath);
}
