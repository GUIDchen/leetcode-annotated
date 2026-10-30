// 题目：1121. 将数组分成几个递增序列（Divide Array Into Increasing Sequences）
// 思路：数组非降序，同一个值出现 cnt 次就必须分进 cnt 个不同的子序列，于是至少要有 cnt*k 个元素；一遍扫描求最大重复次数并检验即可。
// 时间复杂度：O(n)，只扫描一遍；空间复杂度：O(1)，只用两个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {  // nums 非降序；判断能否切成若干不相交的、长度至少为 k 的严格递增子序列
        int cnt = 0;  // 当前这个值已经连续出现了多少次
        int a = 0;  // 上一个读到的元素值；哨兵取 0，因为题目元素都 ≥ 1
        for (int& b : nums) {  // 用引用遍历，逐个比较相邻元素
            cnt = a == b ? cnt + 1 : 1;  // 与上一个值相等就继续累加，否则这段重复结束了，重新从 1 开始计数
            if (cnt * k > nums.size()) {  // 同一个值出现 cnt 次至少要占 cnt 个子序列，每个子序列长 k，所以至少需要 cnt*k 个元素
                return false;  // 元素总数不够，无法完成分割
            }  // 不满足条件的分支结束
            a = b;  // 记住当前值，作为下一轮的「上一个元素」
        }  // 扫描结束
        return true;  // 所有值的重复次数都满足 cnt*k <= n，可以分割
    }  // 方法结束
};  // 类定义结束