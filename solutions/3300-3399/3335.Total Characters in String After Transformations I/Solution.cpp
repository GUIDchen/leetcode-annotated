// 题目：3335. 字符串转换后的长度 I（Total Characters in String After Transformations I）
// 思路：用 f[i][j] 表示经过 i 轮变换后字母 j 的个数；每轮中 'z' 分裂成 "ab"，其余字母平移到下一个字母，逐轮递推后把 26 个字母的数量求和。
// 时间复杂度：O(26·t + |s|)；空间复杂度：O(26·t)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthAfterTransformations(string s, int t) {  // s 是初始字符串，t 是变换轮数；返回变换后的字符总数
        const int mod = 1e9 + 7;  // 取模常量
        vector<vector<int>> f(t + 1, vector<int>(26, 0));  // f[i][j]：经过 i 轮变换后字母 j（0 表示 a）的个数

        for (char c : s) {  // 统计初始串中每个字母的出现次数
            f[0][c - 'a']++;  // 第 0 轮的计数
        }  // 初始统计结束

        for (int i = 1; i <= t; ++i) {  // 逐轮推进变换
            f[i][0] = f[i - 1][25] % mod;  // 只有 'z'(25) 会变成 "ab"，所以 a 的数量等于上一轮 z 的数量
            f[i][1] = (f[i - 1][0] + f[i - 1][25]) % mod;  // b 的数量等于上一轮 a 与 z 的数量之和
            for (int j = 2; j < 26; ++j) {  // 其余字母由它的前一个字母平移而来
                f[i][j] = f[i - 1][j - 1] % mod;  // 字母 j 的数量继承自上一轮的 j-1
            }  // 内部循环结束
        }  // 本轮结束

        int ans = 0;  // 累加最终 26 个字母的总数
        for (int j = 0; j < 26; ++j) {  // 枚举字母
            ans = (ans + f[t][j]) % mod;  // 累加并取模
        }  // 累加结束

        return ans;  // 返回变换后的字符总数
    }  // 方法结束
};  // 类定义结束