# 题目：823. 带因子的二叉树（Binary Trees With Factors）
# 思路：排序后用字典记录「数值 → 下标」。f[i] 表示以 arr[i] 为根的方案数：枚举因子对，若两个因子都在数组中，就累加 f[j]*f[c]，最后对所有 f 求和。
# 时间复杂度：O(n²)，双重枚举因子；空间复杂度：O(n)，dp 列表与下标字典。
class Solution:  # LeetCode 约定的题解类
    def numFactoredBinaryTrees(self, arr: List[int]) -> int:  # arr：可选作节点值的数组
        mod = 10**9 + 7  # 取模常数
        n = len(arr)  # 元素个数
        arr.sort()  # 排序，保证因子一定排在倍数前面
        idx = {v: i for i, v in enumerate(arr)}  # 数值 → 下标 的映射
        f = [1] * n  # f[i]：以 arr[i] 为根的合法二叉树个数，单节点也算 1 种
        for i, a in enumerate(arr):  # 依次把每个元素当作根
            for j in range(i):  # 只枚举比 a 小的因子，避免重复统计
                b = arr[j]  # 候选因子 b
                if a % b == 0 and (c := (a // b)) in idx:  # b 整除 a 且另一个因子 c 也在数组中
                    f[i] = (f[i] + f[j] * f[idx[c]]) % mod  # 左子树 f[j] 种、右子树 f[c] 种，相乘后累加
        return sum(f) % mod  # 所有根作为整棵树根的情况求和
