## 基于 GIF 的"幻影坦克"与"无影坦克"隐写图实现

### 项目结构

```plaintext
.
├── cmake
│   └── CompilerOptions.cmake
├── CMakeLists.txt
├── lib      # 辅助模块
│   ├── include         # 头文件库
│   ├── file_io         # 数据读写
│   ├── gif_enc         # GIF 编码 & LZW 编解码
│   └── image_sequence  # 动图解码 & 图像基础处理
├── lsb      # LSB 隐写编解码
├── mirage   # "幻影坦克"隐藏图编码
...
