package cgw.gifview.com;

import android.graphics.Bitmap;
import android.media.Image;
import android.nfc.Tag;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib");
    }

    Bitmap bitmap;
    long l;
    ImageView iv_show;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        iv_show = findViewById(R.id.iv_show);
        findViewById(R.id.sample_text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                staaaa();
            }
        });
    }

    private File getAssetsFile(String fileName) {
        try {
            InputStream is = getAssets().open(fileName);
            FileOutputStream fos = null;
//创建文件名
            File file = new File(Environment.getExternalStorageDirectory(), "t");
            if (!file.exists()) {
                file.createNewFile();
            }
            // 打开一个已存在文件的输出流
            fos = new FileOutputStream(file);
            // 将输入流is写入文件输出流fos中
            int ch = 0;
            try {
                while ((ch = is.read()) != -1) {
                    fos.write(ch);
                }
                return file;
            } catch (IOException e1) {
                e1.printStackTrace();
            } finally {
                //关闭输入流等
                fos.close();
                is.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            int mNextFrame = GifPlayer.draw(l, bitmap);
            iv_show.setImageBitmap(bitmap);
            handler.sendEmptyMessageDelayed(1, mNextFrame);
        }
    };

    public void staaaa() {


        File file = getAssetsFile("test.gif");
        if (!file.exists()) return;
        l = GifPlayer.openGif(file.getAbsolutePath());

        int width = GifPlayer.getWidth(l);
        int height = GifPlayer.getHeight(l);

        bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        int draw = GifPlayer.draw(l, bitmap);
        iv_show.setImageBitmap(bitmap);
        handler.sendEmptyMessageDelayed(1, draw);
    }
}
