# 题目：421. 数组中两个数的最大异或值（Maximum XOR of Two Numbers in an Array）
# 思路：把所有数按二进制位从高到低插入 0/1 字典树；查询时贪心地优先走相反位分支，让高位尽量为 1，从而得到最大异或值。
# 时间复杂度：O(n * 31)，每个数插入与查询各 31 步；空间复杂度：O(n * 31)，字典树节点数。
class Trie:  # 二进制字典树：每个节点最多两个子节点，分别对应下一位是 0 还是 1
    __slots__ = ("children",)  # __slots__ 限定实例属性，减少内存开销

    def __init__(self):  # 构造函数：初始化两个子节点
        self.children: List[Trie | None] = [None, None]  # children[0] 对应下一位为 0 的分支，children[1] 对应下一位为 1 的分支，初始都为空

    def insert(self, x: int):  # 把数字 x 的二进制位从高到低插入字典树
        node = self  # 从根节点开始向下走
        for i in range(30, -1, -1):  # 从第 30 位枚举到第 0 位（数值小于 2 的 31 次方，第 31 位符号位不用管）
            v = x >> i & 1  # 取出 x 的第 i 位（0 或 1）
            if node.children[v] is None:  # 该位对应的子节点还没建立
                node.children[v] = Trie()  # 新建一个字典树节点挂上去
            node = node.children[v]  # 沿该位对应的分支继续向下

    def search(self, x: int) -> int:  # 查询 x 与树中已有数字能异或出的最大值
        node = self  # 从根节点开始
        ans = 0  # ans 累积最优异或结果
        for i in range(30, -1, -1):  # 同样从高位到低位逐位决策
            v = x >> i & 1  # 取出 x 的第 i 位
            if node.children[v ^ 1]:  # 存在相反位分支时，这一位异或结果为 1，更优
                ans |= 1 << i  # 把答案的第 i 位置为 1
                node = node.children[v ^ 1]  # 走向相反位分支
            else:  # 否则只能走相同位的分支，这一位异或结果为 0
                node = node.children[v]  # 走向相同位分支
        return ans  # 返回本次查询能得到的最大值


class Solution:  # 题解类
    def findMaximumXOR(self, nums: List[int]) -> int:  # nums 是输入数组，返回任取两个数异或能得到的最大值
        trie = Trie()  # 建一棵空的字典树
        for x in nums:  # 先把所有数字都插入树中
            trie.insert(x)  # 逐个插入
        return max(trie.search(x) for x in nums)  # 用每个数在树中查询最优异或值，取最大值返回
