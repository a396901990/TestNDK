package com.dean.testndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    // 导入动态库
    static {
        System.loadLibrary("test");
    }

    // 本地排序方法
    public native boolean doSort(int [] array);

    private Button mOrderBtn;
    private TextView mResultText;

    // 需要排序的数组
    int[] orderArrays = {6,2,5,9,1,3,4,7,8,0,10};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 调用jni调用静态方法返回一个字符串(hello world?)
        Log.d("TestNDK", JNIHelper.getStringFromNative());

        mResultText = (TextView) this.findViewById(R.id.result);
        setResultText(orderArrays);

        mOrderBtn = (Button) this.findViewById(R.id.plus_btn);
        mOrderBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 调用本地排序方法, 根据是否有异常打印success/failed
                boolean isSuccess = doSort(orderArrays);
                mOrderBtn.setText(isSuccess?"success":"failed");
            }
        });

    }

    public void setResultText(String resultText) {
        mResultText.setText(resultText);
    }

    public void setResultText(int[] array) {
        mResultText.setText(Arrays.toString(array));
    }

}
