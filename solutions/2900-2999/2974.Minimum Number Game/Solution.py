# 题目：2974. 最小数字游戏（Minimum Number Game）
# 思路：原地把 nums 变成小根堆，每轮弹出两个最小值，Bob 先放入较小的 b，Alice 再放入较大的 a。
# 时间复杂度：O(n log n)，堆化 O(n) 加 n/2 轮弹出；空间复杂度：O(n)，答案数组额外存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def numberGame(self, nums: List[int]) -> List[int]:  # nums：输入数组，返回重排后的数组
        heapify(nums)  # heapify 原地建小根堆，比逐个 heappush 更快做到 O(n)
        ans = []  # 收集答案的列表
        while nums:  # 每轮消耗两个元素，堆空则游戏结束
            a, b = heappop(nums), heappop(nums)  # 连续弹出两个最小值：a 最小，b 次小
            ans.append(b)  # Bob 拿较小的 b，先进入结果
            ans.append(a)  # Alice 拿较大的 a，后进入结果
        return ans  # 返回最终排列
