// ---- Target Damage ----
// Sends battle attack packets directly via memory addresses.
// NetPointer: address of the network class pointer (read DWORD from this address to get "this")
// BattleCall: address of the SendBattleAttack function (__thiscall)
// Target VID is still obtained via Python API (player.GetTargetVID).
static DWORD lastTargetDamageTick = 0;

// Parse a hex string (no "0x" prefix) into a DWORD.
inline DWORD ParseHexAddr(const char* buf)
{
    if (!buf || !buf[0]) return 0;
    DWORD val = 0;
    for (int i = 0; buf[i]; i++)
    {
        char c = buf[i];
        DWORD digit = 0;
        if (c >= '0' && c <= '9')      digit = c - '0';
        else if (c >= 'A' && c <= 'F') digit = 10 + c - 'A';
        else if (c >= 'a' && c <= 'f') digit = 10 + c - 'a';
        else continue;
        val = (val << 4) | digit;
    }
    return val;
}

// Check if a DWORD address is readable in-process memory.
inline bool IsAddrReadable(DWORD addr)
{
    if (addr < 0x10000) return false; // null-range guard (first 64KB is reserved on Windows)
    MEMORY_BASIC_INFORMATION mbi = {};
    if (VirtualQuery((void*)addr, &mbi, sizeof(mbi)) == 0) return false;
    if (mbi.State != MEM_COMMIT) return false;
    if (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) return false;
    return true;
}

inline void TickTargetDamage()
{
    if (!Keyboard::TargetDamage) return;
    if (!player::GetTargetVID) return;

    // Parse user-configurable addresses
    DWORD netPtrAddr = ParseHexAddr(Keyboard::C_TargetDmgNetPointer);
    DWORD battleAddr = ParseHexAddr(Keyboard::C_TargetDmgBattleCall);
    if (!netPtrAddr || !battleAddr) return;
    if (!IsAddrReadable(netPtrAddr)) return;

    // Read the network class instance pointer
    DWORD netInstance = *(DWORD*)netPtrAddr;
    if (!netInstance || !IsAddrReadable(netInstance)) return;

    // Validate the battle call address is in executable memory
    if (!IsAddrReadable(battleAddr)) return;

    // Get current target VID via Python API
    auto vidResult = PyHelper::CallNoArgs(player::GetTargetVID);
    long targetVID = PyHelper::ExtractInt(vidResult);
    PyHelper::DecRef(vidResult);
    if (targetVID <= 0) return;

    // Throttle by speed setting
    DWORD now = GetTickCount();
    int speed = Keyboard::C_TargetDamageSpeed;
    if (speed < 10) speed = 10; // minimum 10ms between attacks
    if (now - lastTargetDamageTick < (DWORD)speed) return;
    lastTargetDamageTick = now;

    // Call SendBattleAttack as __thiscall(netInstance, targetVID)
    // typedef: void (__thiscall *)(void* this, DWORD vid)
    typedef void (__thiscall *SendBattleAttackFn)(void* pThis, DWORD vid);
    SendBattleAttackFn pSendBattleAttack = (SendBattleAttackFn)battleAddr;

    __try
    {
        pSendBattleAttack((void*)netInstance, (DWORD)targetVID);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // Silently ignore crashes from bad addresses
    }
}
