// 题目：3862. 找出最小平衡下标（Find the Smallest Balanced Index）
// 思路：从右往左枚举，用「总和减去当前元素」维护左侧和、用累乘维护右侧积，并做乘法溢出检查与单调性剪枝。
// 时间复杂度：O(n)，只扫描一遍；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestBalancedIndex(vector<int>& nums) {  // 返回最小平衡下标（左侧和等于右侧积），不存在则返回 -1
        long long s = 0, p = 1;  // s：左侧元素的总和；p：右侧元素的乘积（空乘积记为 1）
        for (int x : nums) {  // 先求整个数组的总和
            s += x;  // 累加当前元素，之后减去 nums[i] 即得左侧和
        }
        for (int i = nums.size() - 1; i >= 0; --i) {  // 从右往左枚举，p 可以直接递推成右侧乘积
            s -= nums[i];  // 扣掉 nums[i]，此时 s 正是下标 i 严格左侧的元素和
            if (s == p) {  // 左侧和等于右侧积，说明 i 是平衡下标
                return i;  // 直接返回（元素均为正数时平衡下标唯一）
            }
            if (p > LLONG_MAX / nums[i]) {  // 乘法前先做 long long 溢出检查
                break;  // 再乘就会溢出，后面不可能再有答案
            }
            p *= nums[i];  // 把 nums[i] 并入乘积，供下一个更小的下标使用
            if (p >= s) {  // 剪枝：继续左移时 p 只增、s 只减，不可能再相等
                break;  // 提前结束
            }
        }
        return -1;  // 遍历完都没有平衡下标，返回 -1
    }
};
