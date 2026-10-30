# 题目：1593. 拆分字符串使唯一子字符串的数目最大（Split a String Into the Max Number of Unique Substrings）
# 思路：回溯枚举每个切分点，用集合判重；当「已用子串数 + 剩余字符数」都不优于当前最优时剪枝。
# 时间复杂度：O(n * 2^n)，最坏枚举所有切分并比较子串；空间复杂度：O(n^2)，集合与递归栈存放子串。
class Solution:  # LeetCode 约定的题解类
    def maxUniqueSplit(self, s: str) -> int:  # s 为待拆分的原字符串，返回最多能得到的不同子串个数
        def dfs(i: int):  # 内层回溯函数：从下标 i 开始切分剩余后缀
            nonlocal ans  # 声明改写外层函数的 ans，而不是新建局部变量
            if len(st) + len(s) - i <= ans:  # 剪枝：剩余字符全部单独成段也超不过当前最优
                return  # 该分支无法更优，直接返回
            if i >= len(s):  # 已经切到末尾，说明得到一种完整切分
                ans = max(ans, len(st))  # 用当前不同子串数更新答案
                return  # 返回上层继续尝试别的切法
            for j in range(i + 1, len(s) + 1):  # 枚举本段子串的结束下标 j（切片不含 j）
                if s[i:j] not in st:  # 该子串尚未使用过，才允许选它
                    st.add(s[i:j])  # 选择这一段，加入已用集合
                    dfs(j)  # 从 j 递归切分后面的部分
                    st.remove(s[i:j])  # 撤销选择，恢复集合

        # 闭包变量放在 dfs 之后初始化，内层函数通过作用域直接可见
        ans = 0  # 记录最大不同子串数目
        st = set()  # 保存当前方案已经用过的子串
        dfs(0)  # 从下标 0 开始回溯
        return ans  # 返回最优解
