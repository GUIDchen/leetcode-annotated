// 题目：3010. 将数组分成最小总代价的子数组 I（Divide an Array Into Subarrays With Minimum Cost I）
// 思路：第一个子数组必须包含首元素，所以总代价 = nums[0] + 其后最小的两个元素；一次遍历同时维护最小值与次小值即可。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(vector<int>& nums) {  // nums：输入数组；返回把数组切成三个子数组的最小总代价
        int a = nums[0], b = 100, c = 100;  // a 固定取首元素作为第一段代价；b、c 记录后面出现过的最小值与次小值，初值 100 不小于题面元素上限
        for (int i = 1; i < nums.size(); ++i) {  // 从下标 1 开始扫描，首元素已被第一段固定占用，不再参与挑选
            if (nums[i] < b) {  // 当前值比已知最小值还小：原来的最小值要让位
                c = b;  // 旧的最小值降级成次小值
                b = nums[i];  // 当前值成为新的最小值
            } else if (nums[i] < c) {  // 不比最小值小，但比次小值小：只需要更新次小值
                c = nums[i];  // 把次小值刷新为当前值
            }  // 两个分支都没命中，说明当前值连次小值都排不上，忽略
        }  // 遍历结束，此时 b、c 就是 nums[1..] 中最小的两个值
        return a + b + c;  // 三段代价相加：首元素 + 后面最小的两个元素
    }  // minimumCost 方法结束
};  // Solution 类定义结束