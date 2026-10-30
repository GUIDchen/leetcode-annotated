// 题目：3300. 替换为数位和以后的最小元素（Minimum Element After Replacement With Digit Sum）
// 思路：把每个元素替换成它的数位和，边算边取最小值。
// 时间复杂度：O(n log M)，每个元素需逐位拆分（M 为元素大小）；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minElement(vector<int>& nums) {  // nums：输入数组；返回把每个元素替换成数位和后得到的新数组的最小值
        int ans = 100;  // ans 存最小数位和；数位和最大为 99，初值取 100 表示“无穷大”
        for (int x : nums) {  // 逐个元素处理
            int y = 0;  // y 累加当前元素的各位数字之和
            for (; x > 0; x /= 10) {  // 反复取最低位并去掉最低位，直到 x 变成 0
                y += x % 10;  // 取出最低位数字累加到 y
            }
            ans = min(ans, y);  // 用当前元素的数位和更新最小值
        }
        return ans;  // 返回最终的最小值
    }
};
