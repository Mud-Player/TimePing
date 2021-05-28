*Build Kit：MSVC2017 X64*

# Qt Creator

## 1.Build

1. 添加环境变量OSG_DIR
2. 使用Qt Creator打开CMakeLists.txt加载工程
3. `Configure Project`界面选择64Bit构建套件
4. 点击左下角构建项目按钮

## 2.Install

1. 切换到`项目`页面，在`Build的步骤`栏右侧下拉`详情`，然后勾选`install`
2. 点击左下角构建项目，相关执行文件将安装到构建目录下的install文件夹

## 3.Run

QtCreator运行程序如果找不到动态库，就会提示`The CDB process terminated`，而且不会像VS一样提示是缺少什么库。下面的方法只是通过QtCreator内建环境变量的方式实现添加动态库运行目录，同样在系统环境变量里面添加也是一样的效果。

1. 切换到`项目`页面，在`构建环境`栏右侧下拉`详情`，然后点击`批量编辑`，添加三个运行时环境变量（语法见Qt的提示)：

   - install文件夹所在路径：${BUILD_DIR}/install（其中${BUILD_DIR)是构建目录）
   - OSG运行库路径：${OSG_DIR}\bin
   - OSG自身依赖库：例如${OSG3rd_Dir}\OSG_3rdParty_v141\x64\bin（其中${OSG3rd_Dir}是OSG第三方依赖库的路径）

2. 运行

# Visual Studio

## 1.Build

1. 法一：转为VS工程

2. 法二：添加环境变量OSG_DIR和Qt5_DIR，然后用VS直接打开CMakeLists.txt

## 2. Install

对`Install`工程执行构建

## 3.Run

对BattleFiledApp工程添加三个运行时环境变量（语法和Qt大致相同，但是注意取变量符号不一样)：

- install文件夹所在路径：${BUILD_DIR}/install（其中${BUILD_DIR)是构建目录）
- OSG运行库路径：${OSG_DIR}\bin
- OSG自身依赖库：例如${OSG3rd_Dir}\OSG_3rdParty_v141\x64\bin（其中${OSG3rd_Dir}是OSG第三方依赖库的路径）