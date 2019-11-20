# ProgrammingProjects

程序设计课程和数据结构与算法课程实验项目

## 目录结构

```shell
├─BTreeExpression           //数据结构与算法项目3
│  ├─build
│  └─src
├─CardManageSystem          //程序设计项目3
│  ├─build
│  └─src
├─ExpressionEvaluate        //数据结构与算法项目2
│  ├─build
│  └─src
├─NewPolynomialCalculator   //数据结构与算法项目1
│  ├─build
│  └─src
├─PolynomialCalculator      //程序设计项目2
│  ├─build
│  └─src
└─WarehouseManagement       //程序设计项目1
    ├─build
    └─src
```

## 编译方法

请先安装cmake与GNU make并设置好环境变量。
进入项目`build`目录，并执行以下代码：

```bash
cmake -G "Unix Makefiles" ../
make
```

即可在该目录输出可执行文件。
