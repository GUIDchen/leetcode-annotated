# 题目：3804. 中心子数组的数量（Number of Centered Subarrays）
# 思路：枚举左端点并向右扩展，用集合记录子数组中出现的值、用变量累计元素和，若和恰好在集合中则计数。
# 时间复杂度：O(n^2)，双重循环枚举所有子数组；空间复杂度：O(n)，每个左端点用一个集合记录出现过的值。
class Solution:  # LeetCode 约定的题解类
    def centeredSubarrays(self, nums: List[int]) -> int:  # 统计满足「存在元素等于子数组和」的子数组个数
        n = len(nums)  # 数组长度
        ans = 0  # 满足条件的子数组个数
        for i in range(n):  # 枚举子数组左端点 i
            st = set()  # 记录当前子数组中出现过的元素
            s = 0  # 当前子数组的元素和
            for j in range(i, n):  # 枚举右端点 j，逐步把子数组向右扩展
                s += nums[j]  # 累加新元素到和
                st.add(nums[j])  # 把新元素加入集合
                if s in st:  # 子数组和恰好是子数组里出现过的某个元素
                    ans += 1  # 计数加一
        return ans  # 返回答案
