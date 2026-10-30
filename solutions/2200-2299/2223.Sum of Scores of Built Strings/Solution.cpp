// 题目：2223. 构造字符串的总得分和（Sum of Scores of Built Strings）
// 思路：Z 函数（扩展 KMP）求出每个后缀 s[i:] 与 s 的最长公共前缀长度 z[i]，得分和即 n + Σz[i]。
// 时间复杂度：O(n)，匹配指针不回退、扩展总量线性；空间复杂度：O(n)，z 数组存 n 个长度值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long sumScores(string s) {  // s：待求得分和的字符串，返回所有后缀与 s 的最长公共前缀长度之和
        int n = s.size();  // 字符串长度
        vector<int> z(n);  // z[i] 表示 s[i:] 与 s 的最长公共前缀长度（Z 函数）
        for (int i = 1, l = 0, r = 0; i < n; ++i) {  // 从下标 1 开始扫描；[l, r] 是当前已匹配出的最右区间
            if (i <= r) {  // i 落在已知匹配区间内，可以复用之前算出的结果
                z[i] = min(r - i + 1, z[i - l]);  // 取「区间剩余长度」与「镜像位置 z[i-l]」中的较小者
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {  // 在初值基础上继续向后扩展，直到失配或越界
                ++z[i];  // 每匹配上一个字符，公共前缀长度加一
            }
            if (i + z[i] - 1 > r) {  // 本次匹配的右端点超过了已有区间，需要刷新区间
                l = i;  // 新区间左端点就是当前位置
                r = i + z[i] - 1;  // 新区间右端点即匹配到的最远位置
            }
        }
        return n + accumulate(z.begin(), z.end(), 0LL);  // 原串自身得分 n，加上所有后缀的 z 值之和
    }
};
