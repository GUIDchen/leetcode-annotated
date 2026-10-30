# 题目：4087. 最多交换 K 次后固定长度子数组的最大和（Maximum Subarray Sum of Fixed Length After at Most K Swaps）
# 核心思路：枚举每个长度为 length 的窗口，把窗口内元素升序、窗口外元素降序；一次交换就是用窗口外最大值换掉窗口内最小值，按「外面第 j 大 vs 里面第 j 小」成对尝试，收益一旦不为正立即停止。可用交换次数受 k、窗口长度与窗口外元素个数共同限制。
# 时间复杂度：O((n-length+1) * n log n)，每个窗口都要排序窗口内外两段；空间复杂度：O(n)，用于暂存临时列表。
class Solution:  # LeetCode 约定的题解类
    def maxSum(self, nums: list[int], length: int, k: int) -> int:  # nums：原数组；length：子数组长度；k：最多交换次数；返回能取得的最大和
        n = len(nums)  # n 为数组长度
        max_swaps = min(k, length, n - length)  # 有效交换次数上限：不超过 k，也不超过窗口内/外的元素个数
        ans = -inf  # ans 记录所有窗口中的最大和，初始取负无穷
        for i in range(n - length + 1):  # 枚举子数组的左端点 i
            internal = sorted(nums[i : i + length])  # 窗口内元素升序，便于依次取出最小的元素
            external = sorted(nums[:i] + nums[i + length :], reverse=True)  # 窗口外元素降序，便于依次取出最大的元素
            total = sum(internal)  # total 为窗口当前和
            for j in range(max_swaps):  # 最多尝试 max_swaps 次交换，第 j 大换第 j 小
                gain = external[j] - internal[j]  # 用外面第 j 大的元素换掉里面第 j 小元素的收益
                if gain <= 0:  # 收益不为正，后面的交换只会更差
                    break  # 提前结束本窗口的交换尝试
                total += gain  # 累加本次交换带来的收益
            ans = max(ans, total)  # 用当前窗口的和更新全局最大值
        return ans  # 返回所有窗口中的最大子数组和
