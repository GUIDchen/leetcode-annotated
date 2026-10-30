// 题目：4020. 电梯请求 I（Elevator Requests I）
// 思路：电梯从 0 层出发，按顺序处理请求，总耗时就是「0 到第一个请求楼层」加上「每一对相邻请求楼层的楼层差」之和；已经在目标楼层时差为 0，不需要移动。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int elevatorRequests(int n, vector<int>& requests) {  // n：楼层数（楼层编号 0..n-1，本题用不到）；requests：按顺序给出的请求楼层；返回处理完所有请求的总秒数
        int ans = requests[0];  // 电梯从 0 层出发，到第一个请求楼层 requests[0] 需要 requests[0] 秒
        for (int i = 1; i < requests.size(); ++i) {  // 从第二个请求开始，逐段累计移动时间
            ans += abs(requests[i - 1] - requests[i]);  // 相邻两个请求楼层之间的移动时间就是楼层差的绝对值（已在目标楼层时为 0）
        }  // 所有相邻段累计完毕
        return ans;  // 返回处理所有请求所需的总时间
    }  // 方法结束
};  // 类定义结束