#<center>CMAKE使用<center/>
##内部构建和外部构建
内部构建(in-sourcebuild)，而 cmake 强烈推荐的是外部构建(out-of-source build)。

“内部构建”，相信看到生成的临时文件比您的代码文件还要多的时候，
估计这辈子你都不希望再使用内部构建。

外部编译的过程如下：
1. 首先，请清除 t1 目录中除 main.c CmakeLists.txt 之外的所有中间文件，最关键
的是 CMakeCache.txt。
2. 在 t1 目录中建立 build 目录，当然你也可以在任何地方建立 build 目录，不一定必
须在工程目录中。
3. 进入 build 目录，运行 cmake ..(注意,..代表父目录，因为父目录存在我们需要的
CMakeLists.txt，如果你在其他地方建立了 build 目录，需要运行 cmake <工程的全
路径>)，查看一下 build 目录，就会发现了生成了编译需要的 Makefile 以及其他的中间
文件.
4. 运行 make 构建工程，就会在当前目录(build 目录)中获得目标文件 hello。
上述过程就是所谓的 out-of-source 外部编译，一个最大的好处是，对于原有的工程没
有任何影响，所有动作全部发生在编译目录。通过这一点，也足以说服我们全部采用外部编
译方式构建工程。

语法解释：
> ADD_SUBDIRECTORY 指令:
`ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])`
这个指令用于向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存
放的位置。EXCLUDE_FROM_ALL 参数的含义是将这个目录从编译过程中排除，比如，工程
的 example，可能就需要工程构建完成后，再进入 example 目录单独进行构建(当然，你
也可以通过定义依赖来解决此类问题)。
上面的例子定义了将 src 子目录加入工程，并指定编译输出(包含编译中间结果)路径为
bin 目录。如果不进行 bin 目录的指定，那么编译结果(包括中间结果)都将存放在
build/src 目录(这个目录跟原有的 src 目录对应)，指定 bin 目录后，相当于在编译时
将 src 重命名为 bin，所有的中间结果和目标二进制都将存放在 bin 目录。
这里需要提一下的是 SUBDIRS 指令，使用方法是：
SUBDIRS(dir1 dir2...)，但是这个指令已经不推荐使用。它可以一次添加多个子目录，
并且，即使外部编译，子目录体系仍然会被保存。
如果我们在上面的例子中将 ADD_SUBDIRECTORY (src bin)修改为 SUBDIRS(src)。
那么在 build 目录中将出现一个 src 目录，生成的目标代码 hello 将存放在 src 目录中

##安装
INSTALL 指令包含了各种安装类型，我们需要一个个分开解释：
> 目标文件的安装：
```
INSTALL(TARGETS targets...
[[ARCHIVE|LIBRARY|RUNTIME]
[DESTINATION <dir>]
[PERMISSIONS permissions...]
[CONFIGURATIONS
[Debug|Release|...]]
[COMPONENT <component>]
[OPTIONAL]
] [...])
```
参数中的 TARGETS 后面跟的就是我们通过 ADD_EXECUTABLE 或者 ADD_LIBRARY 定义的
目标文件，可能是可执行二进制、动态库、静态库。
目标类型也就相对应的有三种，ARCHIVE 特指静态库，LIBRARY 特指动态库，RUNTIME
特指可执行目标二进制。
DESTINATION 定义了安装的路径，如果路径以/开头，那么指的是绝对路径，这时候
CMAKE_INSTALL_PREFIX 其实就无效了。如果你希望使用 CMAKE_INSTALL_PREFIX 来
定义安装路径，就要写成相对路径，即不要以/开头，那么安装后的路径就是
${CMAKE_INSTALL_PREFIX}/<DESTINATION 定义的路径

> 一个疑问
如果我没有定义 CMAKE_INSTALL_PREFIX 会安装到什么地方？
你可以尝试以下，cmake ..;make;make install，你会发现
CMAKE_INSTALL_PREFIX 的默认定义是/usr/local

##静态库与动态库构建

我们解释一下一个新的
指令 ADD_LIBRARY
```
ADD_LIBRARY(libname [SHARED|STATIC|MODULE]
[EXCLUDE_FROM_ALL]
source1 source2 ... sourceN)
```

你不需要写全 libhello.so，只需要填写 hello 即可，cmake 系统会自动为你生成
libhello.X
类型有三种:
* SHARED，动态库
* STATIC，静态库
* MODULE，在使用 dyld 的系统有效，如果不支持 dyld，则被当作 SHARED 对待。

EXCLUDE_FROM_ALL 参数的意思是这个库不会被默认构建，除非有其他的组件依赖或者手
工构建。

### 如果我们把上面的 hello 修改为 hello_static:
`ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})`

就可以构建一个 libhello_static.a 的静态库了。
这种结果显示**不是我们想要的**，我们需要的是名字相同的静态库和动态库，因为 target 名
称是唯一的，所以，我们肯定不能通过 ADD_LIBRARY 指令来实现了。这时候我们需要用到
另外一个指令：
SET_TARGET_PROPERTIES，其基本语法是：
```
SET_TARGET_PROPERTIES(target1 target2 ...
PROPERTIES prop1 value1
prop2 value2 ...)
```

这条指令可以用来设置输出的名称，对于动态库，还可以用来指定动态库版本和 API 版本。

###本小节，我们谈到了：
如何通过 ADD_LIBRARY 指令构建动态库和静态库。
如何通过 SET_TARGET_PROPERTIES 同时构建同名的动态库和静态库。
如何通过 SET_TARGET_PROPERTIES 控制动态库版本
最终使用上一节谈到的 INSTALL 指令来安装头文件和动态、静态库。
