# 题目：3020. 子集中元素的最大数量（Find the Maximum Number of Elements in Subset）
# 思路：合法子集必须排列成左右对称的平方链，长度是奇数，除正中间一个值外每个值都要出现偶数次。用 Counter 统计频次，对每个底数沿平方链尽量往上走（每层取 2 个），再单独判断链顶能否取 1 个；x=1 时链退化，按「尽量取奇数长度」处理。
# 时间复杂度：O(n × loglogM)，n 为数组长度、M 为最大值，链长极短；空间复杂度：O(n)，哈希表最多 n 个键值对。
class Solution:  # LeetCode 约定的题解类
    def maximumLength(self, nums: List[int]) -> int:  # nums 是候选集合，返回满足对称平方模式的子集的最大元素个数
        cnt = Counter(nums)  # Counter 统计每个数值的出现次数：键是数值，值是频次
        ans = cnt[1] - (cnt[1] % 2 ^ 1)  # 先单独处理 1 的退化链：1 的平方还是 1，链长必须为奇数，偶数个 1 时只能取 cnt[1]-1 个
        del cnt[1]  # 把 1 从哈希表删掉，避免后面把它当普通底数重复枚举
        for x in cnt:  # 枚举每个出现过的值作为平方链的底数
            t = 0  # t 记录当前这条链能取到的元素个数
            while cnt[x] > 1:  # 只要 x 还有至少 2 个，就能在链的左右两侧各放一个，继续往上平方
                x = x * x  # x 平方得到链的上一层
                t += 2  # 同一层左右各取一个，元素个数 +2
            t += 1 if cnt[x] else -1  # 链顶只能放 1 个：该值还存在就 +1，否则上一层多算了 1 个要减回来
            ans = max(ans, t)  # 用当前链长更新答案
        return ans  # 返回子集的最大元素个数
