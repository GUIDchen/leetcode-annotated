// 题目：1177. 构建回文串检测（Can Make Palindrome from Substring）
// 思路：前缀计数表记录每个前缀里 26 个字母的出现次数；对查询区间统计出现奇数次的字母数 x，
//       把其中 x/2 个字符改掉即可让至多一个字母保持奇数，于是只需判断 x/2 <= k。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {  // s 为原字符串，queries 每项是 [l, r, k] 的查询
        int n = s.size();  // 字符串长度
        int ss[n + 1][26];  // ss[i][c] 表示前缀 s[0..i-1] 中字母 c 的出现次数
        memset(ss, 0, sizeof(ss));  // 清零初始化，避免读到栈上的脏数据
        for (int i = 1; i <= n; ++i) {  // 前缀长度从 1 推到 n，逐层构造计数表
            for (int j = 0; j < 26; ++j) {  // 先把上一个前缀的 26 个计数整体继承下来
                ss[i][j] = ss[i - 1][j];  // 复制上一行的计数，形成当前前缀的基数
            }  // 26 个字母继承完毕
            ss[i][s[i - 1] - 'a']++;  // 把第 i 个字符（下标 i-1）计入对应字母，得到 ss[i]
        }  // 当前前缀构造完成
        vector<bool> ans;  // 按查询顺序保存布尔结果
        for (auto& q : queries) {  // 逐个查询处理
            int l = q[0], r = q[1], k = q[2];  // l/r 为闭区间端点，k 为最多可替换的字符数
            int x = 0;  // x 统计区间内出现奇数次的字母种数
            for (int j = 0; j < 26; ++j) {  // 枚举 26 个字母
                x += (ss[r + 1][j] - ss[l][j]) & 1;  // 区间计数为奇数则 +1：&1 取最低位判断奇偶
            }  // 26 个字母统计完毕
            ans.emplace_back(x / 2 <= k);  // 奇数种数 x 最多留下 1 个不被配对，需改 x/2 个字符，判断 k 是否够用
        }  // 当前查询处理完毕
        return ans;  // 返回全部查询的答案
    }  // 方法体结束
};  // 题解类结束