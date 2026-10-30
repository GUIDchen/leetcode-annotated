# 题目：3371. 识别数组中的最大异常值（Identify the Largest Outlier in an Array）
# 思路：先求总和 s 与每个值的出现次数；假设 x 是异常值，则其余元素之和 t=s-x，其中必须有元素等于 t/2，再取满足条件的最大 x。
# 时间复杂度：O(n)，计数与枚举各一趟；空间复杂度：O(n)，计数器最多保存 n 个不同值。
class Solution:  # LeetCode 约定的题解类
    def getLargestOutlier(self, nums: List[int]) -> int:  # nums 是输入数组，返回其中最大的异常值
        s = sum(nums)  # s 是整个数组的元素之和
        cnt = Counter(nums)  # 计数器：记录每个值出现的次数
        ans = -inf  # 答案先置为负无穷，方便后面取最大值
        for x, v in cnt.items():  # 枚举每个不同的值 x，假设它就是要找的异常值
            t = s - x  # t 是去掉 x 后其余元素之和
            if t % 2 or cnt[t // 2] == 0:  # t 必须为偶数，且 t/2 这个元素在数组中存在（计数不为 0）
                continue  # 该候选不成立，跳过
            if x != t // 2 or v > 1:  # t/2 不能与异常值 x 重合，除非 x 出现了两次以上
                ans = max(ans, x)  # 记录更大的可行异常值
        return ans  # 返回最大异常值
