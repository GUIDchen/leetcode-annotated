// 3392. 统计符合条件长度为 3 的子数组数目 / Count Subarrays of Length Three With a Condition
// 核心思路：枚举所有长度为 3 的子数组的中间下标 i，判断两侧元素之和的两倍是否等于中间元素，满足则计数加一
// 复杂度：时间 O(n)、空间 O(1)
class Solution {  // 定义 Solution 类
public:  // 公有方法
    int countSubarrays(vector<int>& nums) {  // 统计满足条件的长度为 3 的子数组个数
        int ans = 0;  // 计数器初始化为 0
        for (int i = 1; i + 1 < nums.size(); ++i) {  // 枚举长度为 3 的子数组的中间下标 i
            if ((nums[i - 1] + nums[i + 1]) * 2 == nums[i]) {  // 若中间元素等于两侧元素之和的两倍，则满足条件
                ++ans;  // 计数加一
            }  // 判断结束
        }  // 循环结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束
