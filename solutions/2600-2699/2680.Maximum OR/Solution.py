# 题目：2680. 最大或值（Maximum OR）
# 思路：预处理后缀或，再从左到右滚动维护前缀或；枚举把 k 次左移全部用在同一元素上，用「前缀或 | 左移后的值 | 后缀或」更新答案。
# 时间复杂度：O(n)，前后各扫一遍；空间复杂度：O(n)，suf 列表保存后缀或。
class Solution:  # LeetCode 约定的题解类
    def maximumOr(self, nums: List[int], k: int) -> int:  # nums 是整数数组，k 是可以全部作用在同一个数上的左移次数
        n = len(nums)  # 记下数组长度，建表与遍历都要用到
        suf = [0] * (n + 1)  # suf[i] 表示 nums[i..n-1] 的按位或，多留一位给空后缀 0
        for i in range(n - 1, -1, -1):  # 从后往前递推，先算出所有后缀或
            suf[i] = suf[i + 1] | nums[i]  # 当前后缀或 = 后一个后缀或 再或上 nums[i]
        ans = pre = 0  # ans 是最优答案，pre 是 nums[0..i-1] 的前缀或
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            ans = max(ans, pre | (x << k) | suf[i + 1])  # 左移只会让位更高，把它与前后缀的或合并后取最大
            pre |= x  # 把当前元素并入前缀或，供下一个元素使用
        return ans  # 返回能得到的最大按位或值
