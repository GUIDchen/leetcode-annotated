// 4027. 电梯请求 III / Elevator Requests III
// 核心思路：状压 DP，f[mask][j] 表示已处理集合 mask、最后处理请求 j 时的最早完成时间，转移时取“移动后的时刻”与“请求 j 的开放时间”的较大者。
// 复杂度：时间 O(2^m · m^2)，空间 O(2^m · m)（m 为请求数量）。
class Solution {  // 题解类定义
public:  // 公有成员：判题器调用的接口
    long long elevatorRequests(int n, int start, vector<vector<int>>& requests) {  // 返回服务完所有请求所需的最短总时间
        int m = requests.size();  // 请求的数量

        vector<vector<long long>> f(1 << m, vector<long long>(m, 0));  // f[mask][j]：已服务集合为 mask、且最后服务的是请求 j 时的最早完成时间

        for (int i = 0; i < (1 << m); i++) {  // 枚举所有已服务集合（状压状态）
            for (int j = 0; j < m; j++) {  // 枚举最后服务的那一个请求
                if ((i >> j) & 1) {  // 只有当 j 属于集合 i 时，该状态才存在
                    f[i][j] = LLONG_MAX;  // 先置为无穷大，表示尚未松弛
                    int i0 = i ^ (1 << j);  // 去掉 j 之后的前一状态

                    if (i0 == 0) {  // 前驱状态为空，说明 j 是第一个被服务的请求
                        long long d = abs(start - requests[j][1]);  // 从起点 start 移动到请求 j 所在楼层的时间

                        f[i][j] = min(  // 最早完成时间 = max(到达时刻, 请求开放时间)
                            f[i][j],  // 与当前值比较，保留较小者
                            max(d, (long long) requests[j][0]));  // 请求 j 有开放时间，早到必须等待
                    } else {  // 否则需要从上一个被服务的请求转移过来
                        for (int j0 = 0; j0 < m; j0++) {  // 枚举前一个被服务的请求 j0
                            if (j0 != j && ((i >> j0) & 1)) {  // j0 必须不同于 j，且已经包含在集合 i 中
                                long long d = abs(  // 请求 j0 与请求 j 所在楼层之间的移动时间
                                    requests[j0][1] - requests[j][1]);  // 楼层坐标之差的绝对值

                                f[i][j] = min(  // 用 j0 的完成时刻松弛当前状态
                                    f[i][j],  // 保留较小值
                                    max(  // 完成时刻与请求开放时间取最大值
                                        f[i0][j0] + d,  // 从 j0 完成时刻出发、移动到请求 j 的时刻
                                        (long long) requests[j][0]));  // 请求 j 的开放时间，早到需要等待到该时刻
                            }  // 结束本状态的转移
                        }  // 结束前驱请求枚举
                    }  // 结束前一状态分支
                }  // 结束 j 属于集合 i 的判断
            }  // 结束 j 的枚举
        }  // 结束 mask 的枚举

        long long ans = LLONG_MAX;  // 答案初值为无穷大
        for (int j = 0; j < m; j++) {  // 枚举最后一个被服务的请求 j
            ans = min(ans, f[(1 << m) - 1][j]);  // 取所有收尾方式中的最小值
        }  // 结束收尾枚举

        return ans;  // 返回最短完成时间
    }  // 结束函数
};  // 结束类定义