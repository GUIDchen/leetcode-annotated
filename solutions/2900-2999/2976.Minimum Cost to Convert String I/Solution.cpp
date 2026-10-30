// 题目：2976. 转换字符串的最小成本 I（Minimum Cost to Convert String I）
// 思路：把 26 个小写字母看作结点、转换规则看作带权有向边，先用 Floyd-Warshall 求出任意两字母间的最小转换成本，再逐位累加 source→target 的代价，不可达则返回 -1。
// 时间复杂度：O(26^3 + n)，n 为字符串长度；空间复杂度：O(26^2)，只需一个 26x26 的邻接矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {  // source/target：原串与目标串；original/changed：每条规则的起点、终点字母；cost：对应代价
        const int inf = 1 << 29;  // inf 表示两个字母之间不可达，取 1<<29 保证两次相加也不会溢出 int
        int g[26][26];  // 26x26 的邻接矩阵，g[i][j] 表示字母 i 转成字母 j 的最小成本
        for (int i = 0; i < 26; ++i) {  // 逐行初始化矩阵
            fill(begin(g[i]), end(g[i]), inf);  // 先把第 i 行整行填成不可达
            g[i][i] = 0;  // 自己转成自己的成本为 0
        }  // 矩阵初始化结束

        for (int i = 0; i < original.size(); ++i) {  // 逐条处理转换规则
            int x = original[i] - 'a';  // 起点字母映射到 0..25
            int y = changed[i] - 'a';  // 终点字母映射到 0..25
            int z = cost[i];  // 这条规则的成本
            g[x][y] = min(g[x][y], z);  // 同一对字母可能有多条规则，保留最便宜的一条
        }  // 规则处理结束

        for (int k = 0; k < 26; ++k) {  // Floyd 的中间点 k
            for (int i = 0; i < 26; ++i) {  // 起点 i
                for (int j = 0; j < 26; ++j) {  // 终点 j
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);  // 松弛：借助 k 中转更便宜就更新（允许字母多次间接转换）
                }  // 终点 j 循环结束
            }  // 起点 i 循环结束
        }  // 三重循环结束

        long long ans = 0;  // 累计总成本，用 long long 防止累加溢出
        int n = source.length();  // 逐位比较，所以只需要字符串长度
        for (int i = 0; i < n; ++i) {  // 遍历每一位
            int x = source[i] - 'a';  // 原串该位字母映射到 0..25
            int y = target[i] - 'a';  // 目标串该位字母映射到 0..25
            if (x != y) {  // 字母不同才需要转换；相同则这一位免费
                if (g[x][y] >= inf) {  // 该转换不可达
                    return -1;  // 无法完成转换，按题意返回 -1
                }  // 不可达分支结束
                ans += g[x][y];  // 累加这一位的最小转换成本
            }  // 不同字母分支结束
        }  // 逐位遍历结束
        return ans;  // 返回总成本
    }  // 方法结束
};  // 类定义结束