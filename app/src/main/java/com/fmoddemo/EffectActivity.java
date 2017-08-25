package com.fmoddemo;

import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import org.fmod.FMOD;

import java.io.File;

/**
 * Created by liupei on 2017/8/23.
 */

public class EffectActivity extends AppCompatActivity implements Runnable {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        FMOD.init(this);
        Thread thread = new Thread(this);
        thread.start();
    }

    public void mFix(View btn) {
        final String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "record.wav";
        EffectUtils.stop();
        switch (btn.getId()) {
            case R.id.btn_normal:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        EffectUtils.fix(path, EffectUtils.MODE_NORMAL);
                    }
                }).start();
                break;

            case R.id.btn_luoli:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        EffectUtils.fix(path, EffectUtils.MODE_LUOLI);
                    }
                }).start();
                break;

            case R.id.btn_dashu:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        EffectUtils.fix(path, EffectUtils.MODE_DASHU);
                    }
                }).start();
                break;

            case R.id.btn_jingsong:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        EffectUtils.fix(path, EffectUtils.MODE_JINGSONG);
                    }
                }).start();
                break;

            case R.id.btn_gaoguai:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        EffectUtils.fix(path, EffectUtils.MODE_GAOGUAI);
                    }
                }).start();
                break;

            case R.id.btn_kongling:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        EffectUtils.fix(path, EffectUtils.MODE_KONGLING);
                    }
                }).start();
                break;

            default:
                break;
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    @Override
    public void run() {

    }
}
