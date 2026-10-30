// 题目：967. 连续差相同的数字（Numbers With Same Consecutive Differences）
// 思路：DFS 逐位构造整数，从 1~9 作为最高位出发，每次在末尾追加与上一位相差 k 的数字，位数达标就收集。
// 时间复杂度：O(答案个数 * n)，每个答案构造 n 位；空间复杂度：O(n)，递归深度等于位数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> numsSameConsecDiff(int n, int k) {  // n 是位数，k 是相邻两位数字之差的绝对值
        vector<int> ans;  // 收集所有符合条件的整数
        int boundary = pow(10, n - 1);  // boundary = 10^(n-1)，即 n 位数的最小值，用来判断位数是否已够
        auto dfs = [&](this auto&& dfs, int x) {  // DFS：从已构造出的数值 x 继续向低位扩展
            if (x >= boundary) {  // x 已不小于 10^(n-1)，说明已经构造出 n 位，可以收集
                ans.push_back(x);  // 收集这个数
                return;  // 结束当前分支
            }  // 位数判断结束
            int last = x % 10;  // 取出当前的末位数字
            if (last + k < 10) {  // 末位加 k 仍是个位数字，可以继续追加
                dfs(x * 10 + last + k);  // 追加 (last + k) 这一位后继续递归
            }  // 加法分支结束
            if (k != 0 && last - k >= 0) {  // 末位减 k 仍是个位数字；k 为 0 时与上一分支重复，故需排除
                dfs(x * 10 + last - k);  // 追加 (last - k) 这一位后继续递归
            }  // 减法分支结束
        };  // 递归 lambda 定义结束
        for (int i = 1; i < 10; ++i) {  // 首位不能为 0，从 1 到 9 依次作为起点
            dfs(i);  // 以 i 为最高位开始构造
        }  // 起点遍历结束
        return ans;  // 返回全部结果
    }  // 方法结束
};  // 题解类结束
