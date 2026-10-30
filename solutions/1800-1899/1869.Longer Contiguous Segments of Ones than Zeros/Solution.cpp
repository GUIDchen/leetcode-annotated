// 题目：1869. 哪种连续子字符串更长（Longer Contiguous Segments of Ones than Zeros）
// 思路：写一个统计字符 x 最长连续段长度的 lambda，分别求出 '1' 与 '0' 的最长连续段长度再比较大小。
// 时间复杂度：O(n)，字符串只被扫描两遍；空间复杂度：O(1)，只用了几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkZeroOnes(string s) {  // s：只含 '0' 与 '1' 的字符串
        auto f = [&](char x) {  // 内部 lambda：返回字符 x 在 s 中的最长连续段长度
            int cnt = 0, mx = 0;  // cnt：当前连续段长度；mx：历史最长连续段长度
            for (char& c : s) {  // 遍历字符串的每个字符
                if (c == x) {  // 与目标字符相同，连续段继续延伸
                    mx = max(mx, ++cnt);  // 先自增当前段长度，再刷新历史最大值
                } else {  // 字符不同，连续段被打断
                    cnt = 0;  // 当前连续段长度清零
                }  // 结束 if/else 分支
            }  // 结束 for
            return mx;  // 返回 x 的最长连续段长度
        };  // 结束 lambda
        return f('1') > f('0');  // 比较 '1' 与 '0' 的最长连续段长度，判断 1 是否更长
    }  // 结束方法
};  // 结束类