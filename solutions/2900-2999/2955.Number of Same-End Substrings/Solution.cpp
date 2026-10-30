// 题目：2955. 同端子串的数量（Number of Same-End Substrings）
// 思路：对 26 个字母各建一个前缀计数数组；回答询问时取区间内每个字母的出现次数 x，贡献 x 个单字符子串加上任选两个端点的 C(x,2)。
// 时间复杂度：O((n + q) * 26)，预处理与每次询问都只扫 26 个字母；空间复杂度：O(26n)，前缀计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sameEndSubstringCount(string s, vector<vector<int>>& queries) {  // s：只含小写字母的字符串；queries：若干 [l, r] 询问；返回每个询问的答案
        int n = s.size();  // 字符串长度
        int cnt[26][n + 1];  // 二维前缀计数：cnt[c][j] 表示前 j 个字符中字母 c 出现的次数
        memset(cnt, 0, sizeof(cnt));  // 前缀表全部清零
        for (int j = 1; j <= n; ++j) {  // 逐列递推前缀计数
            for (int i = 0; i < 26; ++i) {  // 对 26 个字母分别继承
                cnt[i][j] = cnt[i][j - 1];  // 先复制上一列的前缀和
            }  // 字母维度循环结束
            cnt[s[j - 1] - 'a'][j]++;  // 当前字符对应的字母在这一列多算一次
        }  // 前缀表构建完成
        vector<int> ans;  // 存放每个询问的答案
        for (auto& q : queries) {  // 逐个处理询问
            int l = q[0], r = q[1];  // 取出询问区间 [l, r]（闭区间）
            ans.push_back(r - l + 1);  // 长度为 1 的子串首尾字母必然相同，先各计 1 个
            for (int i = 0; i < 26; ++i) {  // 对每个字母分别统计区间内的出现次数
                int x = cnt[i][r + 1] - cnt[i][l];  // 前缀和相减得到区间内字母 i 的出现次数
                ans.back() += x * (x - 1) / 2;  // 从 x 个位置中任选两个当首尾，共 C(x, 2) 个更长的合法子串
            }  // 字母维度循环结束
        }  // 询问循环结束
        return ans;  // 返回全部询问的答案
    }  // 方法结束
};  // 类定义结束