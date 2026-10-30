// 题目：1755. 最接近目标值的子序列和（Closest Subsequence Sum）
// 思路：折半枚举——递归求出左右两半各自的全部子集和，把右半排序，再对每个左半和二分查找最接近 goal - x 的右半和。
// 时间复杂度：O(n·2^(n/2))，枚举子集共 2^(n/2) 个、每个左半和做一次二分；空间复杂度：O(2^(n/2))，存放两半的子集和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minAbsDifference(vector<int>& nums, int goal) {  // nums 是输入数组，goal 是目标值
        int n = nums.size();  // 数组长度
        vector<int> lsum;  // 左半 [0, n/2) 所有子集的和
        vector<int> rsum;  // 右半 [n/2, n) 所有子集的和
        dfs(nums, lsum, 0, n / 2, 0);  // 递归枚举左半的全部子集和
        dfs(nums, rsum, n / 2, n, 0);  // 递归枚举右半的全部子集和

        sort(rsum.begin(), rsum.end());  // 右半子集和排序，为后面的二分查找做准备
        int res = INT_MAX;  // 记录目前最小的 |子集和 - goal|

        for (int x : lsum) {  // 枚举左半的每一个子集和 x
            int target = goal - x;  // 右半需要凑出的理想值：加上 x 后正好等于 goal
            int left = 0, right = rsum.size();  // 在 rsum 中二分查找第一个 >= target 的位置
            while (left < right) {  // 左闭右开区间写法，结束时 left 即下界
                int mid = (left + right) >> 1;  // 取中点（右移一位等价于除以 2）
                if (rsum[mid] < target) {  // 中点值偏小，答案一定在右半段
                    left = mid + 1;  // 收缩左边界
                } else {  // 中点值已经不小于 target，答案可能在左半段（含 mid）
                    right = mid;  // 收缩右边界
                }
            }
            if (left < rsum.size()) {  // 存在 >= target 的最小右半和，用它更新答案
                res = min(res, abs(target - rsum[left]));  // 计算偏差并取较小值
            }
            if (left > 0) {  // 同时检查下界左侧、即小于 target 的最大右半和，它也可能更接近
                res = min(res, abs(target - rsum[left - 1]));  // 计算偏差并取较小值
            }
        }

        return res;  // 遍历完所有组合，res 就是最小的绝对差
    }

private:  // 以下为辅助函数，不对外暴露
    void dfs(vector<int>& nums, vector<int>& sum, int i, int n, int cur) {  // 从下标 i 递归到 n，cur 是当前已选元素之和
        if (i == n) {  // 区间内的元素都决定完了，得到一个完整子集和
            sum.emplace_back(cur);  // 把当前子集和收集起来
            return;  // 递归出口
        }

        dfs(nums, sum, i + 1, n, cur);  // 分支一：不选 nums[i]，和不变
        dfs(nums, sum, i + 1, n, cur + nums[i]);  // 分支二：选 nums[i]，和加上它
    }
};