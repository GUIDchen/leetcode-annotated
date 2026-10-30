# 题目：216. 组合总和 III（Combination Sum III）
# 核心思路：回溯枚举 1..9 中递增选择的数字，用剩余和 s 与已选个数两个约束剪枝，凑满 k 个且 s 为 0 时收集答案。
# 时间复杂度：O(C(9,k)) 量级，回溯树上每个合法组合被访问一次；空间复杂度：O(k)，递归深度与路径长度。
class Solution:  # LeetCode 约定的题解类
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:  # 在 1..9 中选 k 个互不相同的数使其和为 n，返回所有组合
        def dfs(i: int, s: int):  # i：下一个可选的数；s：还需要凑出的剩余和
            if s == 0:  # 剩余和为 0，说明已经凑够
                if len(t) == k:  # 并且恰好选了 k 个数才是合法方案
                    ans.append(t[:])  # 复制一份当前路径放进答案（t 之后还会被修改）
                return  # 和为 0 后不该再加数，直接回溯
            if i > 9 or i > s or len(t) >= k:  # 三种剪枝：数字超过 9 / 最小可选数超过剩余和 / 已选够 k 个
                return  # 该分支无解，回溯
            t.append(i)  # 选择数字 i
            dfs(i + 1, s - i)  # 递归：下一个数从 i+1 起选（保证递增不重复），剩余和减去 i
            t.pop()  # 撤销选择，恢复现场
            dfs(i + 1, s)  # 不选 i，直接考虑下一个数

        ans = []  # 存放所有合法组合
        t = []  # 当前递归路径
        dfs(1, n)  # 从数字 1 开始，目标是凑出 n
        return ans  # 返回结果
