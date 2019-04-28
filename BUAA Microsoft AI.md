﻿# 76066002
## 1. Three Doors

> 在一个游戏中，主办方在三个门中任选一个，在门后放了一个奖品，另外两个门之后是空的。选手要在三个门中选择一个抽奖。 当选手选择了一个门，未曾打开门之前，主办方打开了另外两个门中没有奖品的那个门，并向选手说， 他可以改变他的选择，即转为选择剩下一个没有打开的门。 请问，如果选手此时改变选择， 他会提高或降低获奖的可能性么？提高多少？请给出你的分析。 写完你的回答后， 你就可以提交 （submit）文件到你的github 中，大家就能能在github 上看到这个文件的提交记录。这个部分写在上述的 Markdown 文件中。

### 对题目的不明白
> 主办方打开了另外两个门中没有奖品的那个门
那假如选手一开始已经选中有奖品的门，主办方会把两个空的门都打开吗？

### 机会自然会更大
一开始有3个门而中将的机会只有1个：1/3的概率
若有N个门，中将的机会为：1/N

### 相对于【换门】的影响
- 最初： A. 1/3 获奖 | B. 1/3 不中 | ~~C. 1/3 不中~~
- A->B，他不会获奖，中奖的概率仍然为1/3
- B->A，他会中奖， 这会提高获奖机会1/3，所以获奖机会变为2/3

## 2. Chinese Room

> 如何看待 “中文房间” 问题，中文房间有智能么？它有什么样水平的智能？如何才能让它具有人类水平的智能？

若说的是整个中文房间的话，那是有智能中的一部分。如何看待有没有智能的这个问题最简单的方式是跟人类对比。中文房间与人类正常的思维有何不同。
这个中文房间，当外面的人发送象形文字时，它会按照手册返回答案，仅此而已。这个操作其实有一点像人的脑子，只是不会记录操作历史。
因为一个真正的专家，真正懂象形文字的人若被问这么一个问题，他脑子的操作其实也是搜索他记忆力，脑海里关于这个问题的答案，然后返回的自然是按照他脑子里的那些记录。
不一样的是，人的脑子会自动记录每件发生的事，说过的话，看过的东西。就算被问“刚才你说什么？”，人的脑子可以搜索脑子里的记录，返回刚刚他说过的话。

到这儿我其实想说，电脑和人类在内涵方面唯一不能被模仿的可能就是感情这件事了，因为我想到就连对人的态度也都可以用程序，按照规律和机器人已定的性子都可以判断的：机器人“喜欢”什么样的人，“讨厌”什么样的人，要怎么做才会使机器人”喜欢“跟你接触。这些都只是大量数据的问题，但唯一不能模仿的就是真正的感情。人与人之间会有偏袒，选择，等等不可预料的事。就连人自己都无法预料，机器人是做不到。人们做出的选择有时候并不一定是最好的，不论从哪个方面看，都不是最好的选择但人们仍然会选它。有的人都不知道自己为何会做出如此选择，这就是偏袒，偏向。但机器人不会，至少目前不会，我认为将来也不会。我们怎么让它偏袒某个选项呢？偏袒某个东西某些事？当然有"Random"这功能，但除此之外没有固定可控的方法了。因为基本上任何机器人在智商这方面并没有什么不同。人类不也是一生下来还什么都不会做，什么都不懂，然后慢慢被教会什么是好什么是不好，什么时候要生气，喜欢什么样的人，这些都是教出来的。也是为什么人在不同的教育下对同样的事会有不同的判断和了解。机器人也是，我们可以教它什么时候要生气，什么时候要难过掉眼泪。

## 3. AI + VR/AR + 3D模型/动画

> 既然这门课讲了很多计算机前沿，那么学生就可以预计一下这些前沿知识如何能给普通用户或某个行业带来好处。 学生根据讲课的内容和参考文献，用 NABCD 的模板，描述你心目中一个使用了 “人工智能+其他前沿技术” 的创新项目。 这个项目应该是由 7 - 10 名有相关技能的大学生在 4 个月能完成。 写完项目提案后，就可以提交 （submit）到你的github 账户中，你可以在github 上看到这个文件的提交记录。你可以提交多次，但是要记住一定要把最后的版本提交上来。这个部分也写在同一个文件中。

### N(eed)
我个人是喜爱研究二次元世界的人，也是个游戏开发工程师。要想让计算机更深入人类的世界里，难免会需要人工智能和虚拟技术。基于个人兴趣，这个“搭配”其实可以做出很多帮助人类的事情：助理，娱乐。娱乐就不多说了，“助理”说起来简单但其实可以帮到很多事。例如，出去旅游事，有手机一扫周围环境，人工智能判断出人的位置并提出人想要的信息。比如人不知道哪里有公交车，扫位置后，人工智能可以根据扫出来的位置告诉人要往哪儿走。去餐厅吃饭，扫描食物“助理”会分析食物的营养素分量，并根据主人的身体状况提意见。

### A(pproach)
1. 建立3D模型以及动画
2. VR/AR技术都可用。VR则需要带眼镜，AR则在电脑/手机上可看
3. 建立数据库包含着一些判断
4. 装上WiFi，所以有些数据也可以通过网上搜索获得的

### B(enefit)
- 有趣和好玩是必然的
- 更有效的管理日常生活，因为有个人助理
- 减少资本，因为不需要招人当助理

### C(ompetitors)
- 且不说现在开始有许多VR游戏。这些VR游戏是已经二次元世界了，只少更厉害的工具和更厉害的人工智能技术。
- AR技术也有许多人在做，就如同Pokemon游戏正是用AR技术。这就是我想要的效果，把整个世界放入到计算机世界里，又或者说把计算机世界带到人的世界里
- 现在个人助理这种系统也有很多，只是其中并没有很人格化的人工智能，我见过用过的也就是简单地说话，回答，推荐，但并没有很像真正的助理

### D(elivery)
这种技术要送到用户的手里，再简单不过了，只是资本可能有些高，毕竟需要VR的眼镜。剩下的也就是开发的问题，做成软件应用/游戏即可用。