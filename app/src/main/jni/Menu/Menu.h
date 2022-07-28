bool iconValid, settingsValid, initValid;

//Big letter cause crash
void setText(JNIEnv *env, jobject obj, const char* text){
    //https://stackoverflow.com/a/33627640/3763113
    //A little JNI calls here. You really really need a great knowledge if you want to play with JNI stuff
    //Html.fromHtml("");
    jclass html = (*env).FindClass(OBFUSCATE("android/text/Html"));
    jmethodID fromHtml = (*env).GetStaticMethodID(html, OBFUSCATE("fromHtml"), OBFUSCATE("(Ljava/lang/String;)Landroid/text/Spanned;"));

    //setText("");
    jclass textView = (*env).FindClass(OBFUSCATE("android/widget/TextView"));
    jmethodID setText = (*env).GetMethodID(textView, OBFUSCATE("setText"), OBFUSCATE("(Ljava/lang/CharSequence;)V"));

    //Java string
    jstring jstr = (*env).NewStringUTF(text);
    (*env).CallVoidMethod(obj, setText,  (*env).CallStaticObjectMethod(html, fromHtml, jstr));
}

jstring Icon(JNIEnv *env, jobject thiz) {
    iconValid = true;

    //Use https://www.base64encode.org/ to encode your image to base64
    return env->NewStringUTF("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");
 }


jstring IconWebViewData(JNIEnv *env, jobject thiz) {
    iconValid = true;
    //WebView support GIF animation. Upload your image or GIF on imgur.com or other sites

    // From internet (Requires android.permission.INTERNET)
    // return env->NewStringUTF(OBFUSCATE("https://i.imgur.com/SujJ85j.gif"));

    // Base64 html:
    // return env->NewStringUTF("data:image/png;base64, <encoded base64 here>");

    // To disable it, return NULL. It will use normal image above:
    // return NULL

    //return env->NewStringUTF(OBFUSCATE_KEY("https://i.imgur.com/SujJ85j.gif", 'u'));
    return NULL;
}

jobjectArray SettingsList(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_Settings"),
            OBFUSCATE("RedAlert_Made By Nepmods"),
            OBFUSCATE("-1_Toggle_Save feature preferences"), //-1 is checked on Preferences.java
            OBFUSCATE("-3_Toggle_Auto size vertically"),
            OBFUSCATE("Category_Menu"),
            OBFUSCATE("-6_Button_<font color='red'>Close</font>"),
    };

    int Total_Feature = (sizeof features /
                         sizeof features[0]); //Now you dont have to manually update the number everytime;
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    settingsValid = true;

    return (ret);
}
