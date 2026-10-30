// 题目：1320. 二指输入的的最小距离（Minimum Distance to Type a Word Using Two Fingers）
// 思路：三维 DP，f[i][x][y] 表示打完前 i+1 个字母、两指分别在 x、y 键上的最小移动距离，逐字母转移。
// 时间复杂度：O(n·26^3)（含 k 枚举）；空间复杂度：O(n·26^2)，可滚动成一维但此处保留完整表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDistance(string word) {  // word 为待输入的单词，两指初始位置可任意选择
        int n = word.size();  // 单词长度 n
        const int inf = 1 << 30;  // 用足够大的值表示不可达状态
        vector<vector<vector<int>>> f(n, vector<vector<int>>(26, vector<int>(26, inf)));  // f[i][x][y]：打完前 i+1 个字母后，一指在 x、另一指在 y 的最小移动距离
        for (int j = 0; j < 26; ++j) {  // 枚举初始时另一根手指的位置
            f[0][word[0] - 'A'][j] = 0;  // 第一个字母的按键固定，初始移动代价为 0
            f[0][j][word[0] - 'A'] = 0;  // 两指左右对称，交换位置是同一个状态
        }  // 初始状态初始化结束
        for (int i = 1; i < n; ++i) {  // 从第二个字母开始逐个转移
            int a = word[i - 1] - 'A';  // 上一个字母对应的按键编号
            int b = word[i] - 'A';  // 当前字母对应的按键编号
            int d = dist(a, b);  // 同一根手指从 a 移到 b 的距离
            for (int j = 0; j < 26; ++j) {  // 枚举另一根手指所处的位置 j
                f[i][b][j] = min(f[i][b][j], f[i - 1][a][j] + d);  // 情形一：用打字的那根手指从 a 直接移到 b，另一根不动
                f[i][j][b] = min(f[i][j][b], f[i - 1][j][a] + d);  // 情形二：换另一根手指（状态里的 x、y 互换）从 a 移到 b
                if (j == a) {  // 情形三：另一根手指本来就停在 a，让它去按 b，原打字手指保持不动
                    for (int k = 0; k < 26; ++k) {  // 枚举原打字手指可能停留的位置 k
                        int t = dist(k, b);  // k 到 b 的移动距离
                        f[i][b][j] = min(f[i][b][j], f[i - 1][k][a] + t);  // 由 f[i-1][k][a] 转移到 f[i][b][j]
                        f[i][j][b] = min(f[i][j][b], f[i - 1][a][k] + t);  // 对称地由 f[i-1][a][k] 转移到 f[i][j][b]
                    }  // 内层 k 循环结束
                }  // j == a 分支结束
            }  // j 循环结束
        }  // 字母转移循环结束
        int ans = inf;  // 答案初值设为无穷大
        for (int j = 0; j < 26; ++j) {  // 枚举最后另一根手指所在的位置
            ans = min(ans, f[n - 1][word[n - 1] - 'A'][j]);  // 取最后字母在 x 位上的最小距离
            ans = min(ans, f[n - 1][j][word[n - 1] - 'A']);  // 取最后字母在 y 位上的最小距离，两种手指分工取较优
        }  // 枚举结束
        return ans;  // 返回最小总移动距离
    }  // 方法结束

    int dist(int a, int b) {  // 计算键盘上按键编号 a 与 b 之间的曼哈顿距离
        int x1 = a / 6, y1 = a % 6;  // 每行 6 个字母：键号除以 6 得行、对 6 取余得列
        int x2 = b / 6, y2 = b % 6;  // 同理求 b 的行列坐标
        return abs(x1 - x2) + abs(y1 - y2);  // 行差绝对值 + 列差绝对值
    }  // 辅助函数结束
};  // 类定义结束