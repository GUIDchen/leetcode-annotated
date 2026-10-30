// 题目：1537. 最大得分（Get the Maximum Score）
// 思路：双指针同时走两条严格递增路径，f、g 分别表示停在 nums1/nums2 当前位置时的最大得分；遇到相同值（交点）时从两者中较大者切换继续。
// 时间复杂度：O(m+n)，两指针各自只前进不后退；空间复杂度：O(1)，仅用几个变量保存路径得分。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSum(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两条严格递增的路径
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        int m = nums1.size(), n = nums2.size();  // 两条路径各自的长度
        int i = 0, j = 0;  // 双指针，分别指向两条路径当前待取的元素
        long long f = 0, g = 0;  // f、g：以 nums1、nums2 当前元素结尾时的最大得分，用 long long 防止累加溢出
        while (i < m || j < n) {  // 两条路径只要有一条没走完就继续
            if (i == m) {  // nums1 已经走完，只能接着走 nums2
                g += nums2[j++];  // 把 nums2 当前元素计入 g，指针后移
            } else if (j == n) {  // nums2 已经走完，只能接着走 nums1
                f += nums1[i++];  // 把 nums1 当前元素计入 f，指针后移
            } else if (nums1[i] < nums2[j]) {  // nums1 当前值更小，先把它取走
                f += nums1[i++];  // 累加到 nums1 这条路径的得分上
            } else if (nums1[i] > nums2[j]) {  // nums2 当前值更小
                g += nums2[j++];  // 累加到 nums2 这条路径的得分上
            } else {  // 两值相等，这里是两条路径可以互换的汇合点
                f = g = max(f, g) + nums1[i];  // 取两条路径中得分更高的一条，加上当前交点值后两者重新同步
                i++;  // 交点被两条路径共享，nums1 指针前进
                j++;  // nums2 指针同时前进
            }  // 分支结束
        }  // 双指针遍历结束
        return max(f, g) % mod;  // 两条路径走到头后取较大得分，再按题目要求取模
    }  // 方法结束
};  // 题解类结束