// 3682. Minimum Index Sum of Common Elements（3682. 公共元素的最小索引和）
// 核心思路：先用哈希表记录 nums2 中每个元素首次出现的下标，再遍历 nums1 找公共元素，取下标和的最小值。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    int minimumSum(vector<int>& nums1, vector<int>& nums2) {  // 返回公共元素的最小下标和，无公共元素时返回 -1
        int n = nums1.size();  // 两个数组等长，统一用 n 表示
        const int inf = INT_MAX;  // 用 INT_MAX 作为“无穷大”哨兵
        unordered_map<int, int> d;  // d[x] 记录 x 在 nums2 中首次出现的下标
        for (int i = 0; i < n; i++) {  // 遍历 nums2 建立下标表
            if (!d.contains(nums2[i])) {  // 只保留首次出现的下标，保证下标和最小
                d[nums2[i]] = i;  // 记录该元素的下标
            }
        }
        int ans = inf;  // 初始化为无穷大，表示尚未找到公共元素
        for (int i = 0; i < n; i++) {  // 遍历 nums1 寻找公共元素
            if (d.contains(nums1[i])) {  // 该元素在 nums2 中也存在
                ans = min(ans, i + d[nums1[i]]);  // 更新最小下标和
            }
        }
        return ans == inf ? -1 : ans;  // 仍是无穷大说明没有公共元素，返回 -1
    }
};
