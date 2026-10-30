# 题目：351. 安卓系统手势解锁（Android Unlock Patterns）
# 思路：预处理 cross[i][j]（i 到 j 必须已使用的中间点），对每个起点回溯 DFS，再用角、边、中心的对称性合并结果。
# 时间复杂度：O(9!)，即所有合法手势路径数；空间复杂度：O(1)，只有 cross、vis 与递归栈。
class Solution:  # LeetCode 约定的题解类
    def numberOfPatterns(self, m: int, n: int) -> int:  # m、n 分别为手势点数的最少值与最多值
        def dfs(i: int, cnt: int = 1) -> int:  # 内层回溯 DFS：i 是当前落点，cnt 是已选点数（起点默认计 1）
            if cnt > n:  # 点数超过上限 n，这条路径不再合法
                return 0  # 该分支贡献 0 种方案
            vis[i] = True  # 标记当前点已被使用，后续点不能再选它
            ans = int(cnt >= m)  # 已选点数达到下限 m 时，当前前缀本身就算一个合法手势
            for j in range(1, 10):  # 枚举下一个可能落下的数字 1~9
                x = cross[i][j]  # 查询从 i 连到 j 需要预先经过的中间点
                if not vis[j] and (x == 0 or vis[x]):  # j 未用过，且中间没有阻挡点或者阻挡点已用过，才允许连接
                    ans += dfs(j, cnt + 1)  # 递归累加以 j 为下一步的合法手势数
            vis[i] = False  # 回溯：撤销使用标记，让其它分支能复用该点
            return ans  # 返回以 i 为起点的合法手势总数

        cross = [[0] * 10 for _ in range(10)]  # cross[i][j] 记录 i 到 j 的中间点，0 表示可直接连（内层函数调用时才读取它）
        cross[1][3] = cross[3][1] = 2  # 1 与 3 之间隔着 2
        cross[1][7] = cross[7][1] = 4  # 1 与 7 之间隔着 4
        cross[1][9] = cross[9][1] = 5  # 1 与 9 之间隔着 5
        cross[2][8] = cross[8][2] = 5  # 2 与 8 之间隔着 5
        cross[3][7] = cross[7][3] = 5  # 3 与 7 之间隔着 5
        cross[3][9] = cross[9][3] = 6  # 3 与 9 之间隔着 6
        cross[4][6] = cross[6][4] = 5  # 4 与 6 之间隔着 5
        cross[7][9] = cross[9][7] = 8  # 7 与 9 之间隔着 8
        vis = [False] * 10  # 记录 1~9 是否已被当前手势使用
        return dfs(1) * 4 + dfs(2) * 4 + dfs(5)  # 利用对称性：四个角各算一次乘 4，四条边各算一次乘 4，中心只算一次
