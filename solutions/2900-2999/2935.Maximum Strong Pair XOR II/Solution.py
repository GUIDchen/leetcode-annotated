# 题目：2935. 找出强数对的最大异或值 II（Maximum Strong Pair XOR II）
# 思路：排序后用滑动窗口保证窗口内 max <= 2 * min（窗口内任意两数都是强数对），再用 0/1 字典树在窗口内查与 y 异或最大的值。
# 时间复杂度：O(n log C)，每个数只进出字典树各一次、每次走 21 层；空间复杂度：O(n log C)，字典树结点总量。
class Trie:  # 0/1 字典树：支持插入、删除，以及查询与某数异或的最大值
    __slots__ = ("children", "cnt")  # 用 __slots__ 限定实例属性，省内存也避免属性名拼错

    def __init__(self):  # 构造函数：初始化两个孩子指针和计数
        self.children: List[Trie | None] = [None, None]  # 下标 0 / 1 分别对应该位为 0 / 1 的孩子
        self.cnt = 0  # 经过当前结点的数字个数，删除时靠它判断分支是否还存活

    def insert(self, x: int):  # 把 x 插入字典树
        node = self  # 从根结点出发
        for i in range(20, -1, -1):  # 从第 20 位遍历到第 0 位
            v = x >> i & 1  # 取出 x 的第 i 位
            if node.children[v] is None:  # 该分支还不存在
                node.children[v] = Trie()  # 新建一个结点
            node = node.children[v]  # 沿该分支下行
            node.cnt += 1  # 路径上每个结点计数加一

    def search(self, x: int) -> int:  # 找树中与 x 异或值最大的数，返回该异或值
        node = self  # 从根结点出发
        ans = 0  # 累计异或结果
        for i in range(20, -1, -1):  # 从高位到低位贪心
            v = x >> i & 1  # x 的第 i 位
            if node.children[v ^ 1] and node.children[v ^ 1].cnt:  # 与当前位相反的分支存在且计数非零，就能让这一位异或出 1
                ans |= 1 << i  # 该位异或结果置 1
                node = node.children[v ^ 1]  # 走相反分支继续贪心
            else:  # 否则只能走相同分支
                node = node.children[v]  # 该位异或结果为 0，无需置位
        return ans  # 返回能得到的最大异或值

    def remove(self, x: int):  # 把 x 从字典树中删除（路径计数减一）
        node = self  # 从根结点出发
        for i in range(20, -1, -1):  # 沿与插入相同的路径下行
            v = x >> i & 1  # 计算该位走哪个分支
            node = node.children[v]  # 走到对应孩子
            node.cnt -= 1  # 路径计数减一，减到 0 即视为该数不存在


class Solution:  # LeetCode 约定的题解类
    def maximumStrongPairXor(self, nums: List[int]) -> int:  # nums：输入数组
        nums.sort()  # 原地升序排序，保证左端点是窗口最小值
        tree = Trie()  # 维护当前窗口内所有数字的字典树
        ans = i = 0  # ans：最大异或值；i：滑动窗口左端点下标
        for y in nums:  # y 依次作为窗口右端点，同时也是窗口最大值
            tree.insert(y)  # 右端点入窗口
            while y > nums[i] * 2:  # 最大值超过最小值的两倍，左端点已无法与任何数构成强数对
                tree.remove(nums[i])  # 把左端点从字典树中删掉
                i += 1  # 左端点右移一格
            ans = max(ans, tree.search(y))  # 在窗口内查询与 y 异或最大的值并更新答案
        return ans  # 返回最大异或值
