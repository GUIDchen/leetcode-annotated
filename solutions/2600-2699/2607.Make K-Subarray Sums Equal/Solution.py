# 题目：2607. 使子数组元素和相等（Make K-Subarray Sums Equal）
# 思路：把下标按 g = gcd(n, k) 分成若干同余类，同一类里的元素必须相等；每类取中位数作为目标值，累加绝对差即为最小代价。
# 时间复杂度：O(n log n)，类内排序的总代价不超过 O(n log n)；空间复杂度：O(n)，临时数组最多保存一整类元素。
class Solution:  # LeetCode 约定的题解类
    def makeSubKSumEqual(self, arr: List[int], k: int) -> int:  # arr 是输入数组，k 是子数组长度，返回最小代价
        n = len(arr)  # n：数组长度
        g = gcd(n, k)  # g = gcd(n, k)：下标同余类的个数
        ans = 0  # ans：累计的最小总代价
        for i in range(g):  # 依次处理每个同余类
            t = sorted(arr[i:n:g])  # 切片步长为 g，正好取出整个同余类 i, i+g, i+2g, ...
            mid = t[len(t) >> 1]  # 右移一位等价于整除 2，取中位数作为目标值
            ans += sum(abs(x - mid) for x in t)  # 累加每个元素到中位数的绝对差
        return ans  # 返回总的最小代价
