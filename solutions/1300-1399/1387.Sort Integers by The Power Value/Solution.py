# 题目：1387. 将整数按权重排序（Sort Integers by The Power Value）
# 思路：用记忆化函数算每个数的权重（3x+1 步数），把 [lo, hi] 排序（权重优先、数值次之）后取第 k 个。
# 时间复杂度：O(n log n + n log V)，排序加求权重；空间复杂度：O(n)，缓存权重并保存区间元素。
@cache  # 装饰器缓存：同一个数的权重只计算一次，避免重复模拟
def f(x: int) -> int:  # 计算 x 的权重（变换到 1 所需的步数）
    ans = 0  # 步数计数器
    while x != 1:  # 一直变换直到等于 1
        if x % 2 == 0:  # x 是偶数
            x //= 2  # 整除 2（折半）
        else:  # x 是奇数
            x = 3 * x + 1  # 按 3x+1 规则变换
        ans += 1  # 每完成一次变换，步数加一
    return ans  # 返回总步数


class Solution:  # LeetCode 约定的题解类
    def getKth(self, lo: int, hi: int, k: int) -> int:  # lo..hi 是取值区间，k 是名次
        return sorted(range(lo, hi + 1), key=f)[k - 1]  # 按权重升序排序（稳定排序保证同权重时数值升序），取第 k 小
