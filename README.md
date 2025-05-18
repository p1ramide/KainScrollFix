# KainScrollFix
**KainScrollFix** is a lightweight Windows utility that fixes erratic mouse wheel behavior on some Roccat Kain 100 and similar mice.  
It runs in the background and filters out unwanted reverse scroll spikes caused by faulty hardware signals.

---

### 🧠 How it works

Some Roccat mice generate short, incorrect wheel inputs in the opposite direction while scrolling.  
This app sets a low-level mouse hook (`WH_MOUSE_LL`) and ignores:

- Very small scroll deltas (less than 30)
- Sudden direction changes within 150 milliseconds

This eliminates most bounce effects and makes scrolling feel smooth and consistent.

---

### ⚙️ How to use

1. **Compile the program using g++**:
   ```bash
   g++ -std=c++17 -O2 -Wall -o wheelfix.exe wheelfix.cpp -mwindows
2. **Place wheelfix.exe inside the startup folder**:

   Press Win + R, type:
   ```bash
   shell:startup 
   ```
   - press Enter
   - Move wheelfix.exe into that folder (this ensures it launches automatically with Windows and runs silently)
   - Restart your PC

3. **That's it — the app runs in the background and improves your scroll experience.**

### 🛠️ How to install g++
If you don't have g++, install MSYS2 (**recommended**):
- Go to: https://www.msys2.org/
- Download and install
- Run MSYS2 terminal and execute:
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```
- After that, open MSYS2 UCRT64 terminal and you're ready to compile.

### 💻 Code overview
Uses SetWindowsHookEx to install a global mouse hook

**Filters**:

- Small deltas → blocked
- Direction changes too fast → blocked
**Safe**: does not modify system files or drivers

### ✅ Features
- Silent background execution
- No admin rights required
- No visual window or taskbar icon
- Works automatically at boot (if placed in shell:startup)
