# C++ 服务器开发精髓



> C++ 服务器开发精髓一书学习笔记，仅用于个人学习过程记录



## 一、开发环境介绍



> 开发环境整体上有两台设备，一台 Windows + 一台Mac， 这两台电脑分别通过 VMWare WorkStation 安装了 CentOS7.9 虚拟机，环境细节详见[CentOS7.9](./doc/CentOS7.9/README.md)



### 1. Windows 开发环境

**windows**

```
 msinfo32

   OS Name	Microsoft Windows 10 Pro
   Version	10.0.19042 Build 19042
   Other OS Description 	Not Available
   OS Manufacturer	Microsoft Corporation
   System Name	LIUSHXIN
   System Manufacturer	Dell Inc.
   System Model	Inspiron 7559
   System Type	x64-based PC
   System SKU	0706
   Processor	Intel(R) Core(TM) i5-6300HQ CPU @ 2.30GHz, 2301 Mhz, 4 Core(s), 4 Logical Processor(s)
   BIOS Version/Date	Dell Inc. 1.2.0, 9/22/2016
   SMBIOS Version	3.0
   Embedded Controller Version	255.255
   BIOS Mode	UEFI
   BaseBoard Manufacturer	Dell Inc.
   BaseBoard Product	0H87XC
   BaseBoard Version	A00
   Platform Role	Mobile
   Secure Boot State	On
   PCR7 Configuration	Elevation Required to View
   Windows Directory	C:\WINDOWS
   System Directory	C:\WINDOWS\system32
   Boot Device	\Device\HarddiskVolume1
   Locale	China
   Hardware Abstraction Layer	Version = "10.0.19041.1566"
   User Name	LIUSHXIN\Administrator
   Time Zone	China Standard Time
   Installed Physical Memory (RAM)	12.0 GB
   Total Physical Memory	11.9 GB
   Available Physical Memory	4.18 GB
   Total Virtual Memory	12.6 GB
   Available Virtual Memory	4.79 GB
   Page File Space	768 MB
   Page File	C:\pagefile.sys
   Kernel DMA Protection	Off
   Virtualization-based security	Running
   Virtualization-based security Required Security Properties	
   Virtualization-based security Available Security Properties	Base Virtualization Support, Secure Boot, DMA Protection
   Virtualization-based security Services Configured	
   Virtualization-based security Services Running	
   Device Encryption Support	Elevation Required to View
   A hypervisor has been detected. Features required for Hyper-V will not be displayed.	
```

**visual studio**

```
// Visual Studio 12 2013
// Visual Studio 14 2015
Visual Studio 15 2017 Win64
Visual Studio 16 2019 Win64
```

**cmake**

```
cmake --version 
cmake version 3.28.0  
CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

**git**

```
λ git --version
git version 2.32.0.windows.2
```



### 2. Mac 开发环境

**mac**

```
apples-Mac-mini-1243:Desktop apple$ system_profiler SPHardwareDataType
 Hardware:
   Hardware Overview:
     Model Name: Mac mini
     Model Identifier: Macmini8,1
     Processor Name: 6-Core Intel Core i5
     Processor Speed: 3 GHz
     Number of Processors: 1
     Total Number of Cores: 6
     L2 Cache (per Core): 256 KB
     L3 Cache: 9 MB
     Memory: 8 GB
     System Firmware Version: 1916.40.8.0.0 (iBridge: 20.16.420.0.0,0)
     OS Loader Version: 564.40.4~27
     Serial Number (system): xxx
     Hardware UUID: xxx
     Provisioning UDID: xxx
     Activation Lock Status: Enabled
```

**cmake**

```
apples-Mac-mini-1243:Desktop apple$ cmake --version
cmake version 3.27.4
```

**gcc**

```
apples-Mac-mini-1243:Desktop apple$ gcc -v
Apple clang version 14.0.0 (clang-1400.0.29.202)
Target: x86_64-apple-darwin22.1.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

**g++**

```
apples-Mac-mini-1243:Desktop apple$ g++ -v
Apple clang version 14.0.0 (clang-1400.0.29.202)
Target: x86_64-apple-darwin22.1.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

**gdb**

````
apples-Mac-mini-1243:Desktop apple$ gdb --version
GNU gdb (GDB) 13.2
````

**git**

````
apples-Mac-mini-1243:Desktop apple$ git --version
git version 2.37.1 (Apple Git-137.1)
````



### 3. Linux 开发环境

**centos**

```
[root@localhost home]# cat /etc/redhat-release
CentOS Linux release 7.9.2009 (Core)
```

**cmake**

```
[root@localhost Desktop]# cmake --version
cmake version 3.28.0
```

**gcc**

```
[root@localhost Desktop]# gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/opt/rh/devtoolset-11/root/usr/libexec/gcc/x86_64-redhat-linux/11/lto-wrapper
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,lto --prefix=/opt/rh/devtoolset-11/root/usr --mandir=/opt/rh/devtoolset-11/root/usr/share/man --infodir=/opt/rh/devtoolset-11/root/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --with-linker-hash-style=gnu --with-default-libstdcxx-abi=gcc4-compatible --enable-plugin --enable-initfini-array --with-isl=/builddir/build/BUILD/gcc-11.2.1-20220127/obj-x86_64-redhat-linux/isl-install --enable-gnu-indirect-function --with-tune=generic --with-arch_32=x86-64 --build=x86_64-redhat-linux
Thread model: posix
Supported LTO compression algorithms: zlib
gcc version 11.2.1 20220127 (Red Hat 11.2.1-9) (GCC)
```

**g++**

```
[root@localhost Desktop]# g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/opt/rh/devtoolset-11/root/usr/libexec/gcc/x86_64-redhat-linux/11/lto-wrapper
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,lto --prefix=/opt/rh/devtoolset-11/root/usr --mandir=/opt/rh/devtoolset-11/root/usr/share/man --infodir=/opt/rh/devtoolset-11/root/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --with-linker-hash-style=gnu --with-default-libstdcxx-abi=gcc4-compatible --enable-plugin --enable-initfini-array --with-isl=/builddir/build/BUILD/gcc-11.2.1-20220127/obj-x86_64-redhat-linux/isl-install --enable-gnu-indirect-function --with-tune=generic --with-arch_32=x86-64 --build=x86_64-redhat-linux
Thread model: posix
Supported LTO compression algorithms: zlib
gcc version 11.2.1 20220127 (Red Hat 11.2.1-9) (GCC)
```

**gdb**

```
[root@localhost Desktop]# gdb --version
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-120.el7
```



## 二、目录

[第1章 C++必知必会]()

[第2章 C++ 后端开发必备的工具和调试技巧]()

[第3章 多线程编程与资源同步]()

[第4章 网络编程重难点解析]()

[第5章 网络通信故障排查常用命令]()

[第6章 网络通信协议设计]()

[第7章 单个服务的基本结构]()

[第8章 Redis 网络通信模块源码分析]()

[第9章 服务器开发中的常用模块设计]()
