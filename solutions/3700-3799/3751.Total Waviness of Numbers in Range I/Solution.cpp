// 题目：3751. 范围内总波动值 I（Total Waviness of Numbers in Range I）
// 核心思路：上界只有 1e5，直接枚举区间内每个数并按位判断峰谷即可。把数位从低位到高位拆进数组（相邻关系不变），不足 3 位波动值为 0，否则统计中间严格大于或严格小于两侧的位数并累加。
// 复杂度：时间 O((num2 - num1 + 1) * log num2)，每个数都要拆位检查；空间 O(log num2)，数位数组大小与位数成正比。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int totalWaviness(int num1, int num2) {  // 返回闭区间 [num1, num2] 内所有数字的波动值之和
        int ans = 0;  // ans 累加区间内每个数的波动值
        for (int x = num1; x <= num2; x++) {  // 逐个遍历区间内的整数 x
            ans += f(x);  // 把 x 的波动值累加进答案
        }  // 循环结束
        return ans;  // 返回总波动值
    }  // 方法结束

    int f(int x) {  // 辅助函数：返回整数 x 的波动值，即其中峰与谷的个数
        int nums[20], m = 0;  // nums 存放 x 的各个数位（低位在前），m 为位数
        while (x > 0) {  // 反复取最低位，把 x 的每一位拆出来
            nums[m++] = x % 10;  // 取最低位放入 nums，位数 m 加一
            x /= 10;  // x 去掉最低位
        }  // 循环结束
        if (m < 3) {  // 不足 3 位的数字没有峰谷
            return 0;  // 波动值为 0
        }  // if 分支结束
        int s = 0;  // s 统计峰和谷的总数
        for (int i = 1; i < m - 1; i++) {  // 首尾数位不可能是峰谷，只遍历中间的数位
            if ((nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) || (nums[i] < nums[i - 1] && nums[i] < nums[i + 1])) {  // 中间位严格大于或严格小于两侧相邻位时，它是一个峰或一个谷
                s++;  // 峰谷计数加一
            }  // if 分支结束
        }  // 遍历结束
        return s;  // 返回 x 的波动值
    }  // 方法结束
};  // 类定义结束
