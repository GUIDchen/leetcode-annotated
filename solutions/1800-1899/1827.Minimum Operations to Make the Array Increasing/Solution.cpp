// 题目：1827. 最少操作使数组递增（Minimum Operations to Make the Array Increasing）
// 思路：一次遍历，用 mx 记录处理到当前元素后必须达到的最小值，nums[i] 补到 mx+1 的差值累加进答案。
// 时间复杂度：O(n)，只遍历一次；空间复杂度：O(1)，只用两个辅助变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：输入数组；返回使数组严格递增的最少操作次数
        int ans = 0, mx = 0;  // ans 累计操作次数；mx 记录处理完当前位置后应达到的最小值
        for (int& v : nums) {  // 按顺序遍历每个元素（引用避免拷贝）
            ans += max(0, mx + 1 - v);  // 要让 v 严格大于前一个值，至少要补到 mx+1
            mx = max(mx + 1, v);  // 更新 mx：取「抬到 mx+1」与原值中较大的那个
        }  // 循环结束
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束