#ifndef ZYCHEATS_SGUYS_FUNCTIONS_H
#define ZYCHEATS_SGUYS_FUNCTIONS_H

// 200080D2C0035FD6
// 00 00 80 D2 C0 03 5F D6
// 00E0AFD2C0035FD6
// 1F2003D5

// here you can define variables for the patches
bool addCurrency, freeItems, everythingUnlocked, showAllItems, addSkins;
// test code 
bool ha, hb, hc, hd, he, hf, hg, hh, hi;
// 0x117eaac 0x7cec642aac private Single get_CreditsMultiplier()
// 0x117eb70 0x7cec642b70 private Single get_XPMultiplier()
// 0x120c9b8 0x7cec6d09b8 private Void FindNewEnemy()
// 0x120d384 0x7cec6d1384 private Void CheckIfAimingAtCurrentEnemy()
// 0x122902c 0x7cec6ed02c public Int32 get_currentKillsInKillstreak()
// 0x1244630 0x7cec708630 public Boolean IsVisible()
// 0x1248d40 0x7cec70cd40 public Single get_health()
// 0x1283ac8 0x7cec747ac8 public Int32 get_BaseEarnedXpThisMatch()
// 0x1283ad0 0x7cec747ad0 public Int32 get_EarnedCreditsThisMatch()


monoString *CreateIl2cppString(const char *str) {
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString*(*)(void*, const char*)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0x2596B20")));
    return String_CreateString(NULL, str);
}

void (*PurchaseRealMoney) (void* instance, monoString* itemId, monoString* receipt, void* callback);

void Pointers() {
    PurchaseRealMoney = (void(*)(void*, monoString*, monoString*, void*)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0xE7AADC")));
}

void Patches() {
    PATCH_SWITCH("0x10A69A0", "200080D2C0035FD6", showAllItems);
    PATCH_SWITCH("0xF148A4", "E07C80D2C0035FD6", freeItems);
    
    PATCH_SWITCH("0x117eaac", "00E0AFD2C0035FD6", ha);
    PATCH_SWITCH("0x117eb70", "00E0AFD2C0035FD6", hb);
    PATCH_SWITCH("0x120c9b8", "1F2003D5", hc);
    PATCH_SWITCH("0x120d384", "1F2003D5", hd);
    PATCH_SWITCH("0x122902c", "00E0AFD2C0035FD6", he);
    PATCH_SWITCH("0x1244630", "200080D2C0035FD6", hf);
    PATCH_SWITCH("0x1248d40", "00E0AFD2C0035FD6", hg);
    PATCH_SWITCH("0x1283ac8", "00E0AFD2C0035FD6", hh);
    PATCH_SWITCH("0x1283ad0", "00E0AFD2C0035FD6", hi);
    

    // PATCH_SWITCH("Ox0", "HEX", var);
}

// declare your hooks here
void (*old_Backend)(void *instance);
void Backend(void *instance) {
    if (instance != NULL) {
        if (addCurrency) {
            LOGW("Calling Purchase");
            PurchaseRealMoney(instance, CreateIl2cppString("special_offer1"), CreateIl2cppString("dev"), NULL);
            addCurrency = false;
        }
        if (addSkins) {
            LOGW("Calling Skins");
            addSkins = false;
        }
    }
    return old_Backend(instance);
}

void* (*old_ProductDefinition)(void *instance, monoString* id, monoString* storeSpecificId, int type, bool enabled, void* payouts);
void* ProductDefinition(void *instance, monoString* id, monoString* storeSpecificId, int type, bool enabled, void* payouts) {
    if (instance != NULL) {
        LOGW("Called ProductDefinition! Here are the parameters:");
        LOGW("id: %s", id->getChars());
        LOGW("storeSpecificId: %s", storeSpecificId->getChars());
        LOGW("type: %i", type);
    }
    return old_ProductDefinition(instance, id, storeSpecificId, type, enabled, payouts);
}

void Hooks() {
    HOOK("0xE7BC74", Backend, old_Backend);
    HOOK("0x29DA08C", ProductDefinition, old_ProductDefinition);
}

#endif //ZYCHEATS_SGUYS_FUNCTIONS_H
