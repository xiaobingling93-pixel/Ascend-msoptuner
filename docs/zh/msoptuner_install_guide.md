# MindStudio Ops Tuner安装指南

# 安装说明
MindStudio Ops Tuner（算子Tiling寻优，msOpTuner）是一款用于 CATLASS 模板库算子 Tiling 参数寻优的工具，支持用户自定义搜索空间，能够实例化搜索空间内的所有算子，并批量完成在板性能测试，为算子 Tiling 参数的寻优提供参考依据。本文主要介绍msOpTuner工具的安装方法。  


# 安装前准备
## 更新依赖子仓代码

为了确保代码能够下载成功，需提前在环境中配置git仓库的用户名和秘密信息，方式如下：
配置git存储用户密码，并通过git submodule来下载.gitmodules中的子仓：
```shell
git config --global credential.helper store
git submodule update --init --recursive --depth=1
```
## 环境准备
- Ascend NPU 910B硬件环境

开始构建之前，需要确保已安装编译器bisheng，并且其可执行文件所在路径在环境变量$PATH中(如果已安装cann算子工具包，可在工具包安装路径下执行source set_env.sh).

```shell
source /path/to/Ascend/cann/set_env.sh
```


# 安装步骤
## 项目构建

可以通过如下命令构建：
```shell
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make -j$(nproc)
```
也可以通过一键式脚本来执行：
```shell
python build.py
注：如果本地更改了依赖子仓中的代码，不想构建过程中执行更新动作，可以执行
python build.py local
```

## 测试

```shell
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make -j$(nproc)
```
```shell
cd ../test/
python test_mstuner.py
```

也可以通过一键式脚本来执行：
```shell
python build.py test
```