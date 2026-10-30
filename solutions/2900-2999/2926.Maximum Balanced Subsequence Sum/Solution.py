# 题目：2926. 平衡子序列的最大和（Maximum Balanced Subsequence Sum）
# 思路：平衡条件 nums[j] - j >= nums[i] - i 等价于关键值 key = nums[i] - i 非降，于是把 key 离散化，用树状数组维护前缀最大值做 DP。
# 时间复杂度：O(n log n)，排序加 n 次树状数组操作；空间复杂度：O(n)，存放离散化数组与树状数组。
class BinaryIndexedTree:  # 树状数组，这里用来维护前缀最大值
    def __init__(self, n: int):  # n 为离散化后的值域大小
        self.n = n  # 保存下标上界 1..n
        self.c = [-inf] * (n + 1)  # 用 -inf 初始化，表示该位置还没有候选值

    def update(self, x: int, v: int):  # 把位置 x 的候选值与 v 取最大值
        while x <= self.n:  # 沿着树状数组的父链向上
            self.c[x] = max(self.c[x], v)  # 每个覆盖 x 的位置都更新最大值
            x += x & -x  # 跳到下一个覆盖 x 的下标

    def query(self, x: int) -> int:  # 查询前缀最大值 max(c[1..x])
        mx = -inf  # 初始为极小值，空查询也安全
        while x:  # 把前缀拆成若干段
            mx = max(mx, self.c[x])  # 合并当前段的最大值
            x -= x & -x  # 去掉最低位的 1，跳到前一段
        return mx  # 返回 [1, x] 的最大值


class Solution:  # LeetCode 约定的题解类
    def maxBalancedSubsequenceSum(self, nums: List[int]) -> int:  # nums 为输入数组
        arr = [x - i for i, x in enumerate(nums)]  # 逐个计算关键值 nums[i] - i
        s = sorted(set(arr))  # 排序去重，得到互不相同的值域
        tree = BinaryIndexedTree(len(s))  # 树状数组大小等于不同关键值的个数
        for i, x in enumerate(nums):  # 按原数组顺序做 DP
            j = bisect_left(s, x - i) + 1  # 当前关键值在 s 中的排名，转成 1 起点下标
            v = max(tree.query(j), 0) + x  # 前面 key 不大于当前 key 的最大和；与 0 取大表示可以只取自己
            tree.update(j, v)  # 把以 i 结尾的最大平衡子序列和写入树状数组
        return tree.query(len(s))  # 全局前缀最大值就是答案
