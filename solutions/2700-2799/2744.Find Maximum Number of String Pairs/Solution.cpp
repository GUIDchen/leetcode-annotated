// 题目：2744. 最大字符串配对数目（Find Maximum Number of String Pairs）
// 核心思路：把两个字母编码成一个整数（前一个字母左移 5 位再或上后一个字母），哈希表统计出现次数，遍历时查反向编码。
// 时间复杂度：O(n)，每个字符串只做常数次操作；空间复杂度：O(n)，哈希表至多保存 n 种编码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumNumberOfStringPairs(vector<string>& words) {  // words：长度均为 2 的互不相同的字符串数组
        unordered_map<int, int> cnt;  // 哈希表：键是字符串的正向编码，值是这种字符串出现的次数
        int ans = 0;  // 累计能形成的配对数
        for (auto& w : words) {  // 逐个处理每个字符串
            int a = w[0] - 'a', b = w[1] - 'a';  // a、b 分别是两个字母映射到 0~25 后的下标
            ans += cnt[b << 5 | a];  // 先查它的反转编码出现过几次：出现过就能两两配对，直接累加
            cnt[a << 5 | b]++;  // 再把自身的正向编码计数加一，供后面的字符串查询
        }
        return ans;  // 返回最多能配对的对数
    }
};