// 3759. 统计合格元素的数目（Count Elements With at Least K Greater Values）
// 核心思路：排序后，下标 i 处的元素后面至少有 k 个更大值，当且仅当 nums[n-k] > nums[i]；只需统计前 n-k 个位置中满足该不等式的个数。
// 复杂度：时间 O(n log n)（排序），空间 O(1)（不计排序栈）。
class Solution {  // 定义解法类
public:  // 公有接口
    int countElements(vector<int>& nums, int k) {  // 接口：统计至少有 k 个更大值的元素个数
        int n = nums.size();  // n 为数组长度
        if (k == 0) {  // k 为 0 时任何元素都满足条件
            return n;  // 直接返回全部元素个数
        }  // if 结束
        ranges::sort(nums);  // 升序排序，方便用下标定位第 k 大的位置
        int ans = 0;  // ans 统计合格元素个数
        for (int i = 0; i < n - k; ++i) {  // 只有前 n - k 个位置才有可能凑够 k 个更大的值
            if (nums[n - k] > nums[i]) {  // 排序后第 n - k 个元素是判断门槛：比它小就至少有 k 个更大值
                ++ans;  // 满足条件则计数加一
            }  // if 结束
        }  // for 结束
        return ans;  // 返回合格元素个数
    }  // 方法结束
};  // 类定义结束
