// 题目：1659. 最大化网格幸福感（Maximize Grid Happiness）
// 思路：按行做三进制状态压缩 DP，预处理单行幸福度 f 与相邻两行幸福度 g，再用记忆化搜索分配内向/外向者数量。
// 时间复杂度：O(m · 3^n · 3^n · I · E)；空间复杂度：O(m · 3^n · I · E)，即记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {  // m 行 n 列；introvertsCount 内向者人数；extrovertsCount 外向者人数
        int mx = pow(3, n);  // 每行用三进制状态压缩（0 空 / 1 内向 / 2 外向），共 3^n 种行状态
        int f[mx];  // f[状态]：该行自身的幸福感（含同行相邻两人的影响）
        int g[mx][mx];  // g[a][b]：上一行状态 a、当前行状态 b 时同列上下相邻带来的幸福感
        int bits[mx][n];  // bits[状态][列]：把状态按三进制展开后的每一位人员类型
        int ix[mx];  // ix[状态]：该行状态用掉的内向者数量
        int ex[mx];  // ex[状态]：该行状态用掉的外向者数量
        int memo[m][mx][introvertsCount + 1][extrovertsCount + 1];  // memo[行号][上一行状态][剩余内向][剩余外向]：记忆化缓存
        int h[3][3] = {{0, 0, 0}, {0, -60, -10}, {0, -10, 40}};  // 相邻两人的幸福感增量表：h[自己类型][邻居类型]
        memset(f, 0, sizeof(f));  // f 清零，准备累加
        memset(g, 0, sizeof(g));  // g 清零，准备累加
        memset(bits, 0, sizeof(bits));  // bits 清零，后面逐个写入
        memset(ix, 0, sizeof(ix));  // 内向者计数清零
        memset(ex, 0, sizeof(ex));  // 外向者计数清零
        memset(memo, -1, sizeof(memo));  // memo 全部置 -1，表示该状态尚未计算过
        for (int i = 0; i < mx; ++i) {  // 枚举所有行状态
            int mask = i;  // 拷贝一份三进制数，用于逐位拆解
            for (int j = 0; j < n; ++j) {  // 逐列取出该行每个人的人员类型
                int x = mask % 3;  // 取最低位：当前列的类型
                mask /= 3;  // 右移一位（除以 3），继续处理下一列
                bits[i][j] = x;  // 记录第 i 种状态第 j 列的类型
                if (x == 1) {  // 1 表示内向者
                    ix[i]++;  // 内向者计数加一
                    f[i] += 120;  // 内向者自身基础幸福感 120
                } else if (x == 2) {  // 2 表示外向者
                    ex[i]++;  // 外向者计数加一
                    f[i] += 40;  // 外向者自身基础幸福感 40
                }  // 人员类型分支结束
                if (j) {  // j 非 0 说明左边还有邻居
                    f[i] += h[x][bits[i][j - 1]];  // 加上与左邻的相互影响（查表 h）
                }  // 内层条件结束
            }  // 列循环结束
        }  // 状态枚举结束
        for (int i = 0; i < mx; ++i) {  // 枚举上一行（或上一行的等价状态）
            for (int j = 0; j < mx; ++j) {  // 枚举当前行状态
                for (int k = 0; k < n; ++k) {  // 逐列统计同列上下两人的相互影响
                    g[i][j] += h[bits[i][k]][bits[j][k]];  // 累加上下行同列两人的幸福感增量
                }  // 列循环结束
            }  // 当前行状态循环结束
        }  // 上一行状态循环结束
        function<int(int, int, int, int)> dfs = [&](int i, int pre, int ic, int ec) {  // 定义递归函数：i 当前行号、pre 上一行状态、ic/ec 剩余人数
            if (i == m || (ic == 0 && ec == 0)) {  // 边界：填完所有行，或两种人都不剩
                return 0;  // 没有更多行可放，贡献为 0
            }  // 边界分支结束
            if (memo[i][pre][ic][ec] != -1) {  // 该状态算过就直接取缓存
                return memo[i][pre][ic][ec];  // 返回记忆化结果
            }  // 缓存命中分支结束
            int ans = 0;  // 本行枚举的最优值，初始为 0
            for (int cur = 0; cur < mx; ++cur) {  // 枚举当前行所有可能状态
                if (ix[cur] <= ic && ex[cur] <= ec) {  // 只有人数够用，该状态才可行
                    ans = max(ans, f[cur] + g[pre][cur] + dfs(i + 1, cur, ic - ix[cur], ec - ex[cur]));  // 取「本行幸福 + 上下行影响 + 后续最优」的最大值
                }  // 可行性判断结束
            }  // 状态枚举结束
            return memo[i][pre][ic][ec] = ans;  // 写入记忆化并返回本层答案
        };  // lambda 定义结束
        return dfs(0, 0, introvertsCount, extrovertsCount);  // 从第 0 行、上一行为空状态开始搜索
    }  // 方法结束
};  // 类定义结束