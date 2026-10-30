# 题目：17. 电话号码的字母组合（Letter Combinations of a Phone Number）
# 思路：逐位做字符串的笛卡尔积，ans 保存所有已拼好的前缀，每读一位就把它与每个候选字母两两组合。
# 时间复杂度：O(4^n · n)，每个组合长度为 n，分支因子最多 4；空间复杂度：O(4^n · n)，用于存放全部结果。
class Solution:  # LeetCode 约定的题解类
    def letterCombinations(self, digits: str) -> List[str]:  # digits 是数字串
        if not digits:  # 空输入
            return []  # 返回空列表，而不是含空串的列表
        d = ["abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]  # 下标 0..7 依次对应数字 2..9
        ans = [""]  # 初始只有一个空前缀，作为笛卡尔积的单位元
        for i in digits:  # 逐位处理数字字符
            s = d[int(i) - 2]  # 取出该数字对应的候选字母，'2' 映射到下标 0
            ans = [a + b for a in ans for b in s]  # 列表推导做笛卡尔积：每个旧前缀与每个候选字母拼接
        return ans  # 返回所有字母组合
