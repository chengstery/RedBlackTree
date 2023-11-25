# 红黑树接口的使用说明

## Graphviz 文件夹

Graphviz 文件夹下放的工具用于生成可视化的红黑树图片

tree.dot 用于解析的 .dot 文件，解析后可得到树的可视化图片 tree.png

使用例子
```c
system("./Graphviz/bin/dot -Tpng ./tree.dot -o ./tree.png");
```

## SourceCode 文件夹

SourceCode 文件夹下放了所有接口实现的源代码及一些相关代码，这些代码都是在CLion的MinGW编译器实现的，因此不能保证在其他编译器能正常运行(在其他编译器需要经过小修改可能才能编译)。

## RBTree.exe

RBTree.exe 是经过了CLion编译后的可执行程序，基本实现了该有的功能。双击打开就能用。如果不满足则可以通过修改源代码重新编译。