// 题目：2960. 统计已测试设备（Count Tested Devices After Test Operations）
// 思路：按顺序遍历，ans 既表示已测试设备数，也表示所有剩余设备累计被扣减的电量；当前电量大于 ans 就能被测试。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countTestedDevices(vector<int>& batteryPercentages) {  // batteryPercentages 为各设备的初始电量百分比
        int ans = 0;  // ans 既是已测试设备数，也是后续设备累计被扣减的电量
        for (int x : batteryPercentages) {  // 按顺序处理每台设备
            ans += x > ans;  // 当前电量大于累计扣减量就能被测试，ans 加一（布尔值转为 0/1）
        }  // 遍历结束
        return ans;  // 返回已测试设备数
    }  // 方法体结束
};  // 题解类结束