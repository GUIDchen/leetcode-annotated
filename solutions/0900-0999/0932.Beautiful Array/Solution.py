# 题目：932. 漂亮数组（Beautiful Array）
# 思路：分治构造。把左侧漂亮数组映射成奇数 2x-1、右侧映射成偶数 2x 后拼接；奇偶分离保证不会出现跨度均匀的三元组。
# 时间复杂度：O(n log n)，每层元素总数不超过 n；空间复杂度：O(n)，递归各层结果合起来与 n 同阶。
class Solution:  # LeetCode 约定的题解类
    def beautifulArray(self, n: int) -> List[int]:  # 返回 1..n 的一个排列，使得任意 i<j<k 都不满足 a[i]+a[k] == 2*a[j]
        if n == 1:  # 递归出口：只有一个数时数组本身就是漂亮的
            return [1]  # 长度为 1 的漂亮数组
        left = self.beautifulArray((n + 1) >> 1)  # 奇数部分，长度取上整 (n+1)/2
        right = self.beautifulArray(n >> 1)  # 偶数部分，长度取下整 n/2
        left = [x * 2 - 1 for x in left]  # 上半区映射成奇数 2x-1
        right = [x * 2 for x in right]  # 下半区映射成偶数 2x
        return left + right  # 奇数全在前、偶数全在后，差值为奇数，无法构成等差数列
