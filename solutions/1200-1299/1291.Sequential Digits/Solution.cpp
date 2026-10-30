// 题目：1291. 顺次数（Sequential Digits）
// 核心思路：枚举起始数字与依次拼接的后续数字，构造出全部顺次数，筛出落在 [low, high] 内的并按升序返回。
// 时间复杂度：O(1)，顺次数总量固定（本代码只生成 36 个）；空间复杂度：O(1)，答案规模为常数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sequentialDigits(int low, int high) {  // low、high 是取值区间，返回区间内所有「顺次数」（相邻数位依次加一）
        vector<int> ans;  // ans 收集所有满足区间的顺次数
        for (int i = 1; i < 9; ++i) {  // 枚举起始数字 1..8；起始为 9 时后面无数字可接，故不取 9
            int x = i;  // x 从单个数字 i 开始，往后不断拼接连续数字
            for (int j = i + 1; j < 10; ++j) {  // 枚举下一个要拼上的数字 j
                x = x * 10 + j;  // 在末尾拼接数字 j，相当于长度加一
                if (x >= low && x <= high) {  // 判断拼出的数是否落在 [low, high] 内
                    ans.push_back(x);  // 落在区间内，加入答案
                }  // 结束 if 分支
            }  // 结束内层循环
        }  // 结束外层循环
        sort(ans.begin(), ans.end());  // 拼接顺序并不等于数值大小顺序，最后统一排序
        return ans;  // 返回升序排列的答案
    }  // 结束函数
};  // 结束题解类