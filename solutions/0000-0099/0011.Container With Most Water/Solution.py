# 题目：11. 盛最多水的容器（Container With Most Water）
# 思路：双指针夹逼；容量由较矮的一侧决定，所以每次移动较矮的指针，丢弃不可能更优的组合。
# 时间复杂度：O(n)，每个下标最多被访问一次；空间复杂度：O(1)，只用了几个变量。
class Solution:  # LeetCode 约定的题解类
    def maxArea(self, height: List[int]) -> int:  # height 是每条竖线的高度
        l, r = 0, len(height) - 1  # 左右指针分别指向最左、最右的竖线
        ans = 0  # 记录目前能盛的最大水量
        while l < r:  # 两指针未相遇，还能围成容器
            t = min(height[l], height[r]) * (r - l)  # 面积 = 较矮一侧高度 × 两指针间距
            ans = max(ans, t)  # 用当前面积刷新答案
            if height[l] < height[r]:  # 左边更矮，它就是容量的瓶颈
                l += 1  # 左指针右移，尝试更高的左边
            else:  # 右边更矮或两边等高
                r -= 1  # 右指针左移，尝试更高的右边
        return ans  # 返回最大面积
