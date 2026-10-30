# 题目：2509. 查询树中环的长度（Cycle Length Queries in a Tree）
# 思路：完全二叉树中节点 x 的父节点是 x // 2，加边 (a,b) 后环长 = a、b 到最近公共祖先的边数之和再加 1；每次让编号大的节点上跳，直到两者相等。
# 时间复杂度：O(q log n)，q 为查询条数；空间复杂度：O(1)，除答案数组外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def cycleLengthQueries(self, n: int, queries: List[List[int]]) -> List[int]:  # n 是完全二叉树节点数，queries 是待查询的节点对
        ans = []  # 按查询顺序保存每个环的长度
        for a, b in queries:  # 逐条处理查询，a、b 是本次新加边连接的两个节点
            t = 1  # 环长初值为 1：新加的那条边本身算一条边
            while a != b:  # 两个节点尚未走到最近公共祖先时继续上跳
                if a > b:  # 编号较大的节点一定更深，先让它上跳
                    a >>= 1  # 右移一位即除以 2，得到父节点编号
                else:  # 否则让 b 上跳
                    b >>= 1  # b 的父节点编号为 b // 2
                t += 1  # 每上跳一条边，环就多一条边
            ans.append(t)  # 此时 a == b 即最近公共祖先，t 就是该环的边数
        return ans  # 返回所有查询对应的环长
