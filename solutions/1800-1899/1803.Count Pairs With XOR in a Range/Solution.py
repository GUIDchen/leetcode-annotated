# 题目：1803. 统计异或值在范围内的数对有多少（Count Pairs With XOR in a Range）
# 思路：区间计数转成前缀差，即「异或 < high+1」减去「异或 < low」；用 01 字典树按位贪心统计已插入元素中与当前数异或小于 limit 的个数。
# 时间复杂度：O(n log C)，C 为值域位数（这里 16 位）；空间复杂度：O(n log C)，字典树节点数。
class Trie:  # 01 字典树节点：children[0]/children[1] 对应该位为 0/1 的子节点
    def __init__(self):  # 构造函数：两个子节点为空，子树计数为 0
        self.children = [None] * 2  # 两个子节点，下标 0 和 1 分别代表二进制的 0 与 1
        self.cnt = 0  # cnt 记录经过本节点的数字个数（该前缀下的数量）

    def insert(self, x):  # 把数字 x 按二进制从高位到低位插入字典树
        node = self  # 从根节点开始向下走
        for i in range(15, -1, -1):  # 从第 15 位遍历到第 0 位（元素值小于 2^16）
            v = x >> i & 1  # 取出 x 的第 i 位，即 0 或 1
            if node.children[v] is None:  # 该位的子节点还不存在
                node.children[v] = Trie()  # 新建一个子节点挂上去
            node = node.children[v]  # 走到对应位的子节点
            node.cnt += 1  # 沿途每个节点的计数加一，供 search 统计

    def search(self, x, limit):  # 统计已插入的数 y 中满足 (x ^ y) < limit 的个数
        node = self  # 从根节点开始比较
        ans = 0  # 累计满足条件的个数
        for i in range(15, -1, -1):  # 逐位比较
            if node is None:  # 前缀不存在，后面的比较都不可能成立
                return ans  # 直接返回已累计的结果
            v = x >> i & 1  # 取出 x 的第 i 位
            if limit >> i & 1:  # limit 这一位是 1：异或位为 0 的分支整棵满足，异或位为 1 的分支继续比
                if node.children[v]:  # 若 y 的该位与 x 相同，异或结果为 0，整棵子树都小于 limit
                    ans += node.children[v].cnt  # 把该子树的计数直接累加
                node = node.children[v ^ 1]  # 再走异或该位为 1 的分支，继续比较是否等于 limit
            else:  # limit 这一位是 0
                node = node.children[v]  # 只能走异或位为 0（与 x 该位相同）的分支才不会超过
        return ans  # 返回满足条件的数字个数


class Solution:  # LeetCode 约定的题解类
    def countPairs(self, nums: List[int], low: int, high: int) -> int:  # 统计 nums 中满足 low <= (nums[i] ^ nums[j]) <= high 的数对个数
        ans = 0  # 答案：满足条件的下标对数量
        tree = Trie()  # 空的 01 字典树，保存已经遍历过的数
        for x in nums:  # 逐个把元素作为右端点，统计它与之前元素的异或
            ans += tree.search(x, high + 1) - tree.search(x, low)  # 「异或小于 high+1」减去「异或小于 low」，即异或落在 [low, high] 内的个数
            tree.insert(x)  # 把当前元素插入字典树，供后面的元素查询
        return ans  # 返回满足条件的数对总数
