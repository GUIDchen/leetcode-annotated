# 题目：2355. 你能拿走的最大图书数量（Maximum Number of Books You Can Take 🔒）
# 思路：把约束 books[j] - j ≤ books[i] - i 变形后，用单调栈求每个 i 左边最近的 nums 更小值位置作边界，边界内按等差数列求和，并用 dp 累加出以 i 为最高层的最优解。
# 时间复杂度：O(n)，每个下标进出栈各一次；空间复杂度：O(n)，nums、left、dp 与栈。
class Solution:  # LeetCode 约定的题解类
    def maximumBooks(self, books: List[int]) -> int:  # books 是每层书架的书数，返回最多能拿走的书数
        nums = [v - i for i, v in enumerate(books)]  # 变形为 nums[i] = books[i] - i，之后比较 nums 等价于比较原约束
        n = len(nums)  # 书架层数
        left = [-1] * n  # left[i] 是以 i 为最高层时递减序列能延伸到的最左位置（初值 -1 表示可到开头）
        stk = []  # 单调栈，存下标，对应 nums 值单调递增
        for i, v in enumerate(nums):  # 从左到右扫描，逐个求左边界
            while stk and nums[stk[-1]] >= v:  # 弹出所有 nums 值 ≥ 当前值的下标
                stk.pop()  # 出栈：这些下标不再是候选左边界
            if stk:  # 栈非空说明找到了左侧严格更小的位置
                left[i] = stk[-1]  # 记录左边界下标
            stk.append(i)  # 当前下标入栈，供后面的元素使用
        ans = 0  # 全局答案：最多能拿走的书数
        dp = [0] * n  # dp[i]：以第 i 层为最高层时的最大取书数
        dp[0] = books[0]  # 只有第 0 层时，最多拿走 books[0] 本
        for i, v in enumerate(books):  # 逐层递推
            j = left[i]  # 左边界下标，-1 表示可以一直延伸到第 0 层
            cnt = min(v, i - j)  # 递减序列长度：受本层书数与到左边界距离双重限制
            u = v - cnt + 1  # 递减到的最低一层的书数
            s = (u + v) * cnt // 2  # 等差数列求和：从 u 到 v 共 cnt 项
            dp[i] = s + (0 if j == -1 else dp[j])  # 加上左边界之前的最优解（没有左边界时补 0）
            ans = max(ans, dp[i])  # 更新全局最大值
        return ans  # 返回最大取书数
