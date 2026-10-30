# 3730. 跳跃燃烧的最大卡路里 🔒 / Maximum Calories Burnt from Jumps
# 核心思路：排序后让跳跃高度在最大值与最小值之间交替，每次摆动幅度最大，平方和最大；用双指针从两端向中间构造该顺序。
# 复杂度：时间 O(n log n)，空间 O(1)（排序所需栈空间除外）。
class Solution:  # 定义 LeetCode 解法类
    def maxCaloriesBurnt(self, heights: list[int]) -> int:  # 返回依次跳跃能燃烧的最大卡路里
        heights.sort()  # 升序排序，便于从两端取极值
        pre = 0  # 上一次落脚的高度，起点高度为 0
        l, r = 0, len(heights) - 1  # l 指向最小值，r 指向最大值
        ans = 0  # 答案累加器
        while l < r:  # 双指针向中间收缩
            ans += (heights[r] - pre) ** 2  # 先从当前最大值跳到上一落脚点
            ans += (heights[l] - heights[r]) ** 2  # 再从当前最小值跳到最大值，形成最大落差
            pre = heights[l]  # 更新落脚高度为本次的最小值
            l, r = l + 1, r - 1  # 双指针同时向中间移动
        ans += (heights[r] - pre) ** 2  # 最后从剩余高度跳回最后一次落脚点
        return ans  # 返回总卡路里
