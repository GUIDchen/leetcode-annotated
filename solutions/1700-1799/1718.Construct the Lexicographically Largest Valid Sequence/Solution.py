# 题目：1718. 构建字典序最大的可行序列（Construct the Lexicographically Largest Valid Sequence）
# 思路：DFS 回溯。从左往右填位置，每个位置优先放大数字 i（从 n 到 2），把 i 同时放在 u 与 u+i；大数字都放不下时才放 1。先大后小保证第一个解即字典序最大。
# 时间复杂度：O(n!)（回溯剪枝后远小于此）；空间复杂度：O(n)，递归栈与 path/cnt 数组。
class Solution:
    def constructDistancedSequence(self, n: int) -> List[int]:
        def dfs(u):  # 内部 dfs：尝试填第 u 个位置（path、cnt 来自外层闭包）
            if u == n * 2:  # 所有位置都填满，构造成功
                return True  # 返回成功标志，逐层向上传递
            if path[u]:  # 该位置已被前一个数字占据
                return dfs(u + 1)  # 直接尝试下一个位置
            for i in range(n, 1, -1):  # 从大到小尝试数字，保证字典序最大
                if cnt[i] and u + i < n * 2 and path[u + i] == 0:  # i 还有剩余次数，且第二个位置不越界、未被占用
                    cnt[i] = 0  # 标记 i 已用完
                    path[u] = path[u + i] = i  # 两个相距 i 的位置同时填入 i
                    if dfs(u + 1):  # 继续填下一个空位
                        return True  # 成功则逐层返回
                    path[u] = path[u + i] = 0  # 回溯：清空刚才填入的两个位置
                    cnt[i] = 2  # 回溯：恢复 i 的可用次数
            if cnt[1]:  # 大数字都放不下时，尝试只出现一次的 1
                cnt[1], path[u] = 0, 1  # 在 u 处放 1，并标记 1 已使用
                if dfs(u + 1):  # 继续搜索后续位置
                    return True  # 成功则逐层返回
                path[u], cnt[1] = 0, 1  # 回溯：撤销 1 的放置
            return False  # 当前位置放不下任何数字，搜索失败

        path = [0] * (n * 2)  # 结果序列长度 2n-1，多留一格便于 1 基下标
        cnt = [2] * (n * 2)  # 每个数字最多出现两次（1 稍后改成 1 次）
        cnt[1] = 1  # 数字 1 只出现一次
        dfs(1)  # 从第 1 个位置开始搜索
        return path[1:]  # 去掉 0 号哨兵，返回 1..2n-1
