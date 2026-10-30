# 题目：3010. 将数组分成最小总代价的子数组 I（Divide an Array Into Subarrays With Minimum Cost I）
# 思路：第一个子数组必须包含首元素，所以总代价 = nums[0] + 其后最小的两个元素；一次遍历同时维护最小值与次小值即可。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, nums: List[int]) -> int:  # nums 是输入数组；返回把数组切成三个子数组的最小总代价
        a, b, c = nums[0], inf, inf  # a 固定取首元素（第一段代价）；b、c 记录后面出现过的最小值与次小值，inf 表示暂时还没有
        for x in nums[1:]:  # 首元素已被第一段固定，只在 nums[1:] 里挑最小的两个
            if x < b:  # 当前值比已知最小值还小，原来的最小值要让位
                c, b = b, x  # 元组赋值：同时完成「旧 b 变成次小值、x 变成最小值」
            elif x < c:  # 不比最小值小但比次小值小，只需要更新次小值
                c = x  # 刷新次小值
        return a + b + c  # 返回三段代价之和：首元素加后面最小的两个元素
