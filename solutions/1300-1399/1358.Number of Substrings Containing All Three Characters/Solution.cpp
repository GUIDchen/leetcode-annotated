// 题目：1358. 包含所有三种字符的子字符串数目（Number of Substrings Containing All Three Characters）
// 思路：记录 a、b、c 各自最近一次出现的位置；枚举右端点时，三种字符都出现过则以 min(三个位置)+1 个左端点都可以构成合法子串。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只需长度为 3 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSubstrings(string s) {  // 统计同时包含 a、b、c 三个字符的子串数目
        int d[3] = {-1, -1, -1};  // d[c] 表示字符 c 最近一次出现的下标，-1 表示尚未出现
        int ans = 0;  // 答案累加器
        for (int i = 0; i < s.size(); ++i) {  // 从左到右枚举子串的右端点 i
            d[s[i] - 'a'] = i;  // 更新当前字符的最近出现位置
            ans += min(d[0], min(d[1], d[2])) + 1;  // 三种字符都出现过时，左端点取 min+1 种都能保证三种字符齐备；有字符未出现时 min 为 -1，贡献正好为 0
        }  // 所有右端点枚举完毕
        return ans;  // 返回合法子串总数
    }  // numberOfSubstrings 结束
};  // 类定义结束