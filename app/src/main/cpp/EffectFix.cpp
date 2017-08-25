//
// Created by liupei on 2017/8/23.
//

#include <stdlib.h>
#include "EffectFix.h"
#include "fmod/fmod.hpp"

#include <android/log.h>
#include <unistd.h>

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"tag",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"tag",FORMAT,##__VA_ARGS__);

FMOD::Sound *sound = NULL;
FMOD::System *sys;

JNIEXPORT void JNICALL Java_com_fmoddemo_EffectUtils_stop(JNIEnv *env, jclass type) {
    if (sound != NULL) {
        sound->release();
    }
    if (sys != NULL) {
        sys->close();
        sys->release();
    }
}

JNIEXPORT void JNICALL
Java_com_fmoddemo_EffectUtils_fix(JNIEnv *env, jclass jcl, jstring path_str, jint type) {
    FMOD::System_Create(&sys);
    FMOD::Channel *channel = NULL;
    FMOD::DSP *dsp;
    bool playing = true;
    float frequency = 0;
    sys->init(32, FMOD_INIT_NORMAL, NULL);
    const char *path = env->GetStringUTFChars(path_str, NULL);
    sys->createSound(path, FMOD_DEFAULT, 0, &sound);
    switch (type) {
        case MODE_NORMAL:
            //原声播放
            sys->playSound(sound, 0, false, &channel);
            LOGE("%s", path);
            break;
        case MODE_LUOLI:
            //萝莉
            //DSP digital signal process
            //dsp -> 音效 创建fmod中预定义好的音效
            //FMOD_DSP_TYPE_PITCHSHIFT dsp，提升或者降低音调用的一种音效
            sys->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            //设置音调的参数
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.5);

            sys->playSound(sound, 0, false, &channel);
            //添加到channel
            channel->addDSP(0, dsp);
            LOGI("%s", "fix luoli");
            break;

        case MODE_JINGSONG:
            //惊悚
            sys->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);
            sys->playSound(sound, 0, false, &channel);
            channel->addDSP(0, dsp);

            break;
        case MODE_DASHU:
            //大叔
            sys->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);

            sys->playSound(sound, 0, false, &channel);
            //添加到channel
            channel->addDSP(0, dsp);
            LOGI("%s", "fix dashu");
            break;
        case MODE_GAOGUAI:
            //搞怪
            //提高说话的速度
            sys->playSound(sound, 0, false, &channel);
            channel->getFrequency(&frequency);
            frequency = frequency * 1.6;
            channel->setFrequency(frequency);
            LOGI("%s", "fix gaoguai");
            break;
        case MODE_KONGLING:
            //空灵
            sys->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
            sys->playSound(sound, 0, false, &channel);
            channel->addDSP(0, dsp);
            LOGI("%s", "fix kongling");
            break;
        default:
            break;
    }
    sys->update();

    while (playing) {
        channel->isPlaying(&playing);
        usleep(1000 * 1000);
    }
    goto end;

    end:
    env->ReleaseStringUTFChars(path_str, path);
}