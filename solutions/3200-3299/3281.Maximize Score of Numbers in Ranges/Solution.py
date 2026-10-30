# 3281. 范围内整数的最大得分（Maximize Score of Numbers in Ranges）
# 核心思路：二分答案。对候选得分 mi，贪心地在每个区间 [st, st+d] 中取不小于「上一个已选值 + mi」的最小值；放不下则 mi 过大，据此二分最大可行 mi。
# 复杂度：时间 O(n log n + n log U)，空间 O(1)，U 为数值范围

class Solution:  # 定义题解类
    def maxPossibleScore(self, start: List[int], d: int) -> int:  # 返回能够取到的最大得分
        def check(mi: int) -> bool:  # 判定：是否能给每个区间选一个数、使相邻两数之差都不小于 mi
            last = -inf  # 上一个选中的数，初始为负无穷
            for st in start:  # 按区间从左到右贪心
                if last + mi > st + d:  # 区间内不存在不小于 last + mi 的数，说明 mi 太大
                    return False  # 该得分不可行
                last = max(st, last + mi)  # 在 [st, st + d] 中取满足间隔要求的最小值
            return True  # 所有区间都能放下，该得分可行

        start.sort()  # 按左端点升序排序，保证贪心自左向右进行
        l, r = 0, start[-1] + d - start[0]  # 二分区间：下界 0，上界取可能的最大跨度
        while l < r:  # 二分寻找最大可行得分
            mid = (l + r + 1) >> 1  # 向上取整的中点，避免死循环
            if check(mid):  # mid 可行
                l = mid  # 答案至少是 mid，向右收缩
            else:  # mid 不可行
                r = mid - 1  # 答案小于 mid，向左收缩
        return l  # 返回最大可行得分
