// 题目：2551. 将珠子放入背包中（Put Marbles in Bags）
// 思路：一次划分的得分 = weights[0] + weights[n-1] + (k-1) 个相邻对的和，两端的项在最大/最小得分里相同会抵消；于是把 n-1 个相邻对和排序，用最大的 k-1 个之和减最小的 k-1 个之和。
// 时间复杂度：O(n log n)，排序相邻对之和；空间复杂度：O(n)，存放 n-1 个相邻对之和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long putMarbles(vector<int>& weights, int k) {  // weights 是珠子的重量；k 是要分成的袋子数
        int n = weights.size();  // n 是珠子个数
        vector<int> arr(n - 1);  // arr 存放每一对相邻珠子的重量和，共 n-1 个
        for (int i = 0; i < n - 1; ++i) {  // 遍历所有相邻对
            arr[i] = weights[i] + weights[i + 1];  // 第 i 个相邻对的和：weights[i] + weights[i + 1]
        }
        sort(arr.begin(), arr.end());  // 升序排序，便于同时取出最小的和最大的 k-1 个
        long long ans = 0;  // ans 累计「最大得分 - 最小得分」
        for (int i = 0; i < k - 1; ++i) {  // 每多分一个袋子就多一段边界，所以共取 k-1 个相邻和
            ans -= arr[i];  // 最小得分要加上的 k-1 个较小相邻和，先减掉
            ans += arr[n - 2 - i];  // 最大得分要加上的 k-1 个较大相邻和，再加上
        }
        return ans;  // 两端的 weights[0] 与 weights[n-1] 在两个得分里相同，抵消后只剩相邻和的差值
    }
};