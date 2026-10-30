# 题目：1343. 大小为 K 且平均值大于等于阈值的子数组数目（Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold）
# 思路：把「平均值 >= threshold」等价改写为「窗口和 >= threshold * k」，再用定长滑动窗口增量维护窗口和并计数。
# 时间复杂度：O(n)，窗口只滑动一遍；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:  # arr 是原数组，k 是子数组长度，threshold 是平均值阈值
        threshold *= k  # 把阈值放大 k 倍，转成对窗口和的比较，规避浮点误差
        s = sum(arr[:k])  # 第一个长度为 k 的窗口和（切片会复制，但 k 为常数不影响整体量级）
        ans = int(s >= threshold)  # int(bool) 把 True/False 转成 1/0 作为初始计数
        for i in range(k, len(arr)):  # 窗口右端从下标 k 开始向右滑动
            s += arr[i] - arr[i - k]  # 定长窗口增量更新：加上新进的 arr[i]，减去滑出的 arr[i-k]
            ans += int(s >= threshold)  # 达标（True）时 ans 加 1，不达标加 0
        return ans  # 返回满足条件的窗口个数
