// 题目：2568. 最小无法得到的或值（Minimum Impossible OR）
// 思路：任意子集的按位或若要等于 2^i，数组中必须存在 2^i（更大的数会带上别的二进制位）；因此答案就是最小的、不在数组中的 2 的幂。
// 时间复杂度：O(n + 32)，建哈希表 O(n)，再从小到大检查 32 个 2 的幂；空间复杂度：O(n)，哈希集合存放所有元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minImpossibleOR(vector<int>& nums) {  // nums：可用元素（每个最多用一次）的数组
        unordered_set<int> s(nums.begin(), nums.end());  // 把数组放进哈希集合，便于 O(1) 判断某个值是否存在
        for (int i = 0;; ++i) {  // 从小到大枚举 2 的幂 2^i，题目数据保证 32 位内一定会有缺失项
            if (!s.count(1 << i)) {  // 2^i 不在集合中，任何子集的或都无法造出它
                return 1 << i;  // 第一个缺失的 2 的幂就是最小无法得到的或值
            }
        }
    }
};