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

    private Button orderBtn;
    private TextView resultText;
    private JNIHelper jniHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniHelper = new JNIHelper();

        resultText = (TextView) this.findViewById(R.id.result);
        resultText.setText("test");

        orderBtn = (Button) this.findViewById(R.id.order_btn);
        orderBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[] a = {6,2,5,9,1,3,4,6,8,0};
                jniHelper.doOrder(a);
            }
        });
    }
}
