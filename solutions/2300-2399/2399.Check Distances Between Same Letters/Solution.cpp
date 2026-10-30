// 题目：2399. 检查相同字母间的距离（Check Distances Between Same Letters）
// 思路：数组记录每个字母首次出现的位置（存下标 + 1，0 表示未出现），再次出现时校验中间字符数是否等于 distance。
// 时间复杂度：O(n)，只遍历字符串一次；空间复杂度：O(1)，固定 26 个元素的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkDistances(string s, vector<int>& distance) {  // s：待检查字符串；distance：每个字母规定的间隔
        int d[26]{};  // 记录每个字母首次出现的位置 + 1，全 0 表示都未出现
        for (int i = 1; i <= s.size(); ++i) {  // 用 1 起始的下标遍历，与“位置 + 1”的存储方式对齐
            int j = s[i - 1] - 'a';  // 取当前字符对应的字母序号 0..25
            if (d[j] && i - d[j] - 1 != distance[j]) {  // 出现过，且两次下标差减 1（中间字符数）与规定距离不同
                return false;  // 距离不符，立即返回 false
            }
            d[j] = i;  // 记下出现位置；第二遍时若距离已校验通过，也会更新为最新位置
        }
        return true;  // 遍历结束没有冲突，返回 true
    }
};