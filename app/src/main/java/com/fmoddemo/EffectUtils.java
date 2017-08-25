package com.fmoddemo;

/**
 * Created by liupei on 2017/8/23.
 */

public class EffectUtils {

    //音效的类型
    public static final int MODE_NORMAL = 0;
    public static final int MODE_LUOLI = 1;
    public static final int MODE_DASHU = 2;
    public static final int MODE_JINGSONG = 3;
    public static final int MODE_GAOGUAI = 4;
    public static final int MODE_KONGLING = 5;

    public static native void fix(String path, int type);

    public static native void stop();

    static {
        System.loadLibrary("fmod");
        System.loadLibrary("fmodL");
        System.loadLibrary("voicer");
    }
}
