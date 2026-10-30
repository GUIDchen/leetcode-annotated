// 题目：1525. 字符串的好分割数目（Number of Good Ways to Split a String）
// 核心思路：先用 map 统计整串字符频次（视为右半），再从左到右把字符搬进左半集合，左右不同字符数相等时计数。
// 时间复杂度：O(n)；空间复杂度：O(σ)，σ 为字符种数（≤26）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSplits(string s) {  // s：待分割字符串，返回好分割的切分点个数
        unordered_map<char, int> cnt;  // cnt：右半部分每个字符的剩余出现次数
        for (char& c : s) {  // 先把整串字符都算作右半，统计频次
            ++cnt[c];  // 逐个字符计数
        }  // 第一轮计数结束
        unordered_set<char> vis;  // vis：左半部分出现过的字符集合
        int ans = 0;  // 答案计数
        for (char& c : s) {  // 从左到右枚举分割点，把 s[i] 收进左半（分割点在 i 之后）
            vis.insert(c);  // 把当前字符加入左半集合
            if (--cnt[c] == 0) {  // 从右半计数里减一，等于 0 说明右半已无该字符
                cnt.erase(c);  // 从 map 中删掉，cnt.size() 才等于「右半不同字符数」
            }  // if 结束
            ans += vis.size() == cnt.size();  // 左右不同字符数相等就是好分割，布尔值可直接加到 ans 上（true 记 1）
        }  // 循环结束
        return ans;  // 返回好分割的数目
    }  // 方法结束
};  // 类定义结束