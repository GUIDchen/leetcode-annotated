// 题目：2210. 统计数组中峰和谷的数量（Count Hills and Valleys in an Array）
// 核心思路：线性扫描。j 指向 i 左侧最近的一个「不同值」下标；跳过与右邻相同的平坡位置，
//           再分别用 nums[j] 与 nums[i+1] 作为左右邻居，判断严格大于（峰）或严格小于（谷）。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用两个下标与一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countHillValley(vector<int>& nums) {  // nums 是待统计的数组
        int ans = 0;  // 记录峰和谷的总个数
        for (int i = 1, j = 0; i < nums.size() - 1; ++i) {  // i 指向待判断的位置，j 指向它左侧最近的不同值下标
            if (nums[i] == nums[i + 1]) {  // 与右邻相等，说明还处在一段平坡的内部
                continue;  // 先跳过，等平坡走到最后一格再判断
            }
            if (nums[i] > nums[j] && nums[i] > nums[i + 1]) {  // 严格高于左右两侧不同值，说明是山峰
                ++ans;  // 峰计数加一
            }
            if (nums[i] < nums[j] && nums[i] < nums[i + 1]) {  // 严格低于左右两侧不同值，说明是山谷
                ++ans;  // 谷计数加一
            }
            j = i;  // 当前值成为新的左侧比较基准，供右侧元素使用
        }
        return ans;  // 返回峰与谷的总个数
    }
};