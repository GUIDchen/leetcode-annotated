// 题目：87. 扰乱字符串（Scramble String）
// 思路：记忆化搜索。f[i][j][k] 表示 s1 从 i 起、s2 从 j 起、长度均为 k 的两段是否互为扰乱串；枚举切分长度 h，分「不交换」和「交换」两种拼法递归。
// 时间复杂度：O(n^4)，状态 O(n^3) 个、每个状态枚举 O(n) 种切分；空间复杂度：O(n^3)，记忆化数组。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isScramble(string s1, string s2) {  // 判断 s2 是否由 s1 通过反复交换子串得到
        int n = s1.size();  // 字符串长度（题目保证 s1、s2 等长）
        int f[n][n][n + 1];  // 记忆化数组：第三维是长度，取值 0..n，所以开 n + 1
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示「尚未计算」；1 表示可以，0 表示不行
        function<bool(int, int, int)> dfs = [&](int i, int j, int k) -> int {  // dfs(i, j, k)：判断 s1[i..i+k) 与 s2[j..j+k) 是否互为扰乱串
            if (f[i][j][k] != -1) {  // 该状态之前算过
                return f[i][j][k] == 1;  // 直接返回缓存结果（1 为 true，0 为 false）
            }
            if (k == 1) {  // 只剩一个字符，没有可切分的位置
                return s1[i] == s2[j];  // 单字符互为扰乱串当且仅当字符相同
            }
            for (int h = 1; h < k; ++h) {  // 枚举左半段的长度 h，把两段切成 h 和 k - h
                if (dfs(i, j, h) && dfs(i + h, j + h, k - h)) {  // 第一种拼法：不交换，两半一一对应
                    return f[i][j][k] = true;  // 命中，写入缓存并立即返回
                }
                if (dfs(i + h, j, k - h) && dfs(i, j + k - h, h)) {  // 第二种拼法：交换两半，s1 的后半对 s2 的前半
                    return f[i][j][k] = true;  // 命中，写入缓存并立即返回
                }
            }
            return f[i][j][k] = false;  // 所有切分都不行，缓存 false 并返回
        };
        return dfs(0, 0, n);  // 从两串的起点、全长开始搜索
    }
};