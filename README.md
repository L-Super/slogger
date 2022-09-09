# 日志库

封装自spdlog

头文件为`vvlog.h`

命名空间 `vv`

## 使用说明

关于打印级别，严重程度递增：

- trace：描述事件的日志级别，显示代码的逐步执行，在标准操作期间可以忽略。
- debug： 当需要更详细的信息时，使用此调试信息。
- info：应用程序的运行过程中，输出一些提示信息。
- warn：应用程序内部发生了意外行为，但它仍在继续工作，关键业务功能按预期运行。
- error：一项或多项功能无法正常工作，导致某些功能无法正常工作。
- critical：一项或多项关键业务功能不起作用，整个系统无法实现业务功能。

**通常使用`info` - `critical`级别即可。**

### 控制台打印输出

仅打印到控制台

```cpp
vv::info()
vv::warn()
vv::error()
vv::critical()
vv::trace()
vv::debug()
```

### 控制台文件同时打印输出

同时打印到控制台及文件。出于性能原因，日志信息不会立即刷新到文件中，默认运行结束后刷新，后可根据情况进行调整。

```cpp
vv::vvInfo();
vv::vvWarn();
vv::vvError();
vv::vvCritical();
vv::vvDebug();
vv::vvTrace();
```

### 调试模式输出

推荐使用`VINFO()`代替`vv::info()`，因为此方法比`vv::info()`形式更好，可以打印时，带有文件名-函数名-行号格式，方便开发调试过程中的快速定位。

```
VTRACE()
VDEBUG()
VINFO()
VWARN()
VERROR()
VCRITICAL()
```

## 代码示例

```cpp
#include "string"
#include "vvlog.h"

int main()
{
   std::string str{"hello world"};
   vv::vvTrace("trace");//not display
   vv::vvDebug("debug");//not display
   vv::vvInfo(str);
   vv::vvWarn("{} {} {} {}","this","is","a",str);
   vv::vvError("{} != {}",1,2);

   vv::vvSetGlobalLevel(vv::vvLevel::trace);
   vv::vvTrace("display now");
   VDEBUG("display now too");
   VINFO("hello info");
   VWARN(str);
   return 0;
}
```

输出：

```
[2022-09-09 15:05:48.340] [vvlog] [info] hello world
[2022-09-09 15:05:48.341] [vvlog] [warning] this is a hello world
[2022-09-09 15:05:48.342] [vvlog] [error] 1 != 2
[2022-09-09 15:05:48.342] [vvlog] [trace] display now
[2022-09-09 15:05:48.342] [vvlog] [debug] [example.cpp:14] display now too
[2022-09-09 15:05:48.343] [vvlog] [info] [example.cpp:16] hello info
[2022-09-09 15:05:48.343] [vvlog] [warning] [example.cpp:17] hello world
```

更多示例：

```cpp
vv::info("Welcome");
vv::error("Some error message with arg: {}", 1);
vv::warn("Easy padding in numbers like {:08d}", 12);
vv::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
vv::info("Support for floats {:03.2f}", 1.23456);
vv::info("Positional args are {1} {0}..", "too", "supported");
vv::info("{:<30}", "left aligned");
```

## 注意

默认不会打印trace,debug级别日志，需要设置日志级别。

```cpp
vv::vlogger::instance().vSetLevel(vv::vvLevel::trace);
```

同时，vv::info等仅打印到控制台不受影响。若要开启debug显示，使用以下语句开启全局日志级别设置

```cpp
vv::vvSetGlobalLevel(vv::vvLevel::trace);
```





----

