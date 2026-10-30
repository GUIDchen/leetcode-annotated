// 题目：3859. 统计包含 K 个不同整数的子数组（Count Subarrays With K Distinct Integers）
// 思路：把「恰好 k 个不同值」写成两类单调条件计数之差 f(k) - f(k+1)，f 用双指针加哈希表统计不同值不少于 lim、且出现次数达到 m 的值不少于 k 个的子数组。
// 时间复杂度：O(n)，两次滑动窗口各扫描一遍；空间复杂度：O(n)，哈希表最多保存 n 个不同值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubarrays(vector<int>& nums, int k, int m) {  // nums：输入数组；k：不同整数个数；m：每个整数的最少出现次数
        auto f = [&](int lim) -> long long {  // 定义 f(lim)：统计不同值不少于 lim、且达标值不少于 k 个的子数组数
            unordered_map<int, int> cnt;  // 滑动窗口内每个值的出现次数
            long long ans = 0;  // 该 f 的计数结果
            int l = 0;  // 滑动窗口左端点
            int t = 0;  // 出现次数已达到 m 的不同值个数

            for (int x : nums) {  // 右端点逐个右移
                if (++cnt[x] == m) {  // 当前值的计数刚好达到 m
                    ++t;  // 达标的不同值个数加一
                }

                while (cnt.size() >= lim && t >= k) {  // 窗口过大时收缩左端：不同值不少于 lim 且达标值不少于 k
                    int y = nums[l++];  // 取出左端点元素，并把左端点右移
                    if (--cnt[y] == m - 1) {  // 移除后计数恰好掉到 m - 1，说明该值不再达标
                        --t;  // 达标的不同值个数减一
                    }
                    if (cnt[y] == 0) {  // 该值已完全移出窗口
                        cnt.erase(y);  // 从哈希表删除，保证 size() 等于不同值个数
                    }
                }

                ans += l;  // 收缩后 l 恰为以当前下标结尾的过大子数组个数（左端点在 [0, l-1]）
            }

            return ans;  // 返回 f(lim) 的结果
        };

        return f(k) - f(k + 1);  // 差分：不同值不少于 k 的减去不少于 k+1 的，恰好留下 k 个不同值
    }
};
