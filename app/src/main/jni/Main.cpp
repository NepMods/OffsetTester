#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"


//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

#include "Includes/Macros.h"

struct Hacks {
    
} Nepmods;

struct Offsets {
    
} Global;

struct Variables {
    
    //GLOBAL
    const char *libname;
    
    //HEX PATCHER
    const char *offset;
    const char *hex;
    
    int SelectedHook;
bool isFloat;
bool isInt;
bool isBool;
bool StartHook = false;
float HookFloatValue = 0.1;
bool HookBoolValue = false;
int HookIntValue = 0;
const char *offsetToHook;



//Hook Void
int SelectedVoidHook;
bool isVoidFloat;
bool isVoidInt;
bool isVoidBool;
bool StartHookVoid = false;
float HookVoidFloatValue = 0.1;
bool HookVoidBoolValue = false;
int HookVoidIntValue = 0;
const char *offsetToUpdateVoid;
const char *offsetToHookVoid;
 


//Hook Field Offset
int SelectedFieldHook;
bool isFieldFloat;
bool isFieldInt;
bool isFieldBool;
bool StartFieldHooking;
const char *fieldOffset;
float HookFieldFloatValue = 0.1;
bool HookFieldBoolValue = false;
int HookFieldIntValue = 0;
const char *offsetToUpdateField;


//Void Disable
int SelectedOption;
bool isVoidDisabled;
bool startDisable;
const char *voidOffset;

//Void Call
int SelectedCallOption;
bool CallVoid;
bool StartCalling;
const char *callOffset;
const char *updateOffset;


//Easy Patcher
int SelectedEasyTool;
int SelectedEasyInt;
int SelectedEasyFloat;
int SelectedEasyBool;

bool isSelectedBool;
bool isSelectedInt;
bool isSelectedFloat;
const char *EasyPatchOffset;

const char *HexToPatchBool;
const char *HexToPatchInt;
const char *HexToPatchFloat;

 const char *BoolTrue = "00 00 A0 E3 1E FF 2F E1";
const char *BoolFalse = "01 00 A0 E3 1E FF 2F E1";

const char *Int1 = "01 00 A0 E3 1E FF 2F E1";
const char *Int10 = "0A 00 A0 E3 1E FF 2F E1";
const char *Int50 = "37 00 A0 E3 1E FF 2F E1";
const char *Int100 = "1E FF 2F E1";
const char *Int999 = "E0 7C 80 D2 C0 03 5F D6";
const char *Int1000 = "0E 00 A0 E3 1E FF 2F E1";
const char *Int1M = "01 04 A0 E3 1E FF 2F E1";
const char *Int12M = "0E 00 A0 E3 1E FF 2F E1";

const char *Float1 = "C0 0F 43 E3 1E FF 2F E1";
const char *Float2 = "EC 0F 43 E3 1E FF 2F E1";
const char *Float40 = "20 02 44 E3 1E FF 2F E1";
const char *Float99 = "c6 02 44 e3 1e ff 2f e1";
const char *Float100 = "C8 02 44 E3 1E FF 2F E1";
const char *Float1000 = "7a 04 44 e3 1e ff 2f e1";
const char *Float2000 = "FA 04 44 E3 1E FF 2F E1";

    
} NM;


/*

     All Hook Functions Here
     
*/



float (*_HookFloat)(void *instance);
float HookFloat(void *instance) {
    if(instance != NULL) {
            if(NM.isFloat) {
        if(NM.StartHook) {
            
   
        float ReturnValue = NM.HookFloatValue;
        return ReturnValue;
        
      }
     }
   }
   return _HookFloat(instance);
 }

bool (*_HookBool)(void *instance);
bool HookBool(void *instance) {
    if(instance != NULL) {
            if(NM.isBool) {
        if(NM.StartHook) {
        
            bool ReturnValue = NM.HookBoolValue;
        return ReturnValue;
        
       }
     }
   }
   return _HookBool(instance);
 }

int (*_HookInt)(void *instance);
int HookInt(void *instance) {
    if(instance != NULL) {
        LOGD(OBFUSCATE("HOOKING"));
            if(NM.isInt) {
        if(NM.StartHook) {
            
   
        int ReturnValue = NM.HookIntValue;
        return ReturnValue;
       }
     }
   }
   return _HookInt(instance);
 }

void (*PatchVoidBool)(void* _this, bool valuez);
void (*_HookVoidBool)(void *player);
void HookVoidBool(void *player) {
    if (player != NULL) {
        if(NM.StartHookVoid) {
            if(NM.isVoidBool) {
                PatchVoidBool(player, NM.HookVoidBoolValue);
            }
        }
     }
    return _HookVoidBool(player);
}

void (*PatchVoidFloat)(void* _this, float valuez);
void (*_HookVoidFloat)(void *player);
void HookVoidFloat(void *player) {
    if (player != NULL) {
        if(NM.StartHookVoid) {
            if(NM.isVoidFloat) {
                PatchVoidFloat(player, NM.HookVoidFloatValue);
            }
        }
     }
    return _HookVoidFloat(player);
}

void (*PatchVoidInt)(void* _this, int valuez);
void (*_HookVoidInt)(void *player);
void HookVoidInt(void *player) {
    if (player != NULL) {
        if(NM.StartHookVoid) {
            if(NM.isVoidInt) {
                PatchVoidInt(player, NM.HookVoidIntValue);
            }
        }
     }
    return _HookVoidInt(player);
}

void(*_HookField)(void *instance); //this can also be done within the player update hook
void HookField(void *instance) {
  if(instance != NULL) {
      if(NM.StartFieldHooking) {
            if (NM.isFieldBool) {
            *(bool *) ((uint64_t) instance + string2Offset(NM.fieldOffset)) = NM.HookFieldBoolValue;
        } else if(NM.isFieldInt) {
             *(int *) ((uint64_t) instance + string2Offset(NM.fieldOffset)) = NM.HookFieldIntValue;
        } else if(NM.isFieldFloat) {
             *(float *) ((uint64_t) instance + string2Offset(NM.fieldOffset)) = NM.HookFieldFloatValue;
        }
      }
  }
  
 return _HookField(instance);
}

void(*_DisableVoid)(void *instance);
void DisableVoid(void *instance) {
    if(instance != NULL) {
        if(NM.isVoidDisabled) {
            if(NM.startDisable) {
                return;
            }
        }
        
    }
    return _DisableVoid(instance);
}

void(*_VoidUpdate)(void *instance);
void VoidUpdate(void *instance) {
    if (instance != NULL) {
        if(NM.CallVoid && NM.StartCalling) {
            
                _VoidUpdate(instance);
         }   
    }
   return _VoidUpdate(instance);
}

void *hack_thread(void *) {
    if(NM.libname == NULL) {
        NM.libname = "libil2cpp.so";
    }
    if(NM.offset == NULL) {
        NM.offset = "0x000000";
    }
    if(NM.hex == NULL) {
        NM.hex = "00 00 00 00 00";
    }
    
    LOGI(OBFUSCATE("pthread created"));


    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));

 
    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__) 


/*

     ARM64-V8A
     
*/



#else 

    
/*

     Others
     
*/


#endif


    return NULL;
}


jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("RedAlert_This Is Official V3 Version. Report Bugs For More Improvement"),
            
            OBFUSCATE("1_InputText_Input Lib Name"),
            OBFUSCATE("2_Button_Set Lib"),
            OBFUSCATE("Collapse_Patch Offset"),
            
            OBFUSCATE("100_CollapseAdd_InputText_Input Offset"),
            OBFUSCATE("101_CollapseAdd_InputText_Input Hex"),
            OBFUSCATE("102_CollapseAdd_Toggle_Patch"),
            
            OBFUSCATE("Collapse_Hook Offset"),
            OBFUSCATE("200_CollapseAdd_RadioButton_Hook_OFF,Hook Bool,Hook Int,Hook Float"),
            OBFUSCATE("201_CollapseAdd_InputText_Enter Offset To Hook"),
            OBFUSCATE("202_CollapseAdd_InputValue_Enter Value To Hook"),
            OBFUSCATE("203_CollapseAdd_Toggle_Hook Enable"),
            
            OBFUSCATE("Collapse_Hook Void"),
            OBFUSCATE("300_CollapseAdd_RadioButton_Hook_OFF, Void (bool value),Void (int Value),Void (float Value)"),
            OBFUSCATE("301_CollapseAdd_InputText_Enter Offset To Hook"),
            OBFUSCATE("302_CollapseAdd_InputValue_Enter Value To Hook"),
            OBFUSCATE("303_CollapseAdd_InputText_Enter Update Offset"),
            OBFUSCATE("304_CollapseAdd_Toggle_Hook Enable"),
            
            OBFUSCATE("Collapse_Hook Field Offset"),
            OBFUSCATE("400_CollapseAdd_RadioButton_Hook_OFF, bool,int, float"),
            OBFUSCATE("401_CollapseAdd_InputText_Enter Field Offset To Hook"),
            OBFUSCATE("402_CollapseAdd_InputValue_Enter Value To Hook"),
            OBFUSCATE("403_CollapseAdd_InputText_Enter Update Offset"),
            OBFUSCATE("404_CollapseAdd_Toggle_Hook Enable"),
            
            OBFUSCATE("Collapse_Disable Void (Anticrash/Antidetect Tester)"),
            OBFUSCATE("500_CollapseAdd_RadioButton_Hook_OFF, Disactive Void"),
            OBFUSCATE("501_CollapseAdd_InputText_Enter Offset To Disable Void"),
            OBFUSCATE("502_CollapseAdd_Toggle_Hook Enable"),
            
            OBFUSCATE("Collapse_Hook Call Void"),
            OBFUSCATE("600_CollapseAdd_RadioButton_Hook_OFF, Call Void"),
            OBFUSCATE("601_CollapseAdd_InputText_Enter Offset To Call Void"),
            
            OBFUSCATE("602_CollapseAdd_Toggle_Hook Enable"),
            
            OBFUSCATE("Collapse_Easy Patcher"),
            OBFUSCATE("700_CollapseAdd_Spinner_Choose Type_Off, Int, Float, Bool"),
            OBFUSCATE("701_CollapseAdd_InputText_Enter Offset"),
            OBFUSCATE("702_CollapseAdd_Spinner_Select Value For Int _Off - 00, 1, 10, 50, 100, 999, 1000, 1M, 12M"),
            OBFUSCATE("703_CollapseAdd_Spinner_Select Value For Float_Off - 00, 1, 2, 40, 99, 100, 1000, 2000"),
            OBFUSCATE("704_CollapseAdd_Spinner_Select Value For Bool_Off - 00, True - 00 00 A0 E3 1E FF 2F E1, False - 01 00 A0 E3 1E FF 2F E1"),
            OBFUSCATE("705_CollapseAdd_Toggle_Start Patching"),
          
            
            OBFUSCATE("ButtonLink_Report Bug_https://t.me/nepmods"),
            
            
            
    };
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    switch (featNum) {
        
        case 1:
            
            NM.libname = env->GetStringUTFChars(str, 0);
            
            break;
            
        case 2:
            
            Toast(env,obj,NM.libname,ToastLength::LENGTH_LONG);
            
            break;
            
        case 100:
            
             NM.offset = env->GetStringUTFChars(str, 0);
            
            break;
            
         case 101:
             
              NM.hex = env->GetStringUTFChars(str, 0);
             
            break;
         
         case 102:
             if(boolean) {
                 NepPatch(NM.libname, NM.offset, NM.hex);
             } else {
                 NepRestore(NM.libname, NM.offset);
             }
              
            break;
         
            case 103:
              Toast(env, obj, OBFUSCATE("Restore Coming Soon"), ToastLength::LENGTH_LONG);
              
          break;
          case 200:
              NM.SelectedHook = value;
               if (NM.SelectedHook == 1) {
                   Toast(env, obj, "Done", ToastLength::LENGTH_LONG);

                   NM.isBool = false;
                   NM.isInt = false;
                   NM.isFloat = false;
               } else if(NM.SelectedHook == 2) {
                   
                   NM.isBool = true;
                   NM.isInt = false;
                   NM.isFloat = false;
                   Toast(env, obj, "Hooking Bool", ToastLength::LENGTH_LONG);
                  
               }else if(NM.SelectedHook == 3) {
                
                   NM.isBool = false;
                   NM.isInt = true;
                   NM.isFloat = false;
                   Toast(env, obj, "Hooking Int", ToastLength::LENGTH_LONG);
                  
               }else if(NM.SelectedHook == 4) {
                   NM.isBool = false;
                   NM.isInt = false;
                   NM.isFloat = true;
                   
                   Toast(env, obj, "Hooking Float", ToastLength::LENGTH_LONG);
                  
               }
            break;
            case 201:
                   NM.offsetToHook = env->GetStringUTFChars(str, 0);
                   break;
            case 202:
                   
                   if(NM.isFloat) {
                       NM.HookFloatValue = (float) value;
                   } else if(NM.isBool) {
                       int TheValue = (int) value;
                       
                       if(TheValue == 0) {
                           NM.HookBoolValue = false;
                       } else if(TheValue == 1) {
                           NM.HookBoolValue = true;
                       }
                       
                   } else if(NM.isInt) {
                       NM.HookIntValue = (int) value;
   
                   }
            break;
            case 203:
                   
                   NM.StartHook = boolean;
                   if(NM.StartHook) {
                       if(NM.isFloat) {
                           NepmodsHook(NM.libname, NM.offsetToHook, HookFloat,_HookFloat);
                  
                           Toast(env, obj, "Hooking Float", ToastLength::LENGTH_LONG);
                  
                       } else if(NM.isBool) {
                           NepmodsHook(NM.libname, NM.offsetToHook, HookBool,_HookBool);
                  
                           Toast(env, obj, "Hooking Bool", ToastLength::LENGTH_LONG);
                  
                       } else if(NM.isInt) {
                           NepmodsHook(NM.libname, NM.offsetToHook, HookInt,_HookInt);
                  
                           Toast(env, obj, "Hooking Int", ToastLength::LENGTH_LONG);
                  
                       }
                   }
            break;
            case 300:
                   NM.SelectedVoidHook = value;
               if (NM.SelectedVoidHook == 1) {
                   
                   NM.isVoidBool = false;
                   NM.isVoidInt = false;
                   NM.isVoidFloat = false;
               } else if(NM.SelectedVoidHook == 2) {
                   
                   NM.isVoidBool = true;
                   NM.isVoidInt = false;
                   NM.isVoidFloat = false;
                   Toast(env, obj, "Hooking Void Bool", ToastLength::LENGTH_LONG);
                  
               }else if(NM.SelectedVoidHook == 3) {
                   
                   NM.isVoidBool = false;
                   NM.isVoidInt = true;
                   NM.isVoidFloat = false;
                   Toast(env, obj, "Hooking Void Int", ToastLength::LENGTH_LONG);
                  
               }else if(NM.SelectedVoidHook == 4) {
                   NM.isVoidBool = false;
                   NM.isVoidInt = false;
                   NM.isVoidFloat = true;
                   Toast(env, obj, "Hooking Void Float", ToastLength::LENGTH_LONG);
                  
               } else {
                   NM.isVoidBool = false;
                   NM.isVoidInt = false;
                   NM.isVoidFloat = false;
               }
                   
             break;
             case 301:
                   NM.offsetToHookVoid = env->GetStringUTFChars(str, 0);
                   
                   if(NM.isVoidFloat) {
                       
                         PatchVoidFloat = (void (*)(void *, float))getAbsoluteAddress(NM.libname, string2Offset(NM.offsetToHookVoid));
                         
                   } else if(NM.isVoidBool) {
                           PatchVoidBool = (void (*)(void *, bool))getAbsoluteAddress(NM.libname, string2Offset(NM.offsetToHookVoid));
                         
                           
                       } else if(NM.isVoidInt) {
                           PatchVoidInt = (void (*)(void *, int))getAbsoluteAddress(NM.libname, string2Offset(NM.offsetToHookVoid));
                         
                           
                           
                       }
               break;
               case 302:
                                     
                   if(NM.isVoidFloat) {
                       NM.HookVoidFloatValue = (float) value;
                   } else if(NM.isVoidBool) {
                       int TheValue = (int) value;
                       
                       if(TheValue == 0) {
                           NM.HookVoidBoolValue = false;
                       } else if(TheValue == 1) {
                           NM.HookVoidBoolValue = true;
                       }
                       
                   } else if(NM.isVoidInt) {
                       NM.HookVoidIntValue = (int) value;
   
                   }
             break;
             case 303:
                   NM.offsetToUpdateVoid = env->GetStringUTFChars(str, 0);
              if(NM.isVoidInt) {
                    NepmodsHook(NM.libname, NM.offsetToUpdateVoid, HookVoidInt,_HookVoidInt);
                     
                 } else if(NM.isVoidBool) {
                           NepmodsHook(NM.libname, NM.offsetToUpdateVoid, HookVoidBool,_HookVoidBool);
                       } else if(NM.isVoidFloat) {
                           
                           NepmodsHook(NM.libname, NM.offsetToUpdateVoid, HookVoidFloat,_HookVoidFloat);
                     
                       }
            break;
            case 304:
                   NM.StartHookVoid = boolean;
                   if(NM.StartHookVoid) {
                       if(NM.isVoidFloat) {
                           
                           Toast(env, obj, "Hooking Void Float", ToastLength::LENGTH_LONG);
                  
                       } else if(NM.isVoidBool) {
                           
                           Toast(env, obj, "Hooking Void Bool", ToastLength::LENGTH_LONG);
                  
                       } else if(NM.isVoidInt) {
                           
                           Toast(env, obj, "Hooking Void Int", ToastLength::LENGTH_LONG);
                  
                       }
                   }
           break;
           case 400:
               NM.SelectedFieldHook = value;
               if (NM.SelectedFieldHook == 1) {
                   
                   NM.isFieldBool = false;
                   NM.isFieldInt = false;
                   NM.isFieldFloat = false;
               } else if(NM.SelectedFieldHook == 2) {
                   
                   NM.isFieldBool = true;
                   NM.isFieldInt = false;
                   NM.isFieldFloat = false;
                   
               }else if(NM.SelectedFieldHook == 3) {
                   
                   NM.isFieldBool = false;
                   NM.isFieldInt = true;
                   NM.isFieldFloat = false;
                   
               }else if(NM.SelectedFieldHook == 4) {
                   NM.isFieldBool = false;
                   NM.isFieldInt = false;
                   NM.isFieldFloat = true;

                   
               } else {
                   NM.isFieldBool = false;
                   NM.isFieldInt = false;
                   NM.isFieldFloat = false;
               }
                   
           break;
           case 401:
               NM.fieldOffset = env->GetStringUTFChars(str, 0);
           break;
           case 402:
               if(NM.isFieldFloat) {
                       NM.HookFieldFloatValue = (float) value;
                   } else if(NM.isFieldBool) {
                       int TheValue = (int) value;
                       
                       if(TheValue == 0) {
                           NM.HookFieldBoolValue = false;
                       } else if(TheValue == 1) {
                           NM.HookFieldBoolValue = true;
                       }
                       
                   } else if(NM.isFieldInt) {
                       NM.HookFieldIntValue = (int) value;
   
                   }
           break;
           case 403:
               NM.offsetToUpdateField = env->GetStringUTFChars(str, 0);
              NepmodsHook(NM.libname, NM.offsetToUpdateField, HookField,_HookField);
                     
           break;
           case 404:
               NM.StartFieldHooking = boolean;
                   if(NM.StartFieldHooking) {
                       if(NM.isFieldFloat) {
                           
                           Toast(env, obj, "Hooking Field Float", ToastLength::LENGTH_LONG);
                  
                       } else if(NM.isFieldBool) {
                           
                           Toast(env, obj, "Hooking Field Bool", ToastLength::LENGTH_LONG);
                  
                       } else if(NM.isFieldInt) {
                           
                           Toast(env, obj, "Hooking Field Int", ToastLength::LENGTH_LONG);
                  
                       }
                   }
           break;
           case 500:
               NM.SelectedOption = value;
               if(NM.SelectedOption == 2) {
                   NM.isVoidDisabled = true;
               } else {
                   NM.isVoidDisabled = false;
               }
               
           break;
           case 501:
               NM.voidOffset = env->GetStringUTFChars(str, 0);
           break;
           case 502:
               NM.startDisable = boolean;
               if(NM.isVoidDisabled && NM.voidOffset != NULL && NM.startDisable) {
                   NepmodsHook(NM.libname, NM.voidOffset, DisableVoid,_DisableVoid);
                   const char *TextToast = NM.voidOffset;
                   Toast(env, obj, TextToast, ToastLength::LENGTH_LONG);
                  
               }
           break;
           case 600:
               NM.SelectedCallOption = value;
               if(NM.SelectedCallOption == 2) {
                   NM.CallVoid = true;
               } else {
                   NM.CallVoid = false;
               }
               break;
           case 601:
               NM.callOffset = env->GetStringUTFChars(str, 0);
               break;
           
           case 602:
               NM.StartCalling = boolean;
               if(NM.StartCalling && NM.CallVoid) {
                   Toast(env, obj, "Calling Void", ToastLength::LENGTH_LONG);
                   
                  NepmodsHook(NM.libname, NM.callOffset, VoidUpdate,_VoidUpdate);
                  
               }
               break;
           case 700: 
           
               NM.SelectedEasyTool = value;
               if(NM.SelectedEasyTool == 0) {
                   NM.isSelectedBool= false;
                   NM.isSelectedInt = false;
                   NM.isSelectedFloat = false;
               } else if(NM.SelectedEasyTool == 1) {
                   Toast(env, obj, "Int", ToastLength::LENGTH_LONG);
                   NM.isSelectedBool= false;
                   NM.isSelectedInt = true;
                   NM.isSelectedFloat = false;
               
                   }else if(NM.SelectedEasyTool == 2) {
                   Toast(env, obj, "Float", ToastLength::LENGTH_LONG);
                   NM.isSelectedBool= false;
                   NM.isSelectedInt = false;
                   NM.isSelectedFloat = true;
               
                   }else if(NM.SelectedEasyTool == 3) {
                   NM.isSelectedBool= true;
                   NM.isSelectedInt = false;
                   NM.isSelectedFloat = false;
               
                       Toast(env, obj, "Bool", ToastLength::LENGTH_LONG);
                   }
           break;
           case 701:
               NM.EasyPatchOffset = env->GetStringUTFChars(str, 0);
           break;
           case 702:
               if(value != 0 && NM.SelectedEasyTool != 0) {
                   if(NM.isSelectedInt) {
                     NM.SelectedEasyInt = value;
                     int SelectedEasyInt = value;
                     if(SelectedEasyInt == 1) {
                         NM.HexToPatchInt = NM.Int1;
                     } else if(SelectedEasyInt == 2) {
                         NM.HexToPatchInt = NM.Int10;
                     }else if(SelectedEasyInt == 3) {
                         NM.HexToPatchInt = NM.Int50;
                     }else if(SelectedEasyInt == 4) {
                         NM.HexToPatchInt = NM.Int100;
                     }else if(SelectedEasyInt == 5) {
                         NM.HexToPatchInt = NM.Int999;
                     }else if(SelectedEasyInt == 6) {
                         NM.HexToPatchInt = NM.Int1000;
                     }else if(SelectedEasyInt == 7) {
                         NM.HexToPatchInt = NM.Int1M;
                     }else if(SelectedEasyInt == 8) {
                         NM.HexToPatchInt = NM.Int12M;
                     }
                   } else {
                       Toast(env, obj, "Not Using, Select Int To Activate This", ToastLength::LENGTH_LONG);
                   }
               }
           break;
           case 703:
               if(value != 0 && NM.SelectedEasyTool != 0) {
                  if(NM.isSelectedFloat) {
                      NM.SelectedEasyFloat = value;
                      int SelectedEasyFloat = value;
                     if(SelectedEasyFloat == 1) {
                         NM.HexToPatchFloat = NM.Float1;
                     } else if(SelectedEasyFloat == 2) {
                         NM.HexToPatchFloat = NM.Float2;
                     }else if(SelectedEasyFloat == 3) {
                         NM.HexToPatchFloat = NM.Float40;
                     }else if(SelectedEasyFloat == 4) {
                         NM.HexToPatchFloat = NM.Float99;
                     }else if(SelectedEasyFloat == 5) {
                         NM.HexToPatchFloat = NM.Float100;
                     }else if(SelectedEasyFloat == 6) {
                         NM.HexToPatchFloat = NM.Float1000;
                     }else if(SelectedEasyFloat == 7) {
                         NM.HexToPatchFloat = NM.Float2000;
                     }
                   } else {
                       Toast(env, obj, "Not Using, Select Float To Activate This", ToastLength::LENGTH_LONG);
                   }
               }
           break;
           case 704:
               if(value != 0 && NM.SelectedEasyTool != 0) {
                 if(NM.isSelectedBool) {
                      NM.SelectedEasyBool = value;
                      int SelectedEasyBool = value;
                     if(SelectedEasyBool == 1) {
                         NM.HexToPatchBool = NM.BoolTrue;
                     } else if(SelectedEasyBool == 2) {
                         NM.HexToPatchBool = NM.BoolFalse;
                     } 
                   } else {
                       Toast(env, obj, "Not Using, Select Bool to Activate This", ToastLength::LENGTH_LONG);
                   }
               }
           break;
           case 705:
               if(boolean) {
                    if(NM.EasyPatchOffset != NULL) {
                       if(NM.isSelectedBool) {
                           NepPatch(NM.libname, NM.EasyPatchOffset, NM.HexToPatchBool);
                           Toast(env, obj, "Bool Patched", ToastLength::LENGTH_LONG);
                       } else if(NM.isSelectedInt){
                           NepPatch(NM.libname, NM.EasyPatchOffset, NM.HexToPatchInt);
                           Toast(env, obj, "Int Patched", ToastLength::LENGTH_LONG);
                       } else if(NM.isSelectedFloat) {
                           NepPatch(NM.libname, NM.EasyPatchOffset, NM.HexToPatchFloat);
                           Toast(env, obj, "Float Patched", ToastLength::LENGTH_LONG);
                      } else {
                          NepRestore(NM.libname, NM.EasyPatchOffset);
                          Toast(env, obj, "Current Offset Restored", ToastLength::LENGTH_LONG);
                      }
                  }
              } else {
                  if(NM.EasyPatchOffset != NULL) {
                     NepRestore(NM.libname, NM.EasyPatchOffset);
                     Toast(env, obj, "Current Offset Restored", ToastLength::LENGTH_LONG);
                  }
              }
               break;
            

            
    }
}


    
/*

     Ignore All code Down From Here
     
*/


__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

#include "RegisterMenu.h"


