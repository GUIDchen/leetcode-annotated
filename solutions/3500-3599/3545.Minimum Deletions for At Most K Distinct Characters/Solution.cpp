// 题目：3545. 不同字符数量最多为 K 时的最少删除数（Minimum Deletions for At Most K Distinct Characters）
// 思路：统计每个字母的出现次数并升序排序，保留出现次数最多的 K 种字母，其余字母的字符必须全部删除。
// 时间复杂度：O(n + 26 log 26)，n 为字符串长度；空间复杂度：O(26)，即 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDeletion(string s, int k) {  // s：输入字符串；k：允许保留的不同字符数量上限
        vector<int> cnt(26);  // 计数数组：cnt[i] 表示字母 'a' + i 的出现次数
        for (char c : s) {  // 遍历字符串中的每个字符
            ++cnt[c - 'a'];  // 把字符映射到 0~25 的下标并累加
        }
        ranges::sort(cnt);  // 升序排序，出现次数少的字母排在前面，便于优先删除
        int ans = 0;  // 需要删除的字符总数
        for (int i = 0; i + k < 26; ++i) {  // 前 26 - k 个较小的计数对应的字母都要被删掉
            ans += cnt[i];  // 累加这些字母的全部出现次数
        }
        return ans;  // 返回最少删除字符数
    }
};