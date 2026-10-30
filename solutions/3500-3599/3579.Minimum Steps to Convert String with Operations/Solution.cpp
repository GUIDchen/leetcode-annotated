// 题目：3579. 字符串转换需要的最小操作数 / Minimum Steps to Convert String with Operations（困难）
// 核心思路：先把 word1 切分成若干连续段，每段内部独立计算代价；calc(l, r, rev) 统计该段在不反转/反转对齐下所需的最少操作——位置上的字符对 (a, b) 若能找到反向的 (b, a)，说明两个位置可以用一次交换同时修好，否则每个错位需要一次替换，反转本身再额外花一次操作。再用区间 DP 求前缀最优：f[i] = min(f[j] + min(calc(j, i-1, false), 1 + calc(j, i-1, true)))。
// 复杂度：时间复杂度 O(n^3 + 26^2 * n^3) 量级（等价 O(n^3)），空间复杂度 O(n)。
class Solution {  // 定义题解类
public:  // 公有成员函数
    int minOperations(string word1, string word2) {  // 返回把 word1 转换成 word2 的最小操作数
        int n = word1.length();  // 字符串长度
        vector<int> f(n + 1, INT_MAX);  // f[i] 表示前 i 个字符转换完成的最小操作数
        f[0] = 0;  // 空前缀不需要任何操作

        for (int i = 1; i <= n; ++i) {  // 枚举前缀长度 i
            for (int j = 0; j < i; ++j) {  // 枚举最后一段的起点 j（0 基准）
                int a = calc(word1, word2, j, i - 1, false);  // 最后一段不反转时的代价
                int b = 1 + calc(word1, word2, j, i - 1, true);  // 最后一段先反转一次（代价加一）再匹配的代价
                int t = min(a, b);  // 该段的最小代价
                f[i] = min(f[i], f[j] + t);  // 用当前切分方式更新最优值
            }
        }

        return f[n];  // 转换整个字符串的最小操作数
    }

private:  // 私有辅助函数
    int calc(const string& word1, const string& word2, int l, int r, bool rev) {  // 计算区间 [l, r] 在该对齐方式下的最少操作数
        int cnt[26][26] = {0};  // cnt[a][b] 记录等待配对的反向字符对 (a, b) 的数量
        int res = 0;  // 累计操作数

        for (int i = l; i <= r; ++i) {  // 逐位扫描区间
            int j = rev ? r - (i - l) : i;  // 反转时取镜像下标，否则取同一下标
            int a = word1[j] - 'a';  // 源字符
            int b = word2[i] - 'a';  // 目标字符

            if (a != b) {  // 该位置字符不一致
                if (cnt[b][a] > 0) {  // 之前存在一个 (b, a) 的错位，可以与当前位置交换一次同时修好
                    cnt[b][a]--;  // 消耗掉这个待配对记录，不增加操作数
                } else {  // 没有可配对的反向错位
                    cnt[a][b]++;  // 记录本错位，等待后续匹配
                    res++;  // 否则只能替换，操作数加一
                }
            }
        }

        return res;  // 返回该段的最少操作数
    }
};
