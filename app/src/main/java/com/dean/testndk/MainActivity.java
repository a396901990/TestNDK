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

    public native void doSort(int [] array);

    private Button mPlusBtn;
    private TextView mResultText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.i("ndk_log : ", JNIHelper.getStringFromNative());

        mResultText = (TextView) this.findViewById(R.id.result);
        mResultText.setText(JNIHelper.getStringFromNative());

        mPlusBtn = (Button) this.findViewById(R.id.plus_btn);
        mPlusBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                int[] a = {6,2,5,9,1,3,4,6,8,0};

                doSort(a);
            }
        });

    }

    public void setResultText(String resultText) {
        mResultText.setText(resultText);
    }

}
