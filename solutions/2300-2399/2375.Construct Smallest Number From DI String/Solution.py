# 题目：2375. 根据模式串构造最小数字（Construct Smallest Number From DI String）
# 思路：从高位到低位按 1..9 升序 DFS 填入未使用的数字，用 pattern 的 I/D 约束剪枝，先搜到的解即字典序最小。
# 时间复杂度：最坏 O(9!) 枚举全排列，实际被约束强剪枝；空间复杂度：O(n)，递归深度与 vis/t 都同阶。
class Solution:  # LeetCode 约定的题解类
    def smallestNumber(self, pattern: str) -> str:  # pattern 只包含 'I' 与 'D'
        def dfs(u):  # u 表示当前要填写的下标位置
            nonlocal ans  # 声明要修改外层函数里的 ans
            if ans:  # 已经找到最优解，就不再继续搜索
                return
            if u == len(pattern) + 1:  # 位数 = 模式长度 + 1，说明数字已填满
                ans = ''.join(t)  # 把字符列表拼成字符串作为答案
                return
            for i in range(1, 10):  # 按 1..9 升序尝试，保证先搜到的是字典序最小的
                if not vis[i]:  # 数字 i 还没有被使用
                    if u and pattern[u - 1] == 'I' and int(t[-1]) >= i:  # I 要求上升，故 i 必须更大
                        continue
                    if u and pattern[u - 1] == 'D' and int(t[-1]) <= i:  # D 要求下降，故 i 必须更小
                        continue
                    vis[i] = True  # 标记数字 i 已被使用
                    t.append(str(i))  # 把 i 追加到当前排列末尾
                    dfs(u + 1)  # 递归填写下一位
                    vis[i] = False  # 回溯：释放数字 i
                    t.pop()  # 回溯：撤销刚追加的字符

        vis = [False] * 10  # 数字 1..9 的使用标记，多开一位让下标与数字对齐
        t = []  # 当前正在构造的排列
        ans = None  # 记录第一个（即最小的）合法解
        dfs(0)  # 从第 0 位开始搜索
        return ans  # 返回字典序最小的数字串
