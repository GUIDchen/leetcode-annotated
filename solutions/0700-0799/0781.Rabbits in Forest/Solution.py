# 题目：781. 森林中的兔子（Rabbits in Forest）
# 思路：回答 x 的兔子说明它所在颜色组共有 x+1 只；按答案分组计数，每组至少需要 ceil(v/(x+1)) 个颜色组，贡献 ceil(v/(x+1))*(x+1) 只兔子。
# 时间复杂度：O(n)，一次计数加一次遍历；空间复杂度：O(n)，Counter 最多保存 n 种答案。
class Solution:  # LeetCode 约定的题解类
    def numRabbits(self, answers: List[int]) -> int:  # answers：每只兔子的回答；返回最少可能的兔子总数
        cnt = Counter(answers)  # Counter 统计每个答案出现的次数：键是答案，值是回答该答案的兔子数
        ans = 0  # ans：累计的最少兔子总数
        for x, v in cnt.items():  # 遍历每种答案 x 及其出现次数 v
            group = x + 1  # 同色组的大小固定为 x+1
            ans += (v + group - 1) // group * group  # (v+group-1)//group 为向上取整的组数，再乘组大小得到该答案至少要占的兔子数
        return ans  # 返回最少兔子总数
