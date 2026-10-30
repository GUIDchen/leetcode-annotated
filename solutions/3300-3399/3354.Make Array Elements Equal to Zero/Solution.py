# 题目：3354. 使数组元素等于零（Make Array Elements Equal to Zero）
# 思路：先求总和 s，再从左向右用 l 累加已扫描元素之和；遇到 0 时比较 l 与 s-l，相等则两个方向都可行，相差 1 则只有一个方向可行。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用总和与左侧和两个变量。
class Solution:  # LeetCode 约定的题解类
    def countValidSelections(self, nums: List[int]) -> int:  # nums：输入数组，0 是可选起点
        s = sum(nums)  # 整个数组的元素总和，用来推算右侧元素和 s - l
        ans = l = 0  # 链式赋值：ans 可行起点数、l 当前零左侧元素和，都从 0 开始
        for x in nums:  # 从左向右扫描，只在遇到 0 时结算
            if x:  # 非零元素，推进左侧和
                l += x  # 把当前元素值累加到左侧和
            elif l * 2 == s:  # 左右两侧元素和相等，向左或向右两个起点都能清零
                ans += 2  # 两个方向都可行，答案加 2
            elif abs(l * 2 - s) == 1:  # 两侧元素和恰好相差 1，只有元素和较大的一侧出发才能精确清零
                ans += 1  # 只算一个方向，答案加 1
        return ans  # 返回可行起点总数
