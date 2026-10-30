# 题目：2354. 优质数对的数目（Number of Excellent Pairs）
# 思路：优质判据等价于 popcount(a) + popcount(b) ≥ k（按位或与按位与的 1 个数相加恰为两者 popcount 之和）；先去重，按 popcount 用 Counter 计数，再枚举有序对累加个数。
# 时间复杂度：O(n + 32·m)，m 为去重后元素数；空间复杂度：O(m)。
class Solution:  # LeetCode 约定的题解类
    def countExcellentPairs(self, nums: List[int], k: int) -> int:  # nums 可含重复值；k 是优质对的 1 个数阈值
        s = set(nums)  # 去重：重复值不影响 popcount 分布统计
        ans = 0  # 答案累加器，Python 整数不会溢出
        cnt = Counter()  # 计数器：键是 popcount 取值，值是这种 popcount 的元素个数
        for v in s:  # 遍历去重后的每个数
            cnt[v.bit_count()] += 1  # bit_count() 返回二进制中 1 的个数，按此分桶
        for v in s:  # 枚举有序对的第一个数 v
            t = v.bit_count()  # 第一个数的 popcount
            for i, x in cnt.items():  # 枚举第二个数的 popcount 取值 i 及其出现次数 x
                if t + i >= k:  # 按位或与按位与的 1 个数之和等于两者 popcount 之和，判据即 t + i ≥ k
                    ans += x  # 这 x 个元素都能与 v 组成优质对，累加出现次数
        return ans  # 返回优质对总数（有序对，(v, v) 自查也计入）
