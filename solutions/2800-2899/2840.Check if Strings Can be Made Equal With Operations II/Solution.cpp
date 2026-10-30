// 题目：2840. 判断通过操作能否让字符串相等 II（Check if Strings Can be Made Equal With Operations II）
// 思路：操作可以在同奇偶下标之间任意交换字符且能多次进行，因此只需检查偶数下标、奇数下标上的字母多重集是否分别相同。
// 时间复杂度：O(n)，一次遍历加一次 26 个字母的检查；空间复杂度：O(1)，计数数组固定为 2 * 26。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkStrings(string s1, string s2) {  // 判断能否通过若干次操作把 s1 变成 s2
        vector<vector<int>> cnt(2, vector<int>(26, 0));  // cnt[p][c]：下标奇偶性 p 上字母 c 的计数差
        for (int i = 0; i < s1.size(); ++i) {  // 逐位遍历两个字符串
            ++cnt[i & 1][s1[i] - 'a'];  // s1 在该位置上的字母计数加 1
            --cnt[i & 1][s2[i] - 'a'];  // s2 在该位置上的字母计数减 1
        }
        for (int i = 0; i < 26; ++i) {  // 检查 26 个字母的计数差是否都被抵消
            if (cnt[0][i] || cnt[1][i]) {  // 任一奇偶位置上仍有剩余，说明字母多重集不同
                return false;  // 无法通过交换变得相同
            }
        }
        return true;  // 两个奇偶位置的字母多重集都相同，可以变得相等
    }
};