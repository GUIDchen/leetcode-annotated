# 题目：786. 第 K 个最小的质数分数（K-th Smallest Prime Fraction）
# 思路：每个分母 j 先配最小的分子 arr[0]，把这 n-1 个 (分数值, 分子下标, 分母下标) 建成小根堆，弹 k-1 次并补入同分母的下一个分子。
# 时间复杂度：O((n + k) log n)；空间复杂度：O(n)，堆中最多 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:  # arr 是升序质数数组，k 是目标名次（从 1 开始）
        h = [(1 / y, 0, j + 1) for j, y in enumerate(arr[1:])]  # 元组是 (分数值, 分子下标, 分母下标)；每个分母先配最小分子 0
        heapify(h)  # 原地调整为小根堆
        for _ in range(k - 1):  # 只需弹出前 k-1 个最小值，剩下的堆顶就是第 k 小
            _, i, j = heappop(h)  # 弹出当前最小值，同时拿到它的分子、分母下标
            if i + 1 < j:  # 同一分母下还有下一个分数（分子必须小于分母）
                heappush(h, (arr[i + 1] / arr[j], i + 1, j))  # 把该分母的下一个分数补进堆，保证候选不遗漏
        return [arr[h[0][1]], arr[h[0][2]]]  # 堆顶即第 k 小分数，返回它的分子值与分母值
