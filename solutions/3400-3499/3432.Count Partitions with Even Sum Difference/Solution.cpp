// 3432. Count Partitions with Even Sum Difference / 3432. 统计元素和差值为偶数的分区方案
// 核心思路：l 为左侧和、r 为右侧和，逐位移动分界并判断 (l - r) 是否为偶数。
// 复杂度：时间 O(n)，空间 O(1)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    int countPartitions(vector<int>& nums) {  // 返回元素和差值为偶数的分区方案数
        int l = 0, r = accumulate(nums.begin(), nums.end(), 0);  // l 为左侧元素和，r 先取全部元素和，后续动态维护为右侧和
        int ans = 0;  // 记录满足条件的分区个数
        for (int i = 0; i < nums.size() - 1; ++i) {  // 分区点 i 取 0 到 n-2，保证左右两侧都非空
            l += nums[i];  // 把 nums[i] 从右侧并入左侧
            r -= nums[i];  // 右侧和同步减去 nums[i]
            if ((l - r) % 2 == 0) {  // (l - r) 为偶数等价于 l 与 r 奇偶性相同
                ++ans;  // 满足条件，方案数加一
            }
        }  // 分区点枚举结束
        return ans;  // 返回方案总数
    }  // 方法结束
};  // 类定义结束
