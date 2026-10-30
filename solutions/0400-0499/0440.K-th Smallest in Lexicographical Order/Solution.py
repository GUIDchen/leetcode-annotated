# 题目：440. 字典序的第K小数字（K-th Smallest in Lexicographical Order）
# 思路：把 1..n 看成字典序十叉树，先数出以当前前缀为根的子树节点数 cnt；k >= cnt 就跳过子树换兄弟（curr+1），否则进入子树（curr*10）。
# 复杂度：时间复杂度 O(log^2 n)，最多走 O(log n) 步、每步计数 O(log n)；空间复杂度 O(1)。
class Solution:  # 题解类：求字典序第 k 小的数字
    def findKthNumber(self, n: int, k: int) -> int:  # n 是数值上界，k 是 1-based 的序号，返回第 k 小的数字
        def count(curr):  # 内部辅助函数：数出以 curr 为前缀且不超过 n 的数字个数
            next, cnt = curr + 1, 0  # next 是同层右侧兄弟的前缀，用来界定本层区间；cnt 累计节点数
            while curr <= n:  # 一层一层往下数，直到当前前缀超过 n
                cnt += min(n - curr + 1, next - curr)  # 本层节点数：受上界 n 与右边界 next 双重限制，取较小值
                next, curr = next * 10, curr * 10  # 前缀与右边界同时下沉一层，保持同一层
            return cnt  # 返回整棵前缀子树的节点数

        curr = 1  # 从字典序第一个数 1 出发
        k -= 1  # 改成 0-based 计数：数字 1 本身已经占了第 0 个位置
        while k:  # k 还没归零，说明目标还没走到
            cnt = count(curr)  # 当前前缀子树的节点数
            if k >= cnt:  # 目标不在当前子树里
                k -= cnt  # 把整棵子树跳过
                curr += 1  # 换到下一个兄弟，即前缀加一
            else:  # 否则目标就在当前子树里
                k -= 1  # 先消费掉 curr 自己
                curr *= 10  # 进入子树，走到前缀末尾补零的那个最小数
        return curr  # k 已归零，curr 就是第 k 小的数
