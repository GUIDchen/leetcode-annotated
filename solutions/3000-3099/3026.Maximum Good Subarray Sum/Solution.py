# 题目：3026. 最大好子数组和（Maximum Good Subarray Sum）
# 核心思路：扫描时维护前缀和 s 与哈希表 p（值 → 该值出现位置之前的最小前缀和）；对当前 x，若 x-k 或 x+k 出现过，就用 s 减去对应的最小前缀和更新答案，最后把下一个元素的前缀和按更小值写入表中。
# 时间复杂度：O(n)，每个元素只做常数次哈希查询；空间复杂度：O(n)，哈希表最多保存 n 个不同的值。
class Solution:  # LeetCode 约定的题解类
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：好子数组首尾元素差的绝对值；返回最大子数组和
        ans = -inf  # ans：目前找到的最大子数组和，先置为负无穷
        p = {nums[0]: 0}  # 哈希表：值 → 该值出现位置之前的最小前缀和（首个元素前前缀和为 0）
        s, n = 0, len(nums)  # s：当前前缀和；n：数组长度
        for i, x in enumerate(nums):  # 逐元素扫描，i 是下标，x 是当前元素
            s += x  # 把当前元素累加进前缀和
            if x - k in p:  # 存在与 x 相差 k 的前一个值，能形成好子数组
                ans = max(ans, s - p[x - k])  # 用当前前缀和减去它的最小前缀和，取较大值更新答案
            if x + k in p:  # 另一个方向上存在与 x 相差 k 的值
                ans = max(ans, s - p[x + k])  # 同样用两者前缀和之差更新答案
            if i + 1 < n and (nums[i + 1] not in p or p[nums[i + 1]] > s):  # 还没到末尾，且下一个元素未出现过或表中前缀和更大
                p[nums[i + 1]] = s  # 写入更小的前缀和，使后续算出的子数组和更大
        return 0 if ans == -inf else ans  # 没找到好子数组返回 0，否则返回最大和
