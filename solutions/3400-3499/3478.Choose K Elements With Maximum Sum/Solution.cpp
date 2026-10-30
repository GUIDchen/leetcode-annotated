// 3478. 选出和最大的 K 个元素（Choose K Elements With Maximum Sum）
// 核心思路：把 (nums1[i], i) 排序后滑动指针 j，把 nums1 值严格小于当前值的元素对应的 nums2 值维护进大小不超过 k 的小根堆，堆内和即答案，nums1 相等的元素共享同一批候选。
// 复杂度：时间 O(n log n)，空间 O(n)
class Solution {  // 解题类
public:  // 公有成员
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {  // 返回每个下标对应的、至多 k 个元素的最大和
        int n = nums1.size();  // 元素个数
        vector<pair<int, int>> arr(n);  // 存放 (nums1 的值, 原始下标) 并用于排序
        for (int i = 0; i < n; ++i) {  // 把每个元素与其下标打包
            arr[i] = {nums1[i], i};  // 记录第 i 个元素的值和下标
        }  // 结束打包循环
        ranges::sort(arr);  // 按 nums1 的值升序排序
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆，用来保留当前最大的至多 k 个 nums2 值
        long long s = 0;  // 堆内元素之和
        int j = 0;  // 已经加入堆的左指针 j
        vector<long long> ans(n);  // 存放每个下标的答案
        for (int h = 0; h < n; ++h) {  // 从最小的 nums1 值开始向后推进
            auto [x, i] = arr[h];  // 取出当前元素的值 x 与原始下标 i
            while (j < h && arr[j].first < x) {  // 把所有 nums1 值严格小于 x 的元素补进候选集合
                int y = nums2[arr[j].second];  // 取该候选元素对应的 nums2 值
                pq.push(y);  // 压入小根堆
                s += y;  // 同步累加堆内和
                if (pq.size() > k) {  // 堆内元素超过 k 个时
                    s -= pq.top();  // 先减去堆顶的最小值
                    pq.pop();  // 再弹出堆顶，保持堆大小不超过 k
                }  // 结束堆大小调整
                ++j;  // 左指针右移，该元素之后不会再被计入
            }  // 结束候选集合扩充
            ans[i] = s;  // 当前堆内和就是下标 i 的答案
        }  // 结束遍历
        return ans;  // 返回答案数组
    }  // 结束方法
};  // 结束类定义
