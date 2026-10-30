// 题目：2024. 考试的最大困扰度（Maximize the Confusion of an Exam）
// 思路：分别以 'T' 和 'F' 为目标字符，用滑动窗口求「窗口内该字符个数不超过 k」的最长区间；把窗口里这些字符全部改写即可得到同字符连续段，两种目标取较大值。
// 时间复杂度：O(n)，字符串被扫描两遍；空间复杂度：O(1)，只用了几个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxConsecutiveAnswers(string answerKey, int k) {  // answerKey：只有 'T'/'F' 的答题串；k：最多可改写的字符数；返回最长连续相同答案的长度
        int n = answerKey.size();  // 记下串长，最后用「串长 - 左边界」直接得到窗口长度
        auto f = [&](char c) {  // 闭包 f：求「窗口内字符 c 的个数不超过 k」的最长窗口长度
            int l = 0, cnt = 0;  // l 是滑动窗口左边界；cnt 是当前窗口内等于 c 的字符个数
            for (char& ch : answerKey) {  // 右边界 ch 从左到右扫过整个字符串
                cnt += ch == c;  // 新字符进入窗口：它等于 c 时计数加 1（布尔值参与加法）
                if (cnt > k) {  // 窗口内 c 的个数超过可改写次数，必须从左侧收缩
                    cnt -= answerKey[l++] == c;  // 左端出窗：只有出窗的字符正好是 c 才把计数减 1，同时左边界右移一位
                }  // 收缩完成
            }  // 扫描结束，l 停在最优窗口的左端
            return n - l;  // 最优窗口长度 = 总长 - 左边界
        };  // 闭包定义结束
        return max(f('T'), f('F'));  // 把两段分别改成全 'T'、全 'F'，取最优的那一种
    }  // 方法结束
};  // 类定义结束