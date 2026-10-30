# 题目：573. 松鼠模拟（Squirrel Simulation）
# 核心思路：先假设每颗坚果都由树往返搬运，总路程为 2 倍距离和；再枚举第一颗坚果，把这一趟换成从松鼠位置出发。
# 时间复杂度：O(n)，两趟遍历坚果；空间复杂度：O(1)，只额外用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minDistance(  # 求搬运所有坚果所需的最小总路程
        self,  # 当前实例
        height: int,  # 网格行数，本题用不到
        width: int,  # 网格列数，本题用不到
        tree: List[int],  # 树的位置 [行, 列]
        squirrel: List[int],  # 松鼠的初始位置 [行, 列]
        nuts: List[List[int]],  # 所有坚果的位置列表
    ) -> int:  # 返回最小总路程
        tr, tc = tree  # 解包取出树的行列坐标
        sr, sc = squirrel  # 解包取出松鼠的行列坐标
        s = sum(abs(r - tr) + abs(c - tc) for r, c in nuts) * 2  # 假设每颗坚果都从树往返：先求到树的曼哈顿距离和，再乘 2
        ans = inf  # 最优值初始化为正无穷，方便被任何合法方案刷新
        for r, c in nuts:  # 枚举哪颗坚果作为第一颗被搬运
            a = abs(r - tr) + abs(c - tc)  # 该坚果到树的距离，即原方案中的一趟
            b = abs(r - sr) + abs(c - sc)  # 松鼠到该坚果的距离，即新方案中的一趟
            ans = min(ans, s - a + b)  # 用 b 替换 a 得到该方案总路程，取最小
        return ans  # 返回最小总路程
