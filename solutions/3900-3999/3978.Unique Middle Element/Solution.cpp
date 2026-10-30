// 3978. Unique Middle Element | 唯一中间元素（简单）
// 核心思路：取出下标 n / 2 处的中间元素，再整个数组扫一遍统计它出现的次数，次数等于 1 说明中间元素是唯一的。
// 复杂度：时间 O(n)，一次遍历；空间 O(1)，只用常数个变量。
class Solution {  // 定义题解类
public:  // 公有接口
    bool isMiddleElementUnique(vector<int>& nums) {  // 返回中间元素是否在整个数组中只出现一次
        int n = nums.size();  // 数组长度
        int cnt = 0;  // 中间元素出现的次数
        for (int x : nums) {  // 遍历数组中的每个元素
            if (x == nums[n / 2]) {  // 与中间元素（下标 n / 2，偶数长度时取靠右的那个）比较
                ++cnt;  // 数值相同，计数加一
            }  // if 结束
        }  // 遍历结束
        return cnt == 1;  // 只出现一次才是“唯一”
    }  // 方法结束
};  // 类定义结束