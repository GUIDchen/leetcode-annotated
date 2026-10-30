// 题目：3229. 使数组等于目标数组所需的最少操作次数（Minimum Operations to Make Array Equal to Target）
// 思路：记 d[i] = target[i] - nums[i]。相邻差值同号时方向一致，可沿用同一个区间操作，只需补上高度差；异号或出现 0 则操作断开，需整体新增 |d[i]| 次。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用到常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumOperations(vector<int>& nums, vector<int>& target) {  // nums：初始数组；target：目标数组；返回最少的区间加减操作次数
        using ll = long long;  // 计数器可达 1e14 量级，用 64 位整数防止溢出
        ll f = abs(target[0] - nums[0]);  // 首个位置的差值只能由覆盖它的操作单独补足
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个位置开始，逐个比较相邻两个差值
            long x = target[i] - nums[i];  // 当前位置需要的增减量
            long y = target[i - 1] - nums[i - 1];  // 前一个位置需要的增减量
            if (x * y > 0) {  // 同号说明方向一致，两个位置可以共用同一个操作
                ll d = abs(x) - abs(y);  // 只需补上当前差值比前一个多出来的那部分高度
                if (d > 0) {  // 当前差值更大时才需要新增操作
                    f += d;  // 把新增的所需操作次数累加进答案
                }  // 同号分支结束
            } else {  // 异号或有一个为 0：原来的操作无法继续延伸
                f += abs(x);  // 当前位置的整段需求都要由新的操作覆盖
            }  // 异号分支结束
        }  // 循环结束
        return f;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束