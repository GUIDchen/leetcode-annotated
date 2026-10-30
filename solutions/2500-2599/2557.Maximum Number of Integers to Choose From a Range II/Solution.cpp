// 题目：2557. 从一个范围内选择最多整数 II（Maximum Number of Integers to Choose From a Range II）
// 思路：补上虚拟边界 0 与 n+1 后排序去重，相邻禁用值之间就是一段连续可选区间；对每段二分出在剩余预算内最多能选几个（取最小的若干个数，即从 i+1 开始），选完扣掉等差数列和。
// 时间复杂度：O(b log b + b log n)，b 为禁用值个数；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxCount(vector<int>& banned, int n, long long maxSum) {  // banned 是禁用数字，n 是范围上界；maxSum 用 long long 防止求和溢出
        banned.push_back(0);  // 补一个虚拟左边界 0，方便把范围切分成若干段连续可选区间
        banned.push_back(n + 1);  // 补一个虚拟右边界 n+1，保证最后一段能覆盖到 n
        sort(banned.begin(), banned.end());  // 排序后才能用相邻元素切出可选区间
        banned.erase(unique(banned.begin(), banned.end()), banned.end());  // 去重，避免出现长度为负的区间
        int ans = 0;  // ans 记录已经选了多少个数字
        for (int k = 1; k < banned.size(); ++k) {  // 枚举每对相邻的禁用值，中间就是一段连续可选区间
            int i = banned[k - 1], j = banned[k];  // i 是左禁用值，j 是右禁用值，可选范围是 i+1 .. j-1
            int left = 0, right = j - i - 1;  // 二分答案的上下界：这段区间最多能选 j - i - 1 个数
            while (left < right) {  // 二分找最大的可行个数（上中位数写法保证能收敛）
                int mid = left + ((right - left + 1) / 2);  // 取上中位数，避免 left 与 right 相邻时死循环
                if ((i + 1 + i + mid) * 1LL * mid / 2 <= maxSum) {  // 从 i+1 加到 i+mid 的等差数列和；1LL 强制按 long long 计算，防溢出
                    left = mid;  // 和没有超过预算，说明 mid 可行，尝试选更多
                } else {  // 和已经超预算
                    right = mid - 1;  // mid 不可行，往小处继续找
                }  // 二分分支结束
            }  // 二分结束，left 就是这段区间能选的最大个数
            ans += left;  // 累加这段选中的个数
            maxSum -= (i + 1 + i + left) * 1LL * left / 2;  // 从预算里扣掉这段实际消耗的等差数列和
            if (maxSum <= 0) {  // 预算已经用完
                break;  // 后面的区间只会更贵，提前结束
            }  // 预算判断结束
        }  // 所有区间处理完毕
        return ans;  // 返回最多能选的整数个数
    }  // maxCount 方法结束
};  // Solution 类定义结束