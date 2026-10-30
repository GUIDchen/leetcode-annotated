# 题目：1713. 得到子序列的最少操作次数（Minimum Operations to Make a Subsequence）
# 思路：把 target 的值映射成 1 基下标，取出 arr 中命中的下标组成序列，求其最长上升子序列长度 L，答案 = len(target) - L，树状数组加速转移。
# 时间复杂度：O((n + m) log m)；空间复杂度：O(m)。
class BinaryIndexedTree:  # 树状数组：维护前缀最大值，用于求 LIS
    __slots__ = "n", "c"  # 限定实例属性，节省内存并加快属性访问

    def __init__(self, n: int):  # 构造函数：n 为下标上界
        self.n = n  # 记录上界，供 update 与 query 使用
        self.c = [0] * (n + 1)  # 多开一格，1 基下标且全部初始化为 0

    def update(self, x: int, v: int):  # 把位置 x 的最优值更新为 max(原值, v)
        while x <= self.n:  # 沿 lowbit 依次跳到所有覆盖 x 的节点
            self.c[x] = max(self.c[x], v)  # 覆盖节点取最大值
            x += x & -x  # lowbit 向上跳

    def query(self, x: int) -> int:  # 查询前缀 [1, x] 的最大值
        res = 0  # 空集最大值为 0
        while x:  # 沿 lowbit 把前缀拆成若干段
            res = max(res, self.c[x])  # 逐段合并最大值
            x -= x & -x  # lowbit 向下拆
        return res  # 返回前缀最大值，即 LIS 转移来源


class Solution:  # LeetCode 约定的题解类
    def minOperations(self, target: List[int], arr: List[int]) -> int:  # target：目标序列；arr：给定序列
        d = {x: i for i, x in enumerate(target, 1)}  # 值 → target 下标（从 1 开始），字典推导式一次建成
        nums = [d[x] for x in arr if x in d]  # 只保留在 target 中出现过的值对应的下标，保持 arr 的顺序
        m = len(target)  # target 的长度，也是答案的基准值
        tree = BinaryIndexedTree(m)  # 建立树状数组
        ans = 0  # 最长上升子序列（即最长公共子序列）的长度
        for x in nums:  # 依次处理下标序列
            v = tree.query(x - 1) + 1  # 严格上升：只能接在更小的下标后面，故查前缀 x-1
            ans = max(ans, v)  # 更新最优 LIS 长度
            tree.update(x, v)  # 写入以 x 结尾的最优长度
        return len(target) - ans  # target 中不在 LIS 里的元素都需要插入
