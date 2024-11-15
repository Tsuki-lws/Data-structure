<h1> 数据结构 Lab1 </h1>
<h3> 负责助教：朱启瑞 </h3>

## 说明

- 请使用 Java/C++ 完成本课程的 Lab 和 Project 代码的编写。<br>
- 本课程的 Lab 将以测试用例的通过情况作为评分的主要依据，请确保你已经在洛谷平台上使用测试用例进行过评分。<br>
- 切勿抄袭！若存在雷同，一经查实，双方按零分处理。<br>
- 截止日期2024年9月17日23:59，将代码打包成 zip ，命名格式为 **学号_姓名_Lab1.zip** ,上传至elearning平台. 同时，你也需要在洛谷平台上提交并运行每道题方能得分。<br>
洛谷：https://www.luogu.com.cn/contest/197250 <br>
邀请码：gs3r


## 任务 

### 1. 实现单链表
请实现一个有头结点的单链表，以及它的指定结点的后插操作和指定结点的删除操作。
- 输入格式：输入的第一行有N个数字，代表链表的N个结点和它们的值。之后每一行有三个值，分别代表操作、指定结点的值和新结点的值。例如“add 6 8”，代表在值为6的结点后插入一个值为8的结点；“delete 5”，代表删除值为5的结点。
- 输出格式：最新的链表中的结点的值按顺序输出，用空格隔开。

#### 样例输入
```
1 2 3 4 5 6
add 6 8
delete 5
```
#### 样例输出
```
1 2 3 4 6 8
```

### 提示
测试样例中保证插入和删除后的链表没有值相同的结点，如果链表中没有结点，输出“None”。


### 2. 挑选队伍
ICPC集训队每年都需要派出一个最强的队伍代表学校参赛，每年都只会从新生中组建新的队伍，而每个队伍在入学m年后就会毕业退役，现在需要你算出每年应该派哪支队伍代表参赛。<br>
- 输入包含n+1行，第一行有四个数字n,m,a,b，表示将有n支队伍，每个队伍的在役时间m，比赛的起始年份a和结束年份b。
- 接下来n行，每行包括三个数字y,score,id，分别表示该队伍的入学年份、能力评分和队伍编号
- 输出包含b-a+1行，每行一个数字，表示从第a年开始当年在役的评分最高的队伍。

#### 样例输入
```
9 5 2012 2018
2012 450 1
2012 430 2
2013 520 3
2014 500 4
2015 480 5
2015 470 6
2016 480 7
2017 470 8
2018 460 9
```
#### 样例输出
```
1
3
3
3
3
3
4
```
