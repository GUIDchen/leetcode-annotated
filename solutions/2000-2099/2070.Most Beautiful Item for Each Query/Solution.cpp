// 题目：2070. 每一个查询的最大美丽值（Most Beautiful Item for Each Query）
// 思路：物品按价格排序，查询按下标按价格排序；离线从小到大回答查询，用物品指针不断纳入价格不超过查询的物品，并维护已纳入物品的最大美丽值。
// 时间复杂度：O((n + m) log(n + m))，两次排序主导；空间复杂度：O(m + n)，用于下标数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {  // items 是 (价格, 美丽值)，queries 是查询价格；返回每个查询的最大美丽值
        sort(items.begin(), items.end());  // 先按价格升序排序，价格相同时按美丽值升序
        int n = items.size();  // 物品数量
        int m = queries.size();  // 查询数量
        vector<int> idx(m);  // 保存查询下标的数组，排序后仍能写回答案的原位置
        iota(idx.begin(), idx.end(), 0);  // iota 把 idx 依次填成 0,1,2,...,m-1
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按查询价格从小到大对下标排序
            return queries[i] < queries[j];  // 比较两个下标对应的查询价格
        });
        int mx = 0, i = 0;  // mx 维护已纳入物品的最大美丽值，i 是物品指针
        vector<int> ans(m);  // 存放每个查询的答案
        for (int j : idx) {  // 按价格从低到高依次回答每个查询
            while (i < n && items[i][0] <= queries[j]) {  // 把价格不超过当前查询的物品全部纳入考虑
                mx = max(mx, items[i][1]);  // 用当前物品的美丽值刷新最大值
                ++i;  // 物品指针后移，每个物品只会被纳入一次
            }
            ans[j] = mx;  // 当前查询的答案就是已纳入物品的最大美丽值（无物品时为 0）
        }
        return ans;  // 返回按原查询顺序排列的答案数组
    }
};