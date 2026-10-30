// 题目：2107. 分享 K 个糖果后独特口味的数量（Number of Unique Flavors After Sharing K Candies）
// 思路：分出去的是长度恰为 k 的连续一段，剩下 n-k 个糖果构成滑动窗口；用哈希表维护窗口内各口味个数，独特口味数即哈希表大小，取最大值。
// 时间复杂度：O(n)，每个元素进出窗口各一次；空间复杂度：O(n)，哈希表最多存 n 种口味。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shareCandies(vector<int>& candies, int k) {  // candies：糖果口味数组；k：要分享出去的连续糖果个数
        unordered_map<int, int> cnt;  // cnt 记录「口味 → 在剩余窗口中的出现次数」
        int n = candies.size();  // n 是糖果总数
        for (int i = k; i < n; ++i) {  // 先把下标 k 到 n-1 这一段作为初始剩余窗口
            ++cnt[candies[i]];  // 统计窗口内每种口味的出现次数
        }  // 初始窗口统计结束
        int ans = cnt.size();  // 初始窗口里独特口味的数量就是哈希表大小
        for (int i = k; i < n; ++i) {  // 滑动窗口整体右移一位，共移动（n-k）次
            ++cnt[candies[i - k]];  // 左端刚滑出的那颗糖果重新回到剩余窗口
            if (--cnt[candies[i]] == 0) {  // 右端即将移出的糖果计数减一，减到 0 说明该口味已不在窗口里
                cnt.erase(candies[i]);  // 从哈希表中删除计数为 0 的口味，保证 size() 就是种类数
            }  // 删除分支结束
            ans = max(ans, (int) cnt.size());  // 用当前窗口的独特口味数更新答案
        }  // 滑动结束
        return ans;  // 返回能获得的最多独特口味数
    }  // 方法结束
};  // 题解类结束