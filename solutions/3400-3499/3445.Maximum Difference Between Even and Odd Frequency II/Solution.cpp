// 题目：3445. 奇偶频次间的最大差值 II（Maximum Difference Between Even and Odd Frequency II）
// 思路：枚举「出现奇数次」的字符 a 和「出现偶数次」的字符 b（题目只有 0~4 五个字符），问题就变成找一段长度至少 k 的区间，让 (a 的次数 - b 的次数) 最大且 a 为奇数、b 为偶数。用前缀计数 (preA, preB) 表示窗口左边界之前的状态，按 (preA 奇偶, preB 奇偶) 分成四类，各自只保留最小的 preA - preB；右指针每扩展一步，就查一次 (curA 奇偶取反, curB 偶) 那一类，O(1) 更新答案。
// 时间复杂度：O(25n)，外层 25 种字符组合、每种左右指针各扫一遍；空间复杂度：O(1)，只有 2×2 的辅助表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDifference(string s, int k) {  // s：只含 0~4 的数字串；k：所选子串的最小长度；返回最大差值
        const int n = s.size();  // n 是串长，循环里反复用到
        const int inf = INT_MAX / 2;  // 用半个 INT_MAX 当无穷大，避免后续做减法溢出
        int ans = -inf;  // 答案初值取负无穷，表示还没找到合法方案

        for (int a = 0; a < 5; ++a) {  // a 是要求出现奇数次的字符
            for (int b = 0; b < 5; ++b) {  // b 是要求出现偶数次（且至少 2 次）的字符
                if (a == b) {  // 两个角色必须是不同的字符
                    continue;  // 跳过这种非法组合
                }

                int curA = 0, curB = 0;  // curA/curB：前缀 [0, r] 中 a、b 的出现次数
                int preA = 0, preB = 0;  // preA/preB：窗口左边界之前（下标 <= l）的 a、b 出现次数
                int t[2][2] = {{inf, inf}, {inf, inf}};  // t[pa][pb]：奇偶性为 (pa, pb) 的历史前缀中最小的 preA - preB
                int l = -1;  // l 是窗口左边界的前一位（窗口为 (l, r]），初始时窗口为空

                for (int r = 0; r < n; ++r) {  // 右端点 r 向右扩展，枚举所有子串右端
                    curA += (s[r] == '0' + a);  // 把 s[r] 计入 a 的前缀计数（比较结果为 0/1）
                    curB += (s[r] == '0' + b);  // 把 s[r] 计入 b 的前缀计数
                    while (r - l >= k && curB - preB >= 2) {  // 窗口长度已达 k，且 b 在窗口内至少出现 2 次，可以收缩左边界
                        t[preA & 1][preB & 1] = min(t[preA & 1][preB & 1], preA - preB);  // 用当前左边界之前的前缀状态更新对应奇偶类的最小值
                        ++l;  // 左边界右移一格，窗口变小
                        preA += (s[l] == '0' + a);  // 被移出窗口的字符若等于 a，就把它加进 preA
                        preB += (s[l] == '0' + b);  // 同理更新 b 的前缀计数
                    }  // 收缩结束，此时窗口 (l, r] 满足长度要求
                    ans = max(ans, curA - curB - t[(curA & 1) ^ 1][curB & 1]);  // a 要奇数、b 要偶数，历史前缀奇偶须与当前相反；整体减去最小历史前缀即为答案
                }  // 右端点枚举结束
            }  // b 枚举结束
        }  // a 枚举结束

        return ans;  // 返回最大差值
    }  // 方法结束
};  // 类定义结束
