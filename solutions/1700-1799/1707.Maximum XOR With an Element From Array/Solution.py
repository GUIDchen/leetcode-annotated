# 题目：1707. 与数组中元素的最大异或值（Maximum XOR With an Element From Array）
# 思路：把询问按阈值 m 升序处理，同时把 nums 升序后用「只增不减」的指针依次插入 01 字典树；每次查询从高位贪心走相反位，即得所有不超过 m 的元素中的最大异或值。
# 时间复杂度：O((n + q) × 31)，排序另有 O(n log n + q log q)；空间复杂度：O(n × 31)，字典树节点数。
class Trie:  # 01 字典树节点：children[0]/children[1] 对应当前二进制位的 0 或 1
    __slots__ = ["children"]  # 限制实例属性，每个节点只允许有 children，既省内存又加快属性访问

    def __init__(self):  # 构造函数：初始化新节点的孩子数组
        self.children = [None] * 2  # 两个孩子先置空，表示尚无任何前缀被插入

    def insert(self, x: int):  # 把整数 x 的 31 个二进制位（第 30 位到第 0 位）插入字典树
        node = self  # 从当前节点（根）开始向下走
        for i in range(30, -1, -1):  # 从第 30 位到第 0 位枚举，高位在前
            v = x >> i & 1  # 取出 x 的第 i 位，结果只能是 0 或 1
            if node.children[v] is None:  # 该位的分支还不存在
                node.children[v] = Trie()  # 为该位新建一个节点挂上去
            node = node.children[v]  # 沿该位对应的分支继续下移

    def search(self, x: int) -> int:  # 在树中找与 x 异或值最大的元素并返回该最大值；树为空或走不通时返回 -1
        node = self  # 从根节点开始按位匹配
        ans = 0  # 累积最大异或结果的各个二进制位
        for i in range(30, -1, -1):  # 从高位到低位贪心：高位能取 1 就优先取 1
            v = x >> i & 1  # x 当前位的值
            if node.children[v ^ 1]:  # 存在与 x 该位相反的节点，异或后这一位为 1，是最优选择
                ans |= 1 << i  # 把结果的第 i 位置 1
                node = node.children[v ^ 1]  # 走相反的那条分支
            elif node.children[v]:  # 否则尝试走与 x 相同的分支，该位异或结果为 0
                node = node.children[v]  # 沿相同分支继续下移
            else:  # 两个孩子都不存在，说明树是空的或已走到死路
                return -1  # 没有可用元素，按题意返回 -1
        return ans  # 查询结束，返回最大异或值


class Solution:  # LeetCode 约定的题解类
    def maximizeXor(self, nums: List[int], queries: List[List[int]]) -> List[int]:  # nums：候选数组；queries 每项是 [x, m]，表示只能在不超过 m 的元素中选
        trie = Trie()  # 空的 01 字典树，只保存满足 nums[j] <= 当前 m 的元素
        nums.sort()  # 升序排序，便于按阈值 m 从小到大逐步插入
        j, n = 0, len(queries)  # j 指向下一个待插入元素，n 是询问总数
        ans = [-1] * n  # 答案数组，按原始询问顺序存放
        for i, (x, m) in sorted(zip(range(n), queries), key=lambda x: x[1][1]):  # 按各自询问的 m 升序处理，同时保留原下标 i 以便回填答案
            while j < len(nums) and nums[j] <= m:  # 把所有不超过 m 的 nums 元素一次性插入字典树
                trie.insert(nums[j])  # 插入当前元素
                j += 1  # 指针前移，保证每个元素只插入一次
            ans[i] = trie.search(x)  # 在树上贪心求出与 x 异或最大的值，写到原下标位置
        return ans  # 按原顺序返回所有询问的答案
