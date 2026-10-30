# 题目：1521. 找到最接近目标值的函数值（Find a Value of a Mysterious Function Closest to Target）
# 核心思路：以 i 结尾的所有子数组按位与最多只有 O(log V) 种取值；用集合滚动维护这些取值，逐一比较与 target 的距离。
# 时间复杂度：O(n log V)，每轮集合大小有限；空间复杂度：O(log V)。
class Solution:  # LeetCode 约定的题解类
    def closestToTarget(self, arr: List[int], target: int) -> int:  # arr：输入数组；target：目标值
        ans = abs(arr[0] - target)  # 只含 arr[0] 的区间作为初始答案
        s = {arr[0]}  # s：以上一个位置结尾的所有按位与结果
        for x in arr:  # 枚举右端点 x
            s = {x & y for y in s} | {x}  # 集合推导：x 与上一轮每种结果再做与，再并上只有 x 的区间
            ans = min(ans, min(abs(y - target) for y in s))  # 在所有这些值中找与 target 距离最小的并更新答案
        return ans  # 返回最小绝对差
