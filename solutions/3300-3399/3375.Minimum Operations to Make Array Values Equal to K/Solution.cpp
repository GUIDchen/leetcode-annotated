// 题目：3375. 使数组的值全部为 K 的最少操作次数（Minimum Operations to Make Array Values Equal to K）
// 思路：每次操作可把某个值 h 及其倍数的所有更大元素一起降到 h。因此要先把所有比 k 大的不同值逐个降下来；若数组中出现比 k 小的值则无解，k 已在数组中时可少做一次。
// 时间复杂度：O(n)，一次遍历统计不同值与最小值；空间复杂度：O(n)，集合最多存 n 个不同值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int k) {  // nums 是输入数组，k 是目标值
        unordered_set<int> s;  // 集合：记录数组中所有出现过的不同值
        int mi = INT_MAX;  // 记录数组最小值，用于判断 k 是否已经存在
        for (int x : nums) {  // 遍历数组中的每个元素
            if (x < k) {  // 操作只能把值变小，出现比 k 小的值就无解
                return -1;  // 无法让所有元素都等于 k，返回 -1
            }  // 判断结束
            mi = min(mi, x);  // 维护当前最小值
            s.insert(x);  // 把当前值加入去重集合
        }  // 遍历结束
        return s.size() - (mi == k);  // 不同值个数减去 1（当 k 本身已存在时这一步不用做）
    }  // 方法结束
};  // 题解类定义结束
