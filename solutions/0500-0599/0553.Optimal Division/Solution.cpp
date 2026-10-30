// 题目：553. 最优除法（Optimal Division）
// 核心思路：第一个数作被除数，把第二个数起的其余数字整体用括号括起来当除数，结果最大。
// 时间复杂度：O(n)，只需一次线性拼接；空间复杂度：O(n)，用于存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string optimalDivision(vector<int>& nums) {  // nums：正整数数组，返回使表达式值最大的除法字符串
        int n = nums.size();  // n 为元素个数，按 1 个、2 个、多于 2 个三种情况分别构造
        if (n == 1) return to_string(nums[0]);  // 只有一个数：表达式只能是它本身
        if (n == 2) return to_string(nums[0]) + "/" + to_string(nums[1]);  // 两个数：没有括号可用，结果固定为 a/b
        string ans = to_string(nums[0]) + "/(";  // 先拼出「第一个数/(」，准备把其余数整体作为除数
        for (int i = 1; i < n - 1; i++) ans.append(to_string(nums[i]) + "/");  // 依次拼接中间元素，每个元素后面跟一个除号
        ans.append(to_string(nums[n - 1]) + ")");  // 追加最后一个元素并闭合括号，得到 a/(b/c/.../z)
        return ans;  // 返回构造好的最优表达式
    }  // 方法结束
};  // 类定义结束