# 题目：918. 环形子数组的最大和（Maximum Sum Circular Subarray）
# 思路：环形最大和 = max(普通最大子段和, 总和 - 非空最小子段和)，用前缀和的最小/最大值一次扫描求出。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxSubarraySumCircular(self, nums: List[int]) -> int:  # nums 是环形数组（首尾相连）
        pmi, pmx = 0, -inf  # pmi 是最小前缀和（初始 0），pmx 是最大前缀和（初始负无穷）
        ans, s, smi = -inf, 0, inf  # ans 为不环形最大子段和；s 为当前前缀和；smi 为非空最小子段和
        for x in nums:  # 从左到右遍历，边扫描边更新
            s += x  # 累加得到当前前缀和
            ans = max(ans, s - pmi)  # 以当前位置结尾的最大子段和 = 当前前缀和 - 此前最小前缀和
            smi = min(smi, s - pmx)  # 以当前位置结尾的最小子段和 = 当前前缀和 - 此前最大前缀和
            pmi = min(pmi, s)  # 更新最小前缀和，供后续位置使用
            pmx = max(pmx, s)  # 更新最大前缀和，供后续位置使用
        return max(ans, s - smi)  # 取「不环形」与「环形取反」两种情况的较大者
