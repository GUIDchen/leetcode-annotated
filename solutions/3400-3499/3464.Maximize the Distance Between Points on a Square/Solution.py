# 3464. 正方形上的点之间的最大距离 / Maximize the Distance Between Points on a Square
# 核心思路：把正方形边界上的点按顺时针展开成一维周长坐标，再二分最小间距，用贪心在环上验证能否选出 k 个点。
# 复杂度：时间 O(n k log n log side)，空间 O(n)。
class Solution:  # 定义题解类
    def maxDistance(self, side: int, points: List[List[int]], k: int) -> int:  # 返回任意 k 个点之间最小距离的最大值
        nums = []  # 把边界上的点映射为顺时针周长坐标
        for x, y in points:  # 遍历所有给定点
            if x == 0:  # 点落在左边（x == 0）
                nums.append(y)  # 左边按 y 从下到上编号
            elif y == side:  # 点落在上边（y == side）
                nums.append(side + x)  # 上边从左上角起算
            elif x == side:  # 点落在右边（x == side）
                nums.append(side * 3 - y)  # 右边从右上角向下编号
            else:  # 否则点落在下边
                nums.append(side * 4 - x)  # 下边从右下角向左编号
        nums.sort()  # 按周长坐标升序排序，便于二分找后继点

        def check(lo: int) -> bool:  # 判定能否选出 k 个点，使相邻点顺时针间距都不小于 lo
            for start in nums:  # 枚举第一个点
                end = start + side * 4 - lo  # 最后一个点最晚的坐标，保证首尾绕回后间距也不小于 lo
                cur = start  # 当前已选点坐标
                ok = True  # 该起点是否可行
                for _ in range(k - 1):  # 还需要再选 k-1 个点
                    j = bisect_left(nums, cur + lo)  # 找第一个坐标不小于 cur + lo 的点
                    if j == len(nums) or nums[j] > end:  # 找不到后继点，或后继点超出上界
                        ok = False  # 该起点不可行
                        break  # 提前结束贪心
                    cur = nums[j]  # 选中该点，继续向后贪心
                if ok:  # k 个点已全部选出
                    return True  # 该起点可行，判定成功
            return False  # 所有起点都不可行

        l, r = 1, side  # 答案的二分区间：最小 1，最大为边长
        while l < r:  # 二分最大可行间距
            mid = (l + r + 1) >> 1  # 取上中位数，避免只剩两个元素时死循环
            if check(mid):  # mid 可行，尝试更大间距
                l = mid  # 下界抬到 mid
            else:  # mid 不可行
                r = mid - 1  # 上界降到 mid - 1
        return l  # l 即最大可行最小间距
