// 题目：747. 至少是其他数字两倍的最大数（Largest Number At Least Twice of Others）
// 核心思路：第一趟扫描找出最大元素的下标，第二趟扫描检查是否所有其他元素的两倍都不超过最大值，满足则返回该下标，否则返回 -1。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只用一个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int dominantIndex(vector<int>& nums) {  // nums 是待检查的数组，题目保证 n >= 2
        int n = nums.size();  // 数组长度，供两趟循环复用
        int k = 0;  // k 记录最大元素的下标，先假设它是第 0 个
        for (int i = 0; i < n; ++i) {  // 第一趟：顺序扫描找最大值所在位置
            if (nums[k] < nums[i]) {  // 发现比当前最大值更大的元素
                k = i;  // 把最大值的下标更新为 i
            }  // 结束最大值比较
        }  // 结束第一趟扫描
        for (int i = 0; i < n; ++i) {  // 第二趟：验证最大值是否至少是其他每个元素的两倍
            if (k != i && nums[k] < nums[i] * 2) {  // 跳过最大值本身；若存在其他元素的两倍更大就不满足题意
                return -1;  // 立即返回 -1，无需继续检查
            }  // 结束条件判断
        }  // 结束第二趟扫描
        return k;  // 全部检查通过，最大元素的下标就是答案
    }  // 结束 dominantIndex 方法
};  // 结束 Solution 类