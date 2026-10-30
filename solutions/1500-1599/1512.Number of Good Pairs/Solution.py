# 题目：1512. 好数对的数目（Number of Good Pairs）
# 思路：用 Counter 记录每个值出现过的次数，当前元素与之前所有同值元素都构成好数对。
# 时间复杂度：O(n)，哈希计数均摊 O(1)；空间复杂度：O(k)，k 为不同取值的个数。
class Solution:  # LeetCode 约定的题解类
    def numIdenticalPairs(self, nums: List[int]) -> int:  # nums：输入数组，返回满足 i<j 且 nums[i]==nums[j] 的下标对数
        ans = 0  # ans：累计的好数对数目
        cnt = Counter()  # Counter 是带默认值 0 的计数字典，访问不存在的键不会报错
        for x in nums:  # 从左到右遍历每个元素
            ans += cnt[x]  # cnt[x] 是 x 此前出现的次数，这些旧下标与当前下标都能配成好数对
            cnt[x] += 1  # 当前元素加入计数，供后面的同值元素统计
        return ans  # 返回好数对总数
