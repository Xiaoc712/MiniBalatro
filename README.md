# Mini Balatro 学习项目

当前是验证 raylib 编译环境用的最小窗口示例，游戏规则将在后续学习中逐步实现。

## 在 VS Code 中打开

选择“文件 → 打开文件夹”，打开 `D:\agent工作区\mini-balatro`。
请把这个项目文件夹作为 VS Code 工作区打开，以便读取其中的 `.vscode` 配置。

## 编译、运行和调试

- `Ctrl+Shift+B`：编译，在项目目录生成 `mini-balatro.exe`。
- `F5`：编译并启动调试，可在代码行号旁点击设置断点。
- 菜单“终端 → 运行任务 → Run Mini Balatro”：编译并运行。
- 窗口打开后，按 `Esc` 或点击关闭按钮退出。

请使用上述任务或 F5；Code Runner 的默认 C 命令通常不包含 raylib 链接参数。

## 环境

- raylib 6.2：`C:\raylib\w64devkit\include` 和 `C:\raylib\w64devkit\lib`。
- GCC 和 GDB：使用 raylib 自带的 `C:\raylib\w64devkit\bin` 工具。
- 不需要修改系统 PATH。项目任务已经显式指定工具路径。

## 接下来学习

1. 读懂 `main.c` 中窗口初始化、主循环和关闭窗口的过程。
2. 定义 `Card` 结构体，生成 52 张互不重复的牌。
3. 实现洗牌和发牌，再逐步加入牌型、计分和盲注流程。

默认字体用于英文提示；以后显示中文时再加载包含中文字形的字体。
