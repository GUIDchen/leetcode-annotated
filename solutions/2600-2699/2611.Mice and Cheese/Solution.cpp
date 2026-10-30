// 题目：2611. 老鼠和奶酪（Mice and Cheese）
// 思路：按 reward1[i] - reward2[i] 从大到小挑 k 块给第一只老鼠，其余给第二只，总收益最大。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(n)，保存下标数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {  // reward1/reward2 是两只老鼠各块奶酪的收益，k 是第一只老鼠吃的块数
        int n = reward1.size();  // n：奶酪块数
        vector<int> idx(n);  // idx：下标数组，按「第一只老鼠多出的收益」排序
        iota(idx.begin(), idx.end(), 0);  // 填入 0,1,...,n-1
        sort(idx.begin(), idx.end(), [&](int i, int j) { return reward1[j] - reward2[j] < reward1[i] - reward2[i]; });  // 按 reward1-reward2 从大到小排序：差距越大越该给第一只老鼠
        int ans = 0;  // ans：最大总收益
        for (int i = 0; i < k; ++i) {  // 前 k 块给第一只老鼠
            ans += reward1[idx[i]];  // 累加第一只老鼠的收益
        }  // 第一只老鼠处理完毕
        for (int i = k; i < n; ++i) {  // 剩下的都归第二只老鼠
            ans += reward2[idx[i]];  // 累加第二只老鼠的收益
        }  // 第二只老鼠处理完毕
        return ans;  // 返回最大总收益
    }  // 方法结束
};  // 类定义结束