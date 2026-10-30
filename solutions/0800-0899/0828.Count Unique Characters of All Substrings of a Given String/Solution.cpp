// 题目：828. 统计子串中的唯一字符（Count Unique Characters of All Substrings of a Given String）
// 思路：按字符统计贡献。字符 c 出现在 v[i]，它以“唯一一次出现”身份被计入的子串数是 (v[i]-v[i-1]) × (v[i+1]-v[i])，左右各补哨兵后逐位置累加。
// 时间复杂度：O(n)，每个位置只被扫一次；空间复杂度：O(n)，26 个位置表合计存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int uniqueLetterString(string s) {  // s：只含大写字母的字符串，返回所有子串的唯一字符数之和
        vector<vector<int>> d(26, {-1});  // d[c] 保存字符 c 出现的所有下标，先放哨兵 -1 表示“左边界之外”
        for (int i = 0; i < s.size(); ++i) {  // 遍历字符串的每个位置
            d[s[i] - 'A'].push_back(i);  // 把下标 i 记到对应字母的位置表里（s[i]-'A' 把字母映射到 0..25）
        }  // 结束位置记录
        int ans = 0;  // 答案累加器
        for (auto& v : d) {  // 逐个字符计算它的总贡献；用引用是因为下面要就地追加右哨兵
            v.push_back(s.size());  // 补右哨兵 n，表示“右边界之外”
            for (int i = 1; i < v.size() - 1; ++i) {  // 跳过左右哨兵，枚举该字符的每个真实出现位置
                ans += (v[i] - v[i - 1]) * (v[i + 1] - v[i]);  // 以 v[i] 为唯一一次出现的子串数 = 左端点可选数 × 右端点可选数
            }  // 结束位置枚举
        }  // 结束字符循环
        return ans;  // 返回所有子串的唯一字符数之和
    }  // 结束方法
};  // 结束类