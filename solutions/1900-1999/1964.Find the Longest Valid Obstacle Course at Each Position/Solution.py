# 题目：1964. 找出到每个位置为止最长的有效障碍赛跑路线（Find the Longest Valid Obstacle Course at Each Position）
# 思路：等价于求以每个位置结尾的最长非降子序列长度；把高度去重排序成 1..m 的名次，用树状数组维护按名次的前缀最大值。
# 时间复杂度：O(n log n)，排序加 n 次二分与 BIT 操作；空间复杂度：O(n)，名次表、树状数组与答案各占 O(n)。
class BinaryIndexedTree:  # 树状数组：支持单点「取最大」更新与前缀最大值查询
    __slots__ = ["n", "c"]  # 用 __slots__ 限定属性，省掉实例字典、加快属性访问

    def __init__(self, n: int):  # 构造函数，n 是最大下标
        self.n = n  # 保存范围上界，供 update 循环判断
        self.c = [0] * (n + 1)  # 开 n+1 个位置（下标从 1 开始），默认 0 即最大值单位元

    def update(self, x: int, v: int):  # 把位置 x 的值更新为 max(原值, v)，只增不减
        while x <= self.n:  # 沿 x += lowbit(x) 向上覆盖所有包含 x 的区间
            self.c[x] = max(self.c[x], v)  # 对每个覆盖区间取最大值
            x += x & -x  # 跳到父区间（x 加上自己的最低位 1）

    def query(self, x: int) -> int:  # 查询前缀 [1, x] 上的最大值
        s = 0  # 0 是空区间最大值，也是本题答案的下界
        while x:  # x 非 0 时沿 x -= lowbit(x) 把前缀拆成若干块
            s = max(s, self.c[x])  # 并入当前块的最大值
            x -= x & -x  # 移向下一块（去掉最低位的 1）
        return s  # 返回前缀最大值


class Solution:  # LeetCode 约定的题解类
    def longestObstacleCourseAtEachPosition(self, obstacles: List[int]) -> List[int]:  # obstacles 是障碍高度序列，返回每个位置结尾的最长有效路线长度
        nums = sorted(set(obstacles))  # 去重并排序，把高度压缩成 0..n-1 的名次表
        n = len(nums)  # 不同高度的个数，也是树状数组的规模
        tree = BinaryIndexedTree(n)  # 下标 1..n 对应压缩后各个名次
        ans = []  # 按顺序收集每个位置的答案
        for x in obstacles:  # 按下标顺序依次处理每个障碍
            i = bisect_left(nums, x) + 1  # 二分得到 x 的名次并转成 1 基下标；相同高度共用名次，符合非降序要求
            ans.append(tree.query(i) + 1)  # 高度 <= x 的前缀最大值再加 1，即为以当前位置结尾的最优长度
            tree.update(i, ans[-1])  # 把当前答案写入树状数组，供后面的障碍查询
        return ans  # 返回每个位置的最长有效路线长度
