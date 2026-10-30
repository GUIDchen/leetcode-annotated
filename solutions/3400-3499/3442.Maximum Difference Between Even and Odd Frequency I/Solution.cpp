// 3442. 奇偶频次间的最大差值 I / Maximum Difference Between Even and Odd Frequency I
// 核心思路：统计 26 个字母的出现次数，取最大奇数次频次 a 与最小非零偶数次频次 b，答案即 a - b。
// 复杂度：时间 O(n)，空间 O(1)（固定 26 个计数桶）。
class Solution {  // 定义题解类
public:  // 公有方法
    int maxDifference(string s) {  // 返回奇数次频次与偶数次频次的最大差值
        int cnt[26]{};  // cnt[i] 记录第 i 个字母的出现次数
        for (char c : s) {  // 遍历字符串统计频次
            ++cnt[c - 'a'];  // 对应字母计数加一
        }  // 结束统计循环
        int a = 0, b = 1 << 30;  // a 为最大奇频次，b 为最小非零偶频次
        for (int v : cnt) {  // 遍历 26 个字母的频次
            if (v % 2 == 1) {  // 频次为奇数
                a = max(a, v);  // 更新最大奇频次
            } else if (v > 0) {  // 频次为偶数且非零
                b = min(b, v);  // 更新最小偶频次
            }  // 结束分支判断
        }  // 结束频次遍历
        return a - b;  // 返回最大差值
    }  // 结束 maxDifference 方法
};  // 结束 Solution 类
