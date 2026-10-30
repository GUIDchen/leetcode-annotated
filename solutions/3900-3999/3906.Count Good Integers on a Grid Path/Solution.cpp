// 3906. 统计网格路径中好整数的数目（Count Good Integers on a Grid Path）
// 思路：先由 directions 求出 4x4 网格路径上哪些数位受「不小于前一位」的约束，再用数位 DP 统计 [0, x] 内满足约束的 16 位数，最后用前缀和相减得到 [l, r] 的答案。
// 复杂度：时间复杂度 O(16*10*10)，记忆化后每个状态只计算一次；空间复杂度 O(16*10)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countGoodIntegersOnPath(long long l, long long r, string directions) {  // 统计 [l, r] 中满足路径约束的整数个数，directions 给出路径
        bool key[16];  // key[p] 表示路径第 p 个数位是否被约束成「不小于前一位」
        memset(key, 0, sizeof(key));  // 初始化为全部无约束
        int row = 0, col = 0;  // 当前路径在 4x4 网格中的位置
        key[0] = true;  // 起点（第 0 位）有约束
        for (char c : directions) {  // 沿 directions 逐位前进
            if (c == 'D') {  // 向下走：行号加一
                row++;  // 行坐标前移
            } else {  // 否则向右走：列号加一
                col++;  // 列坐标前移
            }  // 方向判断结束
            key[row * 4 + col] = true;  // 路径经过的数位被标记为有约束
        }  // 路径预处理结束

        long long f[16][10];  // 数位 DP 记忆化表：f[数位][上一位数字]
        string s;  // 当前上界 x 补零到 16 位后的字符串

        auto dfs = [&](this auto&& dfs, int pos, int last, bool lim) -> long long {  // pos：当前数位；last：上一位数字；lim：是否紧贴上界
            if (pos == 16) {  // 16 位全部填完，得到一个合法整数
                return 1;  // 计数加一
            }  // 递归出口结束
            if (!lim && f[pos][last] != -1) {  // 非紧上界且已经算过，直接复用记忆化结果
                return f[pos][last];  // 返回缓存值
            }  // 记忆化判断结束

            long long res = 0;  // 当前状态的方案数
            int start = key[pos] ? last : 0;  // 有约束的数位必须不小于上一位
            int end = lim ? (s[pos] - '0') : 9;  // 紧贴上界时只能取到上界当前位的数字

            for (int i = start; i <= end; i++) {  // 枚举当前位可填的数字
                res += dfs(pos + 1, key[pos] ? i : last, lim && (i == end));  // 递归下一位；只有本行也贴上界才继续受限
            }  // 数字枚举结束

            if (!lim) {  // 非紧上界的状态才是通用状态
                f[pos][last] = res;  // 写入记忆化表
            }  // 记忆化写入结束
            return res;  // 返回当前状态的方案数
        };  // DFS 定义结束

        auto calc = [&](long long x) {  // 计算 [0, x] 内的合法整数个数
            if (x < 0) {  // 负数没有合法整数
                return 0LL;  // 返回 0
            }  // 边界判断结束
            string t = to_string(x);  // 把上界转成字符串
            s = string(16 - t.length(), '0') + t;  // 左侧补零到 16 位，低位对齐数位 DP
            memset(f, -1, sizeof(f));  // 每个上界都要清空记忆化表
            return dfs(0, 0, true);  // 从最高位开始，初始紧贴上界
        };  // calc 定义结束

        return calc(r) - calc(l - 1);  // 前缀和相减得到 [l, r] 的答案
    }  // 方法结束
};  // 类定义结束
