# 题目：519. 随机翻转矩阵（Random Flip Matrix）
# 思路：把 m×n 矩阵看成一维下标 0..total-1，每次随机取一个下标，用哈希表把它映射到区间末尾的真实下标，然后把区间右边界左移，实现 O(1) 的无重复随机抽样。
# 时间复杂度：flip 与 reset 均为 O(1)；空间复杂度：O(k)，k 为已翻转过的格子数。
class Solution:  # LeetCode 约定的题解类
    def __init__(self, m: int, n: int):  # 构造函数：m 行 n 列的矩阵
        self.m = m  # 保存行数
        self.n = n  # 保存列数
        self.total = m * n  # 尚未翻过的格子数，同时用作「剩余区间」的右边界
        self.mp = {}  # 哈希表做「逻辑下标 -> 真实下标」的映射（Fisher-Yates 换位思想）

    def flip(self) -> List[int]:  # 随机翻一个还没翻过的格子，返回 [行, 列]
        self.total -= 1  # 区间右边界左移，把最后一个位置腾出来备替换
        x = random.randint(0, self.total)  # 在剩余下标区间内随机取一个逻辑下标
        idx = self.mp.get(x, x)  # 若 x 已被换走过，就取映射后的真实下标
        self.mp[x] = self.mp.get(self.total, self.total)  # 把区间末尾元素填到 x 的位置，维持「已用区间」的紧凑性
        return [idx // self.n, idx % self.n]  # 一维下标还原成行列坐标

    def reset(self) -> None:  # 重置：让所有格子重新变为未翻转
        self.total = self.m * self.n  # 恢复剩余格子数
        self.mp.clear()  # 清空映射表


# Your Solution object will be instantiated and called as such:
# obj = Solution(m, n)
# param_1 = obj.flip()
# obj.reset()
