// 题目：904. 水果成篮（Fruit Into Baskets）
// 核心思路：滑动窗口保证窗口内水果种类不超过两种，用哈希表维护窗口内各类型的计数，种类超过 2 就收缩左边界。
// 时间复杂度：O(n)，每个元素最多进出窗口各一次；空间复杂度：O(1)，哈希表最多只有 3 个键。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int totalFruit(vector<int>& fruits) {  // fruits：每棵树上的水果类型；返回最多能摘的水果个数
        unordered_map<int, int> cnt;  // 哈希表：记录当前窗口内每种水果出现的次数
        int ans = 0;  // 答案：合法窗口的最大长度，即最多能摘的水果数
        for (int i = 0, j = 0; i < fruits.size(); ++i) {  // 滑动窗口：j 是左端点，i 是右端点，窗口内最多保留两种水果
            int x = fruits[i];  // 右端点新加入的水果类型
            ++cnt[x];  // 该类型计数加一，把它纳入窗口
            while (cnt.size() > 2) {  // 窗口内水果种类超过两种，需要不断收缩左边界
                int y = fruits[j++];  // 取出左端点水果类型，同时把左端点右移一位
                if (--cnt[y] == 0) {  // 该类型数量减一；减到 0 说明窗口内已没有这种水果
                    cnt.erase(y);  // 删除该键，保证 cnt.size() 恰好等于窗口内水果种类数
                }  // 结束计数清理
            }  // 结束窗口收缩
            ans = max(ans, i - j + 1);  // 当前窗口合法，用它的长度更新答案
        }  // 结束遍历
        return ans;  // 返回最多能摘的水果个数
    }  // 结束 totalFruit
};  // 结束 Solution 类