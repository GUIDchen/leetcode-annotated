// 题目：1624. 两个相同字符之间的最长子字符串（Largest Substring Between Two Equal Characters）
// 思路：用长度 26 的数组记录每个字母第一次出现的下标，之后遇到同一字母就用「当前下标 - 首次下标 - 1」更新答案。
// 时间复杂度：O(n)，只扫描字符串一遍；空间复杂度：O(1)，只需常数大小的 26 长度数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxLengthBetweenEqualCharacters(string s) {  // s 是只含小写字母的输入字符串，返回最长子串长度
        vector<int> d(26, -1);  // d[i] 记录字母 i 第一次出现的下标，全部初始化为 -1
        int ans = -1;  // 答案初值 -1，恰好对应「不存在相同字符对」的情况
        for (int i = 0; i < s.size(); ++i) {  // 逐字符扫描，i 为当前下标
            int j = s[i] - 'a';  // 把字符映射到 0..25 的字母编号
            if (d[j] == -1) {  // 第一次遇到这个字母
                d[j] = i;  // 记下它最早出现的下标，供后面配对使用
            } else {  // 之前已经出现过这个字母
                ans = max(ans, i - d[j] - 1);  // 两下标之间夹着的字符个数就是子串长度，取最大值
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回统计出的最大长度（没有相同字符对时为 -1）
    }  // 方法结束
};