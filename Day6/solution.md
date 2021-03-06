# Problem A

## 题解

​	首先找出所有可行的三角形，通过对于度数大小分成大度点和小度点来考虑，小度点枚举所有相邻点的两元组对，这样只要三角形内有小度点就会被统计进去；对于大度点只要枚举所有大度点判断他们之间是否可以构成三角形。然后每条边都更新它们可以构成的权值前三大的三角形。然后枚举每个顶点，他连出的边必然有两条构成了一个最大三角形，用这个三角形去拼和它不相交的三角形；或者用这两条边的第二大、第三大三角形相互匹配，这样就能找出一个蝴蝶型的最大值。

# Problem C

## 题解

​	建SAM。

​	考虑SAM的一段状态，它可以用三元组(p,minlen,maxlen)表示。

​	对于字串s[p-i+1,i]，其中p-i+1>p-maxlen+1且p-i+1<=p-minlen+1，考虑向左延伸一个字符，发现只可能延伸出一种字符(否则不符合SAM状态的性质)，那么只需要在这个状态下查一下对应字符的出边的状态的字符串个数即可。

​	而对于字串s[p-maxlen+1,1]，考虑向左延伸一个字符，这个延伸得到的字符串其实为它在parent_tree上的儿子的状态的字符串，枚举所有的儿子，确定对应的字符，再查看对应出边的状态的字符串个数即可。

# Problem D

## 题解

​	首先每个数字必须都是偶数，从前往后依次为从2开始每次只能在2以内变化。然后考虑从这里连出的边，如果＋2就加入了两条边（数字从这里与之后的某一个交换了）；如果不变就让之前的边继续向前延伸；如果－2就让之前的边中找出两条与这个位置的数字相连（表示数字交换）。从前往后一次枚举就好了。

# Problem E

## 题解

​	可以观察到，如果进入了一颗子树，那么直到这颗子树删完为之都不会到其他子树去，所以我们只需要快速地找出每次最小节点的值，而且支持更新操作，这个可以用dfs序+线段树解决。

​	总体上递归解决就好了。

#Problem F

##题意

​	给定一棵树，求出其拓扑排序个数，要求点V在排列的第K个
​	1 <= N <= 5000
​	
##题解

​	先不考虑点v，整棵树的拓扑排序数可以 树形dp + 组合数 求得，复杂度O(N)。
​	考虑dp状态f[i][j]表示点i为根的排序数，且点V在排列的第j个位置。
​	后代不包含V的子树方案可以用之前的dp方法求出。
​	转移时 f[i][j] <- f[x][k] 其中x是V的祖先，我们需要枚举的只有i，j和k
​	记s[x]为点x的后代数
​	考虑对于点i，x唯一的根据i而确定，k <= s[x]，0 <= j - k <= s[i] - s[x]，这两个约束都是显而易见的
​	那么枚举k和j的过程，就等价的对应了 从x的后代中选择一个点，从i的后代，但不是x的后代中选择一个点，的方案数	
​	并且对于不同的点i，这些选点方案不重复
​	因此总复杂度O(N^2)
​	
#Problem G

##题意

​	给定一张N*M方阵，方阵元素为'X'和'.'，要求将'X'的集合分解为若干矩形框的并，且两两矩形框之间没有交集，两两至多只有一条边相邻

​	N, M <= 2000

##题解

​	XX
​	X.
​	这是一个矩形框开始的标志（也是它的左上角）。
​	以此为依据分割矩形框即可。
​	注意存在这种情况
​	.XXX
​	.X.X
​	.XXX
​	XXX.
​	X.X.
​	XXX.
​	此时可能将(2,3)判断成向下，从而导致错误。
解决方法是向下多判断两位（如果右侧有长度至少为3的矩形，那么左侧的长度也至少要延展3）

​	

# Problem I

## 题解

暴力bitset

首先对于序列上的每个数，分解质因数，对于每个质数，我们得到它在序列上的bitset，1表示该位置上的数能被这个质数整除,0反之。

对于询问，首先将x的所有质因数的bitset或起来，那么我们就是要找到在r左边的第一个bit值为0的位置，暴力扫。

复杂度$O(n^2/64*6)$，超暴力。

