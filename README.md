# DRM APP Neo 的EEZ Studio设计工程及输出

EEZ 版本：V0.24.0

## 为什么要分开成独立的repo？

我希望保持生成文件与EEZ Studio的关联关系。也就是 我不希望更改到它生成的UI代码，这样后续我还可以直接用EEZ来更改文件生成UI。

作用主要是提醒大家：在隔壁主仓库不要直接改生成的文件。就算直接在那边编辑器改了，更改不会被staging，也不会push到git

## 如果你clone了这个仓库直接修改src

6