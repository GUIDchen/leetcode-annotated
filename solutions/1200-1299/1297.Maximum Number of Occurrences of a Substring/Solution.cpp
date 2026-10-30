// 题目：1297. 子串的最大出现次数（Maximum Number of Occurrences of a Substring）
// 思路：只需枚举长度 minSize 的窗口——更长的合格子串，其长度 minSize 的前缀出现次数不会更少。
// 时间复杂度：O(n * minSize)，每个窗口切子串并建集合；空间复杂度：O(n * minSize)，哈希表存放子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {  // s：原串；maxLetters：不同字母上限；minSize/maxSize：子串长度下限/上限
        int ans = 0;  // 记录出现次数的最大值
        unordered_map<string, int> cnt;  // 统计每个满足条件的子串出现次数
        for (int i = 0; i < s.size() - minSize + 1; ++i) {  // 枚举所有长度 minSize 的窗口起点
            string t = s.substr(i, minSize);  // 取出当前长度为 minSize 的子串
            unordered_set<char> ss(t.begin(), t.end());  // 用集合统计该子串包含多少种不同字母
            if (ss.size() <= maxLetters) {  // 不同字母数不超过上限，才有资格计入答案
                ans = max(ans, ++cnt[t]);  // 该子串计数加一，并更新最大值
            }
        }
        return ans;  // 返回最大出现次数（maxSize 用不到，因为最短的合法子串出现次数最多）
    }
};