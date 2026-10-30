// 题目：373. 查找和最小的 K 对数字（Find K Pairs with Smallest Sums）
// 思路：每个 nums1[i] 对应一条递增的候选链 (i,0),(i,1),…，把各链队首放进小顶堆，每次弹出最小和后把同链的下一个入堆，重复 k 次。
// 时间复杂度：O((k + m) log m)，堆操作；空间复杂度：O(k + m)，堆与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {  // nums1、nums2 为升序数组，返回和最小的 k 对下标组合对应的值对
        auto cmp = [&nums1, &nums2](const pair<int, int>& a, const pair<int, int>& b) {  // 自定义比较器：用「和更大」实现小顶堆（priority_queue 默认是大顶堆）
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];  // 比较两个下标对的和，注意这里 a、b 是元素对的下标
        };  // 比较器 lambda 结束

        int m = nums1.size();  // nums1 的长度，决定初始入堆的链数
        int n = nums2.size();  // nums2 的长度，用于判断某条链是否还有后继
        vector<vector<int>> ans;  // 保存最终结果
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);  // 小顶堆：按 cmp 的「相反」优先级排序，堆顶是当前和最小的一对下标
        for (int i = 0; i < min(k, m); i++)  // 每条链只需前 min(k, m) 条，其它链的第 0 个元素必然进不了前 k
            pq.emplace(i, 0);  // 把每条链的队首 (i, 0) 入堆
        while (k-- && !pq.empty()) {  // 最多取 k 对，同时堆非空才可继续
            auto [x, y] = pq.top();  // 取出堆顶（当前和最小的下标对）
            pq.pop();  // 弹掉已使用的堆顶
            ans.emplace_back(initializer_list<int>{nums1[x], nums2[y]});  // 按这两个下标取真实值组成答案对（initializer_list 直接构造 vector）
            if (y + 1 < n)  // 该链还有下一个候选才继续入堆
                pq.emplace(x, y + 1);  // 同一条链的下一个下标 j+1 入堆，保证链内递增
        }  // 主循环闭合

        return ans;  // 返回和最小的至多 k 对数字
    }  // 方法结束
};  // 类定义结束