# 题目：2604. 吃掉所有谷子的最短时间（Minimum Time to Eat All Grains）
# 思路：二分答案 t；check(t) 按位置顺序贪心，每只母鸡先吃左侧近处谷子，必要时折返向右，判断能否在 t 内吃完全部谷子。
# 时间复杂度：O((n + m) log C)，C 为时间上界；空间复杂度：O(1) 额外空间（排序自身 O(log) 栈）。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, hens: List[int], grains: List[int]) -> int:  # hens：母鸡位置；grains：谷子位置；返回吃完所有谷子的最短时间
        def check(t):  # 判定函数：给定时间 t，判断能否吃完全部谷子（闭包读取外层 m）
            j = 0  # j 是下一颗还没吃到的谷子下标
            for x in hens:  # 按位置顺序，让每只母鸡覆盖尽可能多的谷子
                if j == m:  # 所有谷子都吃完了
                    return True  # 提前返回可行
                y = grains[j]  # 下一颗待吃谷子的位置
                if y <= x:  # 谷子在母鸡左侧或就在脚下
                    d = x - y  # d：母鸡需要向左走的距离
                    if d > t:  # 走到最左那颗谷子就已超时
                        return False  # 该时间不可行
                    while j < m and grains[j] <= x:  # 吃掉左侧紧邻、无需折返的谷子
                        j += 1  # 向右推进待吃下标
                    while j < m and min(d, grains[j] - x) + grains[j] - y <= t:  # 折返向右时，用 min(左行距离, 右侧距离) 计算总耗时
                        j += 1  # 仍在时间预算内就继续向右覆盖
                else:  # 谷子都在母鸡右侧
                    while j < m and grains[j] - x <= t:  # 距离不超过 t 就能一路向右吃完
                        j += 1  # 继续推进
            return j == m  # 母鸡全部用完，判断是否已吃完全部谷子

        hens.sort()  # 母鸡位置排序，固定从左到右的分配顺序
        grains.sort()  # 谷子位置排序，保证贪心顺序单调
        m = len(grains)  # 谷子数量，供 check 闭包使用
        r = abs(hens[0] - grains[0]) + grains[-1] - grains[0] + 1  # 上界 +1：range(r) 右开，需要覆盖到可行解本身
        return bisect_left(range(r), True, key=check)  # 二分第一个使 check 为 True 的时间，即最小可行时间
