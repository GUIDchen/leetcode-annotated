// 题目：514. 自由之路（Freedom Trail）
// 思路：动态规划。先按字符记下环上所有出现位置，f[i][j] 表示拼完 key[0..i] 且指针停在 j 的最小代价，转移时枚举上一个字符的位置并取环上最短旋转距离。
// 时间复杂度：O(m·n²)，每个字符对每种落点组合转移一次；空间复杂度：O(m·n)，即 DP 表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findRotateSteps(string ring, string key) {  // ring 是圆环上的字符，key 是待拼出的关键字
        int m = key.size(), n = ring.size();  // m 是关键字长度（阶段数），n 是环上的字符数
        vector<int> pos[26];  // 记录每个字母在环上出现的所有下标，转移时可跳过无关位置
        for (int j = 0; j < n; ++j) {  // 一次遍历，把环上每个位置按字符归类
            pos[ring[j] - 'a'].push_back(j);  // 字符 ring[j] 的位置表里追加下标 j
        }  // 位置表建好
        int f[m][n];  // f[i][j]：拼完 key 前 i+1 个字符、指针停在环上位置 j 的最小代价
        memset(f, 0x3f, sizeof(f));  // 初始化为很大的数（0x3f3f3f3f），表示暂时不可达
        for (int j : pos[key[0] - 'a']) {  // 第一个字符可以停在它出现的任意位置
            f[0][j] = min(j, n - j) + 1;  // 从 0 号位转到 j 取顺/逆时针较小值，+1 表示按下按钮
        }  // 第一阶段初始化完成
        for (int i = 1; i < m; ++i) {  // 按顺序递推后面的每个字符
            for (int j : pos[key[i] - 'a']) {  // 枚举当前字符 key[i] 可能的落点 j
                for (int k : pos[key[i - 1] - 'a']) {  // 枚举上一个字符 key[i-1] 停留过的位置 k
                    f[i][j] = min(f[i][j], f[i - 1][k] + min(abs(j - k), n - abs(j - k)) + 1);  // 转移：上一阶段代价 + 环上最短旋转距离 + 按一次按钮
                }  // 枚举完 k
            }  // 枚举完 j
        }  // 所有阶段递推结束
        int ans = 1 << 30;  // 答案取最小值，先设一个足够大的初值
        for (int j : pos[key[m - 1] - 'a']) {  // 最后一个字符的所有可能落点都要看
            ans = min(ans, f[m - 1][j]);  // 取其中代价最小的
        }  // 枚举结束
        return ans;  // 返回最小总代价
    }  // 方法结束
};  // 类定义结束