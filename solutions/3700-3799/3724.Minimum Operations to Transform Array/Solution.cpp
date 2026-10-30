// 3724. Minimum Operations to Transform Array（转换数组的最少操作次数）
// 核心思路：以 nums2 的末尾元素 nums2[n] 为参照，逐对把 [y, x] 的差值累加为代价；若没有任何一对区间覆盖 nums2[n]，再补上把它调到最近端点的最小距离。
// 复杂度：时间 O(n)，空间 O(1)。

class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2) {  // 返回把 nums1 前 n 个元素变成 nums2 对应元素所需的最少操作次数
        long long ans = 1;  // ans 记为 1，作为并入 nums2 末尾元素这一次操作的固定基数
        int n = nums1.size();  // 取前 n 个元素的个数（nums2[n] 是位于末尾的参照元素）
        bool ok = false;  // ok 表示是否已有一对区间覆盖了 nums2[n]
        int d = 1 << 30;  // d 记录把 nums2[n] 调到区间端点的最小距离，初值取大数
        for (int i = 0; i < n; ++i) {  // 逐个位置处理 nums1 与 nums2 的对应元素
            int x = max(nums1[i], nums2[i]);  // x 取两数的较大者，作为目标区间的右端点
            int y = min(nums1[i], nums2[i]);  // y 取两数的较小者，作为目标区间的左端点
            ans += x - y;  // 把区间 [y, x] 抹平需要 x-y 次操作，直接累加进答案
            d = min(d, min(abs(x - nums2[n]), abs(y - nums2[n])));  // 不搬动 nums2[n] 时，把它调到该区间端点所需的最小距离
            ok = ok || (nums2[n] >= y && nums2[n] <= x);  // 若 nums2[n] 已落在 [y, x] 内，说明这一对可以顺带覆盖它
        }  // 遍历结束
        if (!ok) {  // 没有任何一对覆盖 nums2[n]
            ans += d;  // 额外付出最小距离 d，把 nums2[n] 调整到最近端点
        }  // 补偿分支结束
        return ans;  // 返回最少操作次数
    }  // 函数结束
};  // 题解类结束
