// 3868. 通过交换使数组相等的最小花费 / Minimum Cost to Equalize Arrays Using Swaps
// 核心思路：同数组内交换免费，故只有多重集合有意义；用 nums2 的计数逐个抵消 nums1 的元素，剩下的差异元素必须跨数组交换，每两次差异（一对）花 1 次交换，任一计数为奇数则无解。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)（哈希表存储各值的计数）。
class Solution {  // LeetCode 题解类
public:  // 公有成员
    int minCost(vector<int>& nums1, vector<int>& nums2) {  // 返回使两数组相同的最小花费，无解返回 -1
        unordered_map<int, int> cnt2;  // nums2 各值的剩余计数
        for (int x : nums2) {  // 统计 nums2 中每个值的出现次数
            ++cnt2[x];  // 值 x 的计数加一
        }  // nums2 计数完成

        unordered_map<int, int> cnt1;  // nums1 中未被抵消的差异元素计数
        for (int x : nums1) {  // 用 nums2 的计数逐个抵消 nums1
            if (cnt2[x] > 0) {  // nums2 里还有相同的值可以配对
                --cnt2[x];  // 消费一个，该位置无需交换
            } else {  // nums2 里已无相同值
                ++cnt1[x];  // 记入 nums1 的差异元素
            }  // 分支结束
        }  // nums1 扫描完成

        int ans = 0;  // 累计最小花费（跨数组交换次数）

        for (auto& [_, v] : cnt1) {  // 遍历 nums1 的差异计数
            if (v & 1) {  // 该值的差异个数为奇数
                return -1;  // 奇数个元素无法两两配对，方案不存在
            }  // 检查通过
            ans += v / 2;  // 每两个差异元素做一次跨数组交换，花费加 v/2
        }  // nums1 差异统计完毕

        for (auto& [_, v] : cnt2) {  // 遍历 nums2 的剩余计数（与 cnt1 镜像）
            if (v & 1) {  // 该值剩余个数为奇数
                return -1;  // 同样无法两两配对，方案不存在
            }  // 检查通过
        }  // nums2 剩余检查完毕

        return ans;  // 返回最小花费
    }  // 方法结束
};  // 类结束
