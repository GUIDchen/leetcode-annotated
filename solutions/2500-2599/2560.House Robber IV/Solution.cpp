// 题目：2560. 打家劫舍 IV（House Robber IV）
// 核心思路：二分答案「最小能力值 x」，贪心判断能力值为 x 时能否在不相邻的前提下偷到至少 k 间房。
// 时间复杂度：O(n log M)，M 为金额最大值；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCapability(vector<int>& nums, int k) {  // nums：每间房的金额；k：至少要偷的间数
        auto f = [&](int x) {  // 可行性函数：能力值为 x 时能否偷满 k 间
            int cnt = 0, j = -2;  // cnt 是已偷间数；j 是上一次偷的房间下标，初值 -2 表示还没偷过
            for (int i = 0; i < nums.size(); ++i) {  // 从左到右尝试每一间房
                if (nums[i] > x || i == j + 1) {  // 金额超过能力值，或与上一次偷的房相邻
                    continue;  // 这间不能偷，直接看下一间
                }
                ++cnt;  // 偷下这间房，计数加一
                j = i;  // 记录本次偷的位置，供下一次相邻性判断
            }
            return cnt >= k;  // 偷到的间数达到 k 即说明 x 可行
        };
        int left = 0, right = *max_element(nums.begin(), nums.end());  // 答案一定落在 [0, 最大金额] 内
        while (left < right) {  // 二分查找第一个可行的能力值
            int mid = (left + right) >> 1;  // 取中点，>>1 等价于整除 2，可避免加法溢出
            if (f(mid)) {  // mid 可行，答案可能是 mid 或更小
                right = mid;  // 收缩右边界
            } else {  // mid 不可行，答案必定更大
                left = mid + 1;  // 收缩左边界
            }
        }
        return left;  // 边界重合处就是最小可行能力值
    }
};