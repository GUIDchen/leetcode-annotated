# 题目：1539. 第 k 个缺失的正整数（Kth Missing Positive Number）
# 思路：前 i+1 个位置上缺失的正整数个数是 arr[i] - i - 1，随 i 单调不减，二分出第一个缺失数不小于 k 的位置，再由它左边一个元素回推答案。
# 时间复杂度：O(log n)，一次二分；空间复杂度：O(1)，只用常数个变量。
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:  # arr：严格递增的正整数数组；k：要找第 k 个缺失的正整数
        if arr[0] > k:  # 最小元素都比 k 大，说明 1..k 全部缺失
            return k  # 答案就是 k
        left, right = 0, len(arr)  # 二分区间取 [left, right)，right = len(arr) 允许答案落在数组末尾之后
        while left < right:  # 区间里还有元素就继续二分
            mid = (left + right) >> 1  # 取中点，>> 1 等价于除以 2
            if arr[mid] - mid - 1 >= k:  # arr[mid] - mid - 1 就是前 mid+1 个位置中缺失的正整数个数
                right = mid  # 缺失数已经不少于 k，答案在左半段，收缩右边界
            else:  # 缺失数还不够 k
                left = mid + 1  # 答案在右半段，left 右移
        return arr[left - 1] + k - (arr[left - 1] - (left - 1) - 1)  # arr[left-1] 之前已缺失 arr[left-1]-(left-1)-1 个，补上还差的 k 这么多即可
