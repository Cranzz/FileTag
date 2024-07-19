# BUG 列表

| 序列号 | 严重程度 | 问题描述                            | 所属模块 | 状态   | 开始时间 |
| ------ | -------- | ----------------------------------- | -------- | ------ | -------- |
|        |          |                                     |          |        |          |
| 002    | 紧急     | 第一次搜索时，不需要到 500 条再显示 | 文件搜索 | 待解决 |          |
| 003    | 严重     | 搜索文件数量过大时，页面卡顿问题    | 文件搜索 | 解决中 | 0719     |
| 004    | 中等     | 解决进度条显示异常问题              | 文件搜索 | 解决中 | 0719     |
|        |          |                                     |          |        |          |



# 解决记录

| 序列号 | 问题描述                     | 结果     | 解决时间 |
| ------ | ---------------------------- | -------- | -------- |
| 005    | 文件搜索结束后，线程不释放   | 不是问题 | 0719     |
| 001    | “搜索线程被中断”，时间有问题 | 解决     | 0719     |
|        |                              |          |          |



# BUG 详情

## 005 文件搜索结束后，线程不释放

![image-20240719103431110](https://blog-imges-1313931661.cos.ap-nanjing.myqcloud.com/image-20240719103431110.png)





# BUG 分析记录

## 003 搜索文件数量过大时，页面卡顿问题 

### 想法

1. 先遍历文件，根据文件总数动态分配线程数目
2. 或者，让搜素完成的线程去搜索其他文件夹，而不是直接释放



## 005 文件搜索结束后，线程不释放

使用了 `QThreadPool` 来管理线程。如果 `QThreadPool` 没有正确回收线程对象，析构函数可能不会被调用。根据 Qt 文档，当一个 `QRunnable`（在这个例子中是 `FileSearchThread`）完成执行后，Qt 不会自动删除该对象。你需要确保线程对象在使用后被正确销毁。