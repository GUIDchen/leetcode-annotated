// 题目：1672. 最富有客户的资产总量（Richest Customer Wealth）
// 思路：accounts[i] 是第 i 位客户各账户的资产，逐行求和再取最大值，本质是一次二维遍历。
// 时间复杂度：O(m·n)，每个数字恰好访问一次；空间复杂度：O(1)，只用了若干整型变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏：等价于取两者较大值，手写以避免题解片段依赖 std::max

int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {  // accounts：二维资产表；accountsSize：客户数；accountsColSize：每位客户的账户数
    int ans = INT_MIN;  // 记录当前最大总资产；初值取 INT_MIN，保证第一个客户一定能刷新它
    for (int i = 0; i < accountsSize; i++) {  // 外层循环：逐个客户枚举
        int sum = 0;  // 当前客户的总资产，累加前先清零
        for (int j = 0; j < accountsColSize[i]; j++) {  // 内层循环：枚举该客户名下的每一个账户
            sum += accounts[i][j];  // 把该账户的资产累加进总和
        }  // 内层循环结束，sum 就是第 i 位客户的总资产
        ans = max(ans, sum);  // 用当前总和尝试更新历史最大值
    }  // 外层循环结束，ans 已经是所有客户中的最大值
    return ans;  // 返回最富有客户的资产总量
}  // 函数结束