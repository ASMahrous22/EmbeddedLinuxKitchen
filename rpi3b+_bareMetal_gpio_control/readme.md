# Raspberry Pi 3B+ Bare Metal GPIO Control

This project demonstrates how to write a bare-metal program to control GPIO pins on a Raspberry Pi model 3B+. It involves writing assembly and C code, linking them with a custom linker script, and loading the final binary using U-Boot.

## **Project Structure**

### **Files**

1. `gpio_control.S` - Assembly file for initialization.
2. `gpio_control.c` - Main C program.
3. `gpio_control.ld` - Linker script defining memory layout.

### **Overview**

- **The assembly file (********`gpio_control.S`********\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*)** sets up the stack pointer and jumps to `main`.
- **The C file (********`gpio_control.c`********\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*)** configures GPIO and enters an infinite loop.
- **The linker script (********`gpio_control.ld`********\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*)** ensures the program is placed correctly in memory.

```
+--------------------------+
|  gpio_control.S          |  (Assembly Code)
|  - Setup stack pointer   |
|  - Jump to main function |
+--------------------------+

+--------------------------+
|  gpio_control.c          |  (C Code)
|  - Configure GPIO 17     |
|  - Turn on LED           |
|  - Infinite loop         |
+--------------------------+

+--------------------------+
|  gpio_control.ld         |  (Linker Script)
|  - Define memory layout  |
|  - Start at 0x81000      |
+--------------------------+
```

---

## **Build Steps**

### **1. Compile the C Code**

-> Before that write this command "export PATH=/home/abdallah/x-tools/aarch64-rpi3-linux-gnu/bin:\$PATH", to add it to the path folder to run it from anywhere.

```sh
aarch64-rpi3-linux-gnu-gcc -c -nostdlib -o ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.o ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.c
```

- Converts `gpio_control.c` into machine code (`gpio_control.o`).

### **2. Assemble the Assembly Code**

```sh
aarch64-rpi3-linux-gnu-as ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.S -o ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_controlASM.o
```

- Converts `gpio_control.S` into machine code (`gpio_controlST.o`).

### **3. Link Everything Together**

```sh
aarch64-rpi3-linux-gnu-ld -nostdlib -T ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.ld -o ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.elf ~/rpi3b+_bareMetal_gpio_control/gpio_control/*.o
```

- Links object files and produces an ELF executable (`gpio_control.elf`).

### **4. Convert ELF to Binary**

```sh
aarch64-rpi3-linux-gnu-objcopy -O binary ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.elf ~/rpi3b+_bareMetal_gpio_control/gpio_control/gpio_control.bin
```

- Strips ELF metadata to create a raw binary (`gpio_control.bin`).

---

## **Deploying to Raspberry Pi**

### **5. Copy the Binary to the SD Card**

- Copy `gpio_control.bin` to the SD card.
- Insert the SD card into the Raspberry Pi.

### **6. Load the Program Using U-Boot**

Connect to the Raspberry Pi via UART using Minicom and run:

```sh
fatload mmc 0:1 0x81000 gpio_control.bin
go 0x81000
```

- `fatload` loads the binary into RAM at `0x81000`.
- `go 0x81000` jumps to that address to execute the program.

### **7. Observe the LED**

- The LED connected to **GPIO 17 (pin 11)** should turn **ON**.

```
+------------------+
|  Raspberry Pi    |
|  - GPIO 17 ON   |
|  - LED is ON    |
+------------------+
```

---

## **Summary**

| Step | Action            | Command             | Purpose                          |
| ---- | ----------------- | ------------------- | -------------------------------- |
| 1    | Compile C         | `gcc -c`            | Convert C code to machine code   |
| 2    | Assemble          | `as`                | Convert assembly to machine code |
| 3    | Link              | `ld -T`             | Create executable ELF            |
| 4    | Convert to Binary | `objcopy -O binary` | Strip ELF metadata               |
| 5    | Copy to SD        | N/A                 | Transfer binary to Raspberry Pi  |
| 6    | Load with U-Boot  | `fatload` and `go`  | Load and execute program         |
| 7    | Observe LED       | N/A                 | LED should turn ON               |

### **Final Process Flow**

```
[Write Code] --> [Compile] --> [Assemble] --> [Link] --> [Convert to Binary] -->
[Copy to SD] --> [Load with U-Boot] --> [Run on Raspberry Pi] --> [LED Turns ON]
```


