// 题目：728. 自除数（Self Dividing Numbers）
// 思路：暴力枚举区间内每个数，逐位取出数字，要求该位非 0 且能整除原数，全部满足即为自除数。
// 时间复杂度：O(n·log right)，区间长度乘以位数；空间复杂度：O(1)（不计返回的结果数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> selfDividingNumbers(int left, int right) {  // left、right 是需要扫描的闭区间端点
        auto check = [&](int x) -> bool {  // 用 lambda 封装单个数的自除数判定，避免重复代码
            for (int y = x; y; y /= 10) {  // y 从 x 开始逐位整除 10，y 变成 0 时说明所有位都检查完
                if (y % 10 == 0 || x % (y % 10)) {  // 该位是 0，或原数不能被这一位整除，都不满足自除数定义
                    return false;  // 提前判定失败
                }  // if 分支结束
            }  // for 循环结束
            return true;  // 所有位都能整除原数，是自除数
        };  // lambda 定义结束
        vector<int> ans;  // ans 收集区间内所有自除数
        for (int x = left; x <= right; ++x) {  // 枚举闭区间 [left, right] 中的每个整数
            if (check(x)) {  // 判断当前数是否自除数
                ans.push_back(x);  // 满足条件则收集到结果
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回收集到的结果数组
    }  // selfDividingNumbers 方法结束
};  // Solution 类定义结束
