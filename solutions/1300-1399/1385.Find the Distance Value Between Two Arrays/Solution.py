# 题目：1385. 两个数组间的距离值（Find the Distance Value Between Two Arrays）
# 思路：先排序 arr2，再对 arr1 中每个 x 二分定位第一个 >= x-d 的下标，判断该位置是否已超过 x+d。
# 时间复杂度：O((n+m) log m)，排序加 n 次二分；空间复杂度：O(1)，只用常数个辅助变量。
class Solution:  # LeetCode 约定的题解类
    def findTheDistanceValue(self, arr1: List[int], arr2: List[int], d: int) -> int:  # d 是距离阈值
        arr2.sort()  # 原地排序，为二分查找做准备
        ans = 0  # 统计满足条件的 arr1 元素个数
        for x in arr1:  # 逐个检查 arr1 中的元素
            i = bisect_left(arr2, x - d)  # 第一个 >= x-d 的元素下标
            ans += i == len(arr2) or arr2[i] > x + d  # 越界或该元素已大于 x+d，说明距离都大于 d，布尔值直接参与累加
        return ans  # 返回满足条件的元素个数
