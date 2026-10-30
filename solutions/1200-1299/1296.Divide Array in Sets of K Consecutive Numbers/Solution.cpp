// 题目：1296. 划分数组为连续数字的集合（Divide Array in Sets of K Consecutive Numbers）
// 思路：先排序并统计每个值的剩余次数，再从小到大取每个仍有余量的值作为一组起点，连续消耗 k 个数。
// 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(n)，哈希表存放每个值的剩余次数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPossibleDivide(vector<int>& nums, int k) {  // nums：输入数组；k：每组要求的连续数字个数
        if (nums.size() % k) {  // 元素总数不是 k 的整数倍，必然无法完全分组
            return false;  // 直接判定不可能
        }
        ranges::sort(nums);  // 升序排序，保证按从小到大依次作为每组起点
        unordered_map<int, int> cnt;  // 记录每个数值还剩多少个没被用掉
        for (int x : nums) {  // 遍历数组统计频次
            ++cnt[x];  // 当前值的计数加一
        }
        for (int x : nums) {  // 按升序再扫一遍，尝试以每个值作为一组起点
            if (cnt.contains(x)) {  // 该值还有剩余，说明必须从这里开新的一组
                for (int y = x; y < x + k; ++y) {  // 组内需要 x, x+1, ..., x+k-1 这 k 个连续值
                    if (!cnt.contains(y)) {  // 中间某个连续值已被用光，凑不满一组
                        return false;  // 分组失败
                    }
                    if (--cnt[y] == 0) {  // 用掉一个该值，若计数归零
                        cnt.erase(y);  // 从哈希表删除，contains 之后就不会再命中它
                    }
                }
            }
        }
        return true;  // 所有数都被成功分组
    }
};
