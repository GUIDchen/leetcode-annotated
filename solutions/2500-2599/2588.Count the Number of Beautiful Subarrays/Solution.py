# 题目：2588. 统计美丽子数组数目（Count the Number of Beautiful Subarrays）
# 思路：子数组「美丽」等价于异或和为 0；用前缀异或 mask 扫描，Counter 记录各前缀异或值出现次数，当前 mask 之前出现 c 次就新增 c 个以当前位置结尾的美丽子数组。
# 时间复杂度：O(n)，哈希均摊 O(1)；空间复杂度：O(n)，最多存 n+1 种前缀异或值。
class Solution:  # LeetCode 约定的题解类
    def beautifulSubarrays(self, nums: List[int]) -> int:  # nums 为输入数组；返回美丽子数组的个数
        cnt = Counter({0: 1})  # 前缀异或值 → 出现次数；0 先记 1 次代表空前缀
        ans = mask = 0  # ans 为答案（方案数可达 O(n^2)），mask 为前缀异或和
        for x in nums:  # 依次遍历每个元素
            mask ^= x  # 把当前元素异或进前缀异或和
            ans += cnt[mask]  # 之前出现过 c 次同样 mask，就新增 c 个美丽子数组
            cnt[mask] += 1  # 把本次出现的 mask 计入哈希表，供后面使用
        return ans  # 返回美丽子数组总数
