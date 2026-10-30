// 题目：2934. 最大化数组末位元素的最少操作次数（Minimum Operations to Maximize Last Elements in Arrays）
// 思路：最终末位只有两种可能——保持 (nums1[-1], nums2[-1]) 或交换成 (nums2[-1], nums1[-1])；对每种目标各求一次最少交换次数再取小。
// 时间复杂度：O(n)，每种方案线性扫描一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums1, vector<int>& nums2) {  // nums1 / nums2：两个等长数组，一次操作可交换同一位置上的两个元素
        int n = nums1.size();  // 数组长度
        auto f = [&](int x, int y) {  // 闭包：让末位变成 (x, y) 时，前面 n-1 个位置需要的最少交换次数
            int cnt = 0;  // 该方案下累计的交换次数
            for (int i = 0; i < n - 1; ++i) {  // 只检查前 n-1 个位置，末位由参数 x、y 指定
                if (nums1[i] <= x && nums2[i] <= y) {  // 不交换就已满足不超过末位，无需操作
                    continue;  // 直接跳过当前位置
                }
                if (!(nums1[i] <= y && nums2[i] <= x)) {  // 交换后仍不满足，说明这个目标末位无法达成
                    return -1;  // 返回 -1 表示该方案无解
                }
                ++cnt;  // 只能靠交换来满足，计数加一
            }
            return cnt;  // 返回该方案所需的最少交换次数
        };  // 闭包定义结束
        int a = f(nums1.back(), nums2.back());  // 方案一：末位保持原样
        int b = f(nums2.back(), nums1.back());  // 方案二：末位两个元素互换，因此还要额外算一次操作
        return a + b == -2 ? -1 : min(a, b + 1);  // 两种方案都无解时返回 -1；否则取较小值，方案二记得加上末位的那一次交换
    }
};  // 类定义结束