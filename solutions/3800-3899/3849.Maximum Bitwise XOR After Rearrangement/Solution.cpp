// 3849. 重新排列后的最大按位异或值 / Maximum Bitwise XOR After Rearrangement（中等）
// 核心思路：统计 t 中 0 与 1 的个数，从高位到低位优先用与 s 当前位相反的字符，使每位的异或结果为 1。
// 复杂度：时间 O(|s| + |t|)，空间 O(1)。
class Solution {  // 解题类：LeetCode 判题器约定的类名
public:  // 公有接口
    string maximumXor(string s, string t) {  // 重排 t 后与 s 逐位异或，返回能得到的最大二进制串
        int cnt[2]{};  // cnt[0]、cnt[1] 分别记录 t 中 0 与 1 的剩余个数
        for (char c : t) {  // 统计 t 中两种字符的数量
            cnt[c - '0']++;  // 对应字符计数加一
        }  // 统计结束

        string ans(s.size(), '0');  // 结果串，长度与 s 相同，先全置 0
        for (int i = 0; i < s.size(); i++) {  // 从高位到低位依次为 s 的每一位挑选 t 中的字符
            int x = s[i] - '0';  // s 当前位的比特值
            if (cnt[x ^ 1] > 0) {  // 若还存在与 x 相反的字符，异或可得 1
                cnt[x ^ 1]--;  // 消耗一个相反字符
                ans[i] = '1';  // 该位结果为 1
            } else {  // 否则只能用相同字符，异或结果为 0
                cnt[x]--;  // 消耗一个相同字符
            }  // 分支选择结束
        }  // 逐位处理结束

        return ans;  // 返回构造出的最大异或结果串
    }  // maximumXor 方法结束
};  // 解题类定义结束
