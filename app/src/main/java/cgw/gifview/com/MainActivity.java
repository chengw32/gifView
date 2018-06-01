package cgw.gifview.com;

import android.nfc.Tag;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {



    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        File file=new File(Environment.getExternalStorageDirectory(),"Download/timg.gif");
        if (!file.exists())return;
        long l = GifPlayer.openGif(file.getAbsolutePath());
        Log.e("tttt---",""+l);

    }

}
