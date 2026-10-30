# 题目：1375. 二进制字符串前缀一致的次数（Number of Times Binary String Is Prefix-Aligned）
# 思路：扫描翻转序列，维护已翻转位置的最大值 mx；第 i 步若 mx == i，说明前 i 个位置恰好全部被翻成 1，前缀一致。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用到几个整型变量。
class Solution:  # LeetCode 约定的题解类
    def numTimesAllBlue(self, flips: List[int]) -> int:  # flips 是 1..n 的一个排列，返回前缀一致的次数
        ans = mx = 0  # ans 计次数；mx 是前 i 次翻转出现过的最大位置
        for i, x in enumerate(flips, 1):  # 从 1 开始枚举，i 同时表示已翻转次数与前缀长度
            mx = max(mx, x)  # 更新已翻转位置的最大值
            ans += mx == i  # mx == i 时前 i 位全为 1，前缀一致，ans 加一（布尔值当 0/1 用）
        return ans  # 返回计数结果
