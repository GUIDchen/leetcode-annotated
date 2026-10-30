// 3773. 最大等长连续字符组 / Maximum Number of Equal Length Runs
// 核心思路：一次遍历把字符串切成若干段连续相同字符，用哈希表统计每种段长度出现的次数，答案即所有长度中出现次数的最大值。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为字符串长度。
class Solution {  // 定义题解类
public:  // 公有成员
    int maxSameLengthRuns(string s) {  // 返回出现次数最多的“等长连续字符组”的组数
        unordered_map<int, int> cnt;  // 记录每种段长度分别出现过多少次
        int ans = 0;  // 答案：同一长度的最多段数
        int n = s.size();  // 字符串长度
        for (int i = 0; i < n;) {  // 逐个扫描每一段连续相同字符
            int j = i + 1;  // 从当前字符的下一位开始向右扩展
            while (j < n && s[j] == s[i]) {  // 找到本段连续相同字符的右边界
                ++j;  // 右指针继续后移，直到字符不同或越界
            }  // 本段扫描结束
            int m = j - i;  // 本段的长度
            ans = max(ans, ++cnt[m]);  // 该长度的出现次数加一，并更新答案
            i = j;  // 跳到下一段的起点
        }  // 整串扫描结束
        return ans;  // 返回最大段数
    }  // 方法结束
};  // 类定义结束
