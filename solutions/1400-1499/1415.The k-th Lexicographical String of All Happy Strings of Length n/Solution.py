# 题目：1415. 长度为 n 的开心字符串中字典序第 k 小的字符串（The k-th Lexicographical String of All Happy Strings of Length n）
# 思路：按 a、b、c 的字典序回溯拼串，攒够 k 个就剪枝，最后直接取第 k 个。
# 时间复杂度：O(2^n)，开心字符串个数按指数增长（找到 k 个即停止）；空间复杂度：O(k * n)，结果列表与递归深度。
class Solution:  # LeetCode 约定的题解类
    def getHappyString(self, n: int, k: int) -> str:  # n 是目标长度，k 是要求的字典序名次
        def dfs():  # 递归回溯函数，闭包访问外层的 s 与 ans
            if len(s) == n:  # 长度已经达到 n，得到一个开心字符串
                ans.append("".join(s))  # 拼成字符串收进结果列表
                return  # 返回上一层继续搜索
            if len(ans) >= k:  # 已经找到 k 个，剩余分支无需再搜（剪枝）
                return  # 直接返回
            for c in "abc":  # 按字典序依次尝试 a、b、c
                if not s or s[-1] != c:  # 空串可以随便放，否则必须与上一个字符不同
                    s.append(c)  # 选中字符，加入当前路径
                    dfs()  # 递归构造下一位
                    s.pop()  # 撤销选择，回溯

        ans = []  # 结果列表，dfs 内部会往里追加
        s = []  # 当前构造路径，用列表模拟字符栈
        dfs()  # 从空串开始搜索
        return "" if len(ans) < k else ans[k - 1]  # 不足 k 个返回空串，否则取第 k 个（下标 k-1）
