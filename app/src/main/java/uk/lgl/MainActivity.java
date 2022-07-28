package uk.lgl;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.content.Context;
import uk.lgl.modmenu.CrashHandler;
import uk.lgl.modmenu.Menu;
import java.io.File;
import java.io.FileOutputStream;
import android.util.Base64;
import Nepmods.Tester.R;

public class MainActivity extends Activity {
    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("MyLibName");
    }
    //Only if you have changed MainActivity to yours and you wanna call game's activity.
    public String GameActivity = "com.unity3d.player.UnityPlayerActivity";
    public boolean hasLaunched = false;
    public static String cacheDir;
    
    //To call onCreate, please refer to README.md
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        

        //To launch game activity
        if (!hasLaunched) {
            try {
                //Start service
                hasLaunched = true;
                //Launch mod menu.
                MainActivity.this.startActivity(new Intent(MainActivity.this, Class.forName(MainActivity.this.GameActivity)));
                Start(MainActivity.this);
                return;
            } catch (ClassNotFoundException e) {
                Log.e("Mod_menu", "Error. Game's main activity does not exist");
                //Uncomment this if you are following METHOD 2 to launch menu
                //Toast.makeText(MainActivity.this, "Error. Game's main activity does not exist", Toast.LENGTH_LONG).show();
            }
        }
        Start(this);
        }

        //Launch mod menu.
       // Main.StartWithoutPermission(this);
        
        
    private static native void CheckOverlayPermission(Context context);

    public static void StartWithoutPermission(Context context) {
        CrashHandler.init(context, true);
        if (context instanceof Activity) {
            //Check if context is an Activity.
            Menu menu = new Menu(context);
            menu.SetWindowManagerActivity();
            menu.ShowMenu();
        } else {
            //Anything else, ask for permission
            CheckOverlayPermission(context);
        }
    }

    public static void Start(Context context) {
        CrashHandler.init(context, false);
        cacheDir = context.getCacheDir().getPath() + "/";

        writeToFile("img.png", uk.lgl.modmenu.NepmodsSecurity.background());
        CheckOverlayPermission(context);
    }
        
    private static void writeToFile(String name, String base64) {
        File file = new File(cacheDir + name);
        try {
            if (!file.exists()) {
                file.createNewFile();
            }
            FileOutputStream fos = new FileOutputStream(file);
            byte[] decode = Base64.decode(base64, 0);
            fos.write(decode);
            fos.close();
        } catch (Exception e) {
            
        }
    }
}

