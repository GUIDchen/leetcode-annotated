// 3876. 构造奇偶一致的数组 II（Construct Uniform Parity Array II）
// 核心思路：所有奇数都能被最小的那个奇数「消成」偶数，所以只需找出最小奇数 mn；只要每个偶数都不小于 mn，就能通过减法把整个数组变成偶数，否则无解。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 公有成员
    bool uniformArray(vector<int>& nums1) {  // 判断能否把所有元素统一成同一种奇偶性
        int mn = INT_MAX;  // 记录最小奇数，初值为「不存在」
        for (int x : nums1) {  // 第一遍：寻找最小奇数
            if (x % 2 == 1) {  // 当前元素是奇数
                mn = min(mn, x);  // 更新最小奇数
            }  // 奇数判断结束
        }  // 第一遍遍历结束
        for (int x : nums1) {  // 第二遍：检查每个偶数
            if (x % 2 == 0 && mn != INT_MAX && x < mn) {  // 存在比最小奇数还小的偶数
                return false;  // 该偶数无法被消成偶数，无解
            }  // 冲突判断结束
        }  // 第二遍遍历结束
        return true;  // 不存在冲突，可以统一成偶数
    }  // 方法结束
};  // 类结束
