# 题目：1711. 大餐计数（Count Good Meals）
# 思路：遍历时用计数器记录此前各美味值出现的次数；对当前值 d 枚举所有不超过「最大值两倍」的 2 的幂 s，累加 cnt[s-d]，即以 d 为较大下标的所有美味配对。
# 时间复杂度：O(n log M)，M 为最大美味值，枚举的 2 的幂约 21 个；空间复杂度：O(n)，计数器保存不同美味值。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, deliciousness: List[int]) -> int:  # deliciousness：每道菜的美味程度数组
        mod = 10**9 + 7  # 结果取模的常数
        mx = max(deliciousness) << 1  # 两数之和的上界是最大值的两倍，超过它的 2 的幂不可能被凑出
        cnt = Counter()  # 计数器：记录已经遍历过的每个美味值出现了多少次
        ans = 0  # 满足「和为 2 的幂」的配对数
        for d in deliciousness:  # 逐个取当前美味值 d，在它之前出现过的元素中物色搭档
            s = 1  # 从最小的 2 的幂 1 开始枚举目标和
            while s <= mx:  # 目标和不超过上界时才可能被凑出
                ans = (ans + cnt[s - d]) % mod  # 需要的搭档是 s-d，把它此前出现的次数累加进答案并取模
                s <<= 1  # 左移一位，枚举下一个 2 的幂
            cnt[d] += 1  # 把当前值计入计数器，供后面的元素统计配对
        return ans  # 返回配对总数
