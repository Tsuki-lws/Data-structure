<h1> 数据结构 Lab8 </h1>

## 说明

- 请使用 Java/C++ 完成本课程的 Lab 和 Project 代码的编写。<br>
- 本课程的 Lab 将以测试用例的通过情况作为评分的主要依据，请确保你已经在洛谷平台上使用测试用例进行过评分。<br>
- 切勿抄袭！若存在雷同，一经查实，双方按零分处理。<br>
- 截止日期 年 11 月 19 日23:59，将代码打包成 zip ，命名格式为 **学号_姓名_Lab8.zip** ,上传至elearning 平台. 同时，你也需要在 OJ 系统上提交并运行每道题方能得分。<br>
- 洛谷：https://www.luogu.com.cn/contest/212429 <br>
  - 邀请码：e94c

## 任务 

### 1. 求解关键路径

给定带权有向图，图中的每个节点均代表一个任务，每个边均代表一个活动；一个活动的起始节点为任务A，终点节点为任务B，意味着完成A后才能进行B，同时活动边的权重代表完成任务A的时间开销。本题要求计算得到带权有向图中的关键活动路径:

- 输入格式：
每一行有4个符号i，A，B，k。i代表边（活动）的编号，A和B分别代表该条边的起始结点和终点结点，k代表该条边的权重。测试用例确保图不成环，但是可能存在多个关键活动路径。

- 输出格式：
全部关键活动的编号（从小到大排列）。

### 样例输入

```
1 A B 3
2 A C 2
3 B D 2
4 B E 3
5 C D 4
6 C F 3
7 D F 2
8 E F 1
```

### 样例输出

```
2 5 7
```

