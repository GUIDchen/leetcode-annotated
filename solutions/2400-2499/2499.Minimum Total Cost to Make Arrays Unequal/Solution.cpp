// 题目：2499. 让数组不相等的最小总代价（Minimum Total Cost to Make Arrays Unequal）
// 思路：冲突位置（nums1[i]==nums2[i]）先用代价 i 收进交换池；若某值在冲突中超过半数，还需再从非冲突位置里挑代价最小、且两端都不等于该值的位置来稀释，仍不够则无解。
// 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，计数数组大小为 n+1。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 等长，返回让对应位置全不相等的最小总代价
        long long ans = 0;  // 累计的总代价，用 long long 防止下标求和溢出
        int same = 0;  // 统计冲突位置（同下标两元素相等）的个数
        int n = nums1.size();  // 数组长度
        int cnt[n + 1];  // 计数数组：cnt[x] 表示值 x 在冲突位置中出现的次数
        memset(cnt, 0, sizeof cnt);  // 把计数数组全部清零
        for (int i = 0; i < n; ++i) {  // 第一遍：所有冲突位置先支付下标代价，并统计各值在冲突中出现的次数
            if (nums1[i] == nums2[i]) {  // 该位置两元素相等，是必须处理的冲突
                ans += i;  // 与下标 i 交换的代价最小，先把这个代价计入
                ++same;  // 冲突个数加一
                ++cnt[nums1[i]];  // 记录该值在冲突中出现的次数
            }
        }
        int m = 0, lead = 0;  // m 是仍需额外抵消的多余冲突数，lead 是出现次数过多的那个值
        for (int i = 0; i < n + 1; ++i) {  // 遍历所有可能的值（值域 0..n）
            int t = cnt[i] * 2 - same;  // 某值出现次数超过冲突总数的一半时，超出部分无法在冲突内部两两配对
            if (t > 0) {  // 多出来的这部分要靠引入新位置来消解
                m = t;  // 记录还需要的外部位置数量
                lead = i;  // 记录这个多数值
                break;  // 至多只有一个值会超过半数，找到就可以跳出
            }
        }
        for (int i = 0; i < n; ++i) {  // 第二遍：从非冲突位置里挑代价最小的位置，用来稀释多数值的冲突
            if (m > 0 && nums1[i] != nums2[i] && nums1[i] != lead && nums2[i] != lead) {  // 该位置本身不冲突，且两个元素都不等于 lead，交换后才能消解一个多数冲突
                ans += i;  // 支付下标代价 i
                --m;  // 需要的外部位置数减一
            }
        }
        return m > 0 ? -1 : ans;  // m 仍大于 0 说明冲突无法全部消解，无解返回 -1；否则返回最小总代价
    }
};  // 类定义结束