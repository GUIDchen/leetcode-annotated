// 题目：1704. 判断字符串的两半是否相似（Determine if String Halves Are Alike）
// 思路：把字符串均分成前后两半，同步遍历，前半遇到元音就 +1、后半遇到元音就 -1，最终计数为 0 说明两半元音数相等。
// 时间复杂度：O(n)，只扫描半串长度；空间复杂度：O(1)，元音集合大小固定为 10。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool halvesAreAlike(string s) {  // s 是偶数长度的字符串
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};  // 大小写各五个元音，放进哈希集合便于 O(1) 查询
        int cnt = 0, n = s.size() / 2;  // cnt 记录两半元音数之差；n 是半串长度，题目保证长度是偶数
        for (int i = 0; i < n; ++i) {  // 同时遍历前半的第 i 个与后半的第 i 个字符
            cnt += vowels.count(s[i]);  // 前半出现元音就加一（count 返回 0 或 1）
            cnt -= vowels.count(s[i + n]);  // 后半出现元音就减一，与前半的贡献相互抵消
        }
        return cnt == 0;  // 差值归零说明两半的元音个数相同
    }
};