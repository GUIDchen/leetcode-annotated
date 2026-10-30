# 题目：1358. 包含所有三种字符的子字符串数目（Number of Substrings Containing All Three Characters）
# 思路：记录 a、b、c 各自最近一次出现的位置；枚举右端点，三种字符都出现过时左端点有 min(三个位置)+1 种选法。
# 时间复杂度：O(n)；空间复杂度：O(1)，字典里固定只有 3 个键。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubstrings(self, s: str) -> int:  # 统计同时包含 a、b、c 三个字符的子串数目
        d = {"a": -1, "b": -1, "c": -1}  # 记录每个字符最近一次出现的位置，-1 表示尚未出现
        ans = 0  # 答案累加器
        for i, c in enumerate(s):  # 从左到右枚举右端点 i
            d[c] = i  # 更新当前字符的最近出现位置
            ans += min(d["a"], d["b"], d["c"]) + 1  # 三种字符齐备时左端点有 min+1 种选法；有字符缺失时 min 为 -1，贡献为 0
        return ans  # 返回合法子串总数
