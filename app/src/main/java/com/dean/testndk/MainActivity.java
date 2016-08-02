package com.dean.testndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("test");
    }

    public native void doCalcPlus();

    public native void getResult();

    private Button plusBtn;
    private TextView resultText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i("ndk_log : ", JNIHelper.getStringFromNative());

        resultText = (TextView) this.findViewById(R.id.result);
        resultText.setText(JNIHelper.getStringFromNative());

        plusBtn = (Button) this.findViewById(R.id.plus_btn);
        plusBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                doCalcPlus();
            }
        });

    }

    public void getNumberOne() {

    }

    public void getNumberTweo() {

    }
}
