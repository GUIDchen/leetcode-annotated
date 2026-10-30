# 题目：2600. K 件物品的最大和（K Items With the Maximum Sum）
# 思路：贪心先拿价值最高的 1，再拿 0，最后才拿 -1，三段按剩余件数依次结算即可。
# 时间复杂度：O(1)，只有常数次比较；空间复杂度：O(1)，只用参数和临时比较结果。
class Solution:  # LeetCode 约定的题解类
    def kItemsWithMaximumSum(  # 函数签名跨行书写：numOnes/numZeros/numNegOnes 是 1、0、-1 的个数，k 是要取的件数
        self, numOnes: int, numZeros: int, numNegOnes: int, k: int  # 逐个声明四个参数的类型：三个数量与总件数 k
    ) -> int:  # 返回最大和（int）
        if numOnes >= k:  # 情况一：1 足够多，全部取 1，和就是 k
            return k  # 直接返回每件都取 1 的和
        if numZeros >= k - numOnes:  # 情况二：1 不够、但加上 0 后够 k 件，剩下的用 0 补
            return numOnes  # 0 不改变和，答案就是所有 1 的和
        return numOnes - (k - numOnes - numZeros)  # 情况三：1 和 0 都不够，剩余件数只能取 -1，每件减一
