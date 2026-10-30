# 题目：3211. 生成不含相邻零的二进制字符串（Generate Binary Strings Without Adjacent Zeros）
# 思路：DFS 逐位尝试填 0/1，只有首位或上一位为 1 时才允许填 0，递归到长度 n 即得到一个合法串。
# 时间复杂度：O(n · F(n))，结果个数为斐波那契量级；空间复杂度：O(n)，递归与回溯路径深度。
class Solution:  # LeetCode 约定的题解类
    def validStrings(self, n: int) -> List[str]:  # n：目标字符串长度
        def dfs(i: int):  # 递归函数：填第 i 位
            if i >= n:  # 已经填满 n 位
                ans.append("".join(t))  # 把字符列表拼成字符串加入答案
                return  # 结束本层递归
            for j in range(2):  # 依次尝试填入 0 和 1
                if (j == 0 and (i == 0 or t[i - 1] == "1")) or j == 1:  # 填 0 要求是首位或上一位为 1；填 1 永远合法
                    t.append(str(j))  # 把当前位追加到路径末尾
                    dfs(i + 1)  # 递归填下一位
                    t.pop()  # 回溯，撤销本位的选择

        ans = []  # 收集所有合法字符串
        t = []  # 回溯路径，保存当前已构造的前缀
        dfs(0)  # 从第 0 位开始搜索
        return ans  # 返回全部合法字符串
