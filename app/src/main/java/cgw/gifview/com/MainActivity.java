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

public class MainActivity extends AppCompatActivity {



    static {
        System.loadLibrary("native-lib");
    }

    Bitmap bitmap ;
    long l ;
    ImageView iv_show ;

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

    Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            int mNextFrame= GifPlayer.draw(l,bitmap);
            iv_show.setImageBitmap(bitmap);
            handler.sendEmptyMessageDelayed(1,mNextFrame);
        }
    };

    public void staaaa() {

        File file=new File(Environment.getExternalStorageDirectory(),"Download/timg-2.gif");
        if (!file.exists())return;
        l = GifPlayer.openGif(file.getAbsolutePath());

        int width = GifPlayer.getWidth(l);
        int height = GifPlayer.getHeight(l);
        Log.e("ttt", " w -h "+width + "---"+height);

        bitmap= Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        int draw = GifPlayer.draw(l, bitmap);
        iv_show.setImageBitmap(bitmap);
        Log.e("ttt", " draw back "+draw);
        handler.sendEmptyMessageDelayed(1,draw);
    }
}
