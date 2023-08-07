/*

 MIT License
 
 Copyright © 2023 Samuel Venable
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include <cstdio>
#include <cstdlib>

#include "system.hpp"

#if defined(_WIN32)
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <io.h>
#else
#include <unistd.h>
#endif

#if defined(_WIN32)
#undef main
#endif

using namespace ngs::sys;

void clear() {
  if (system(nullptr)) {
    if (getenv("SHELL") && 
      os_product_name().find("wine") == std::string::npos)
      system("clear");
    else
      system("cls");
  }
}

void thread(void *args) {
  while (getchar() != '\n');
  clear();
  exit(0);
}

int main() {
  #if defined(_WIN32)
  _beginthread(thread, 0, nullptr);
  #else
  std::thread(thread, nullptr).detach();
  #endif
  while (true) {
    clear();
    std::string str = "\
OS DEVICE NAME: " + os_device_name() + "\n\
OS PRODUCT NAME: " + os_product_name() + "\n\
OS KERNEL NAME: " + os_kernel_name() + "\n\
OS KERNEL RELEASE: " + os_kernel_release() + "\n\
OS ARCHITECTURE: " + os_architecture() + "\n\
CPU PROCESSOR: " + cpu_processor() + "\n\
CPU VENDOR: " + cpu_vendor() + "\n\
CPU CORE COUNT: " + cpu_core_count() + "\n\
CPU PROCESSOR COUNT: " + cpu_processor_count() + "\n\
RANDOM-ACCESS MEMORY TOTAL: " + memory_totalram(true) + "\n\
RANDOM-ACCESS MEMORY USED: " + memory_usedram(true) + "\n\
RANDOM-ACCESS MEMORY FREE: " + memory_freeram(true) + "\n\
SWAP MEMORY TOTAL: " + memory_totalswap(true) + "\n\
SWAP MEMORY USED: " + memory_usedswap(true) + "\n\
SWAP MEMORY FREE: " + memory_freeswap(true) + "\n\
GPU MANUFACTURER: " + gpu_manufacturer() + "\n\
GPU RENDERER: " + gpu_renderer() + "\n\
GPU MEMORY: " + memory_totalvram(true) + "\n";
    std::vector<char> vec(str.begin(), str.end());
    #if defined(_WIN32)
    _write(1, &vec[0], vec.size());
    Sleep(500);
    #else
    write(1, &vec[0], vec.size());
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    #endif
  }
  return 0;
}
