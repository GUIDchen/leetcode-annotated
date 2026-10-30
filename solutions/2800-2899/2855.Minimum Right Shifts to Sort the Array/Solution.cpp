// 题目：2855. 使数组成为递增数组的最少右移次数（Minimum Right Shifts to Sort the Array）
// 核心思路：右移等价于循环移位，先找到第一段严格递增的结尾 i，再验证剩余部分也递增且都小于首元素，答案是 n - i。
// 时间复杂度：O(n)，只线性扫描一遍；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外公开的接口区域
    int minimumRightShifts(vector<int>& nums) {  // nums 为待排序的数组
        int n = nums.size();  // 数组长度
        int i = 1;  // i 指向第一段严格递增区间的下一个位置
        while (i < n && nums[i - 1] < nums[i]) {  // 找到第一处不再严格递增的断点
            ++i;  // 仍然递增就继续右移指针
        }  // 结束 while 循环
        int k = i + 1;  // 从断点的下一位开始检查第二段
        while (k < n && nums[k - 1] < nums[k] && nums[k] < nums[0]) {  // 第二段必须严格递增，且整体小于首元素（右移后它会排到最前面）
            ++k;  // 满足条件就继续右移指针
        }  // 结束 while 循环
        return k < n ? -1 : n - i;  // k 没走到末尾说明无法通过右移变成递增，返回 -1；否则需要右移 n - i 次
    }  // 结束函数体
};  // 结束类定义