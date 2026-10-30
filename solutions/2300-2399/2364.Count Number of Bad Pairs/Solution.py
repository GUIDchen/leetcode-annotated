# 题目：2364. 统计坏数对的数目（Count Number of Bad Pairs）
# 思路：好数对满足 nums[j] - nums[i] == j - i，等价于 i - nums[i] == j - nums[j]；用哈希表记录差值出现过的次数。
# 时间复杂度：O(n)，哈希操作均摊 O(1)；空间复杂度：O(n)，哈希表最多存 n 个不同的差值。
class Solution:  # LeetCode 约定的题解类
    def countBadPairs(self, nums: List[int]) -> int:  # nums 是输入数组，返回坏数对总数
        cnt = Counter()  # 计数器：键是差值 i - nums[i]，值是此前出现的次数
        ans = 0  # 坏数对总数，Python 整数不会溢出
        for i, x in enumerate(nums):  # 同时取得下标 i 和元素值 x
            ans += i - cnt[i - x]  # 以 i 为右端点的数对共 i 个，减去同差值的好数对个数
            cnt[i - x] += 1  # 更新该差值的出现次数，供后面的位置使用
        return ans  # 返回坏数对总数
