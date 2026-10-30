# 题目：2948. 交换得到字典序最小的数组（Make Lexicographically Smallest Array by Swapping Elements）
# 思路：先把所有下标按元素值升序排序；排序后值相差不超过 limit 的连续一段构成互相可达的连通块，块内元素可任意换位。于是把块内原下标升序、元素值升序一一对应填回，就能让较小的值落到较小的下标上。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，排序结果、下标列表与答案数组。
class Solution:  # LeetCode 约定的题解类
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:  # nums 为输入数组，limit 为可交换元素的最大差值，返回字典序最小的数组
        n = len(nums)  # 数组长度
        arr = sorted(zip(nums, range(n)))  # 把 (元素值, 原始下标) 配对后按元素值升序排序
        ans = [0] * n  # 答案数组，先按长度初始化
        i = 0  # 从排序数组的下标 0 开始扫描
        while i < n:  # 逐个处理排序后的连通块
            j = i + 1  # j 从块起点的下一位置开始试探
            while j < n and arr[j][0] - arr[j - 1][0] <= limit:  # 相邻两值之差不超过 limit，说明可以继续并入同一块
                j += 1  # 块右端向右扩
            idx = sorted(k for _, k in arr[i:j])  # 取出块内所有原始下标并升序排列
            for k, (x, _) in zip(idx, arr[i:j]):  # 按位置从小到大与值从小到大一一配对
                ans[k] = x  # 把第 k 小的值放到对应的最小可用下标上
            i = j  # 跳到下一个连通块
        return ans  # 返回字典序最小的结果数组
