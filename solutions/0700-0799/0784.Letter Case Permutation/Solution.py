# 题目：784. 字母大小写全排列（Letter Case Permutation）
# 思路：按位置 DFS，该位先按原字符递归，若是字母再切换大小写（字符编码异或 32）递归一次；翻转是对合操作，回溯时不还原也不会漏解或重复。
# 时间复杂度：O(n·2^n)，输出规模即为该量级；空间复杂度：O(n)，递归栈加工作列表。
class Solution:  # LeetCode 约定的题解类
    def letterCasePermutation(self, s: str) -> List[str]:  # s：输入字符串；返回所有字母大小写全排列（数字不变）
        def dfs(i: int) -> None:  # 嵌套函数 dfs：从第 i 位开始决定该位取原样还是切换大小写
            if i >= len(t):  # i 越过末尾，说明得到一个完整排列
                ans.append("".join(t))  # 把字符列表拼成字符串加入结果集
                return  # 结束本分支
            dfs(i + 1)  # 先按原字符递归处理后面的位置
            if t[i].isalpha():  # 只有字母才有可能切换大小写，数字跳过
                t[i] = chr(ord(t[i]) ^ 32)  # ord 取编码，异或 32 完成大小写互换，chr 再转回字符
                dfs(i + 1)  # 切换后再次递归，得到这一位取另一形态的排列

        t = list(s)  # t：把字符串转成列表，便于原地修改某一位的字符
        ans = []  # ans：收集所有排列结果
        dfs(0)  # 从第 0 位开始搜索
        return ans  # 返回全部排列
