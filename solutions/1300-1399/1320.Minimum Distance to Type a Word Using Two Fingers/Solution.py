# 题目：1320. 二指输入的的最小距离（Minimum Distance to Type a Word Using Two Fingers）
# 思路：三维 DP，f[i][x][y] 表示打完前 i+1 个字母、两指分别在 x、y 键上的最小移动距离，逐字母转移。
# 时间复杂度：O(n·26^3)（含 k 枚举）；空间复杂度：O(n·26^2)，可滚动成一维但此处保留完整表。
class Solution:  # LeetCode 约定的题解类
    def minimumDistance(self, word: str) -> int:  # word 为待输入的单词，两指初始位置可任意选择
        def dist(a: int, b: int) -> int:  # 计算键盘上按键编号 a 与 b 之间的曼哈顿距离
            x1, y1 = divmod(a, 6)  # 每行 6 个字母：divmod 同时得到行与列
            x2, y2 = divmod(b, 6)  # 同理求 b 的行列坐标
            return abs(x1 - x2) + abs(y1 - y2)  # 行差绝对值 + 列差绝对值

        n = len(word)  # 单词长度 n
        f = [[[inf] * 26 for _ in range(26)] for _ in range(n)]  # f[i][x][y]：打完前 i+1 个字母后，一指在 x、另一指在 y 的最小移动距离
        for j in range(26):  # 枚举初始时另一根手指的位置
            f[0][ord(word[0]) - ord('A')][j] = 0  # 第一个字母的按键固定，初始移动代价为 0
            f[0][j][ord(word[0]) - ord('A')] = 0  # 两指左右对称，交换位置是同一个状态
        for i in range(1, n):  # 从第二个字母开始逐个转移
            a, b = ord(word[i - 1]) - ord('A'), ord(word[i]) - ord('A')  # 上一个与当前字母对应的按键编号
            d = dist(a, b)  # 同一根手指从 a 移到 b 的距离
            for j in range(26):  # 枚举另一根手指所处的位置 j
                f[i][b][j] = min(f[i][b][j], f[i - 1][a][j] + d)  # 情形一：打字手指从 a 直接移到 b，另一根不动
                f[i][j][b] = min(f[i][j][b], f[i - 1][j][a] + d)  # 情形二：换另一根手指从 a 移到 b（状态顺序互换）
                if j == a:  # 情形三：另一根手指本来就停在 a，让它去按 b，原打字手指不动
                    for k in range(26):  # 枚举原打字手指可能停留的位置 k
                        t = dist(k, b)  # k 到 b 的移动距离
                        f[i][b][j] = min(f[i][b][j], f[i - 1][k][a] + t)  # 由 f[i-1][k][a] 转移到 f[i][b][j]
                        f[i][j][b] = min(f[i][j][b], f[i - 1][a][k] + t)  # 对称地由 f[i-1][a][k] 转移到 f[i][j][b]
        a = min(f[n - 1][ord(word[-1]) - ord('A')])  # 最后一列的最小值（另一根手指停在最后字母上）
        b = min(f[n - 1][j][ord(word[-1]) - ord('A')] for j in range(26))  # 生成器求另一根手指遍历 26 个键时的最小值
        return int(min(a, b))  # 两种手指分工取较小者，再转成 int 返回
