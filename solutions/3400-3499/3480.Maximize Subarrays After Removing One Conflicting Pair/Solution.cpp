// 3480. 删除一个冲突对后最大子数组数目（Maximize Subarrays After Removing One Conflicting Pair）
// 核心思路：从右往左枚举左端点 a，维护最小的两个冲突右端点 b1、b2，每个 a 贡献 b1 - a 个合法子数组；删除能解开 b1 那个冲突对可额外获得 b2 - b1 个，取所有冲突对中的最大增量加到答案上。
// 复杂度：时间 O(n + m)，空间 O(n)
class Solution {  // 解题类
public:  // 公有成员
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {  // 返回删除至多一个冲突对后合法子数组的最大数目
        vector<vector<int>> g(n + 1);  // g[a] 存放所有左端点为 a 的冲突对的右端点
        for (auto& pair : conflictingPairs) {  // 把每个冲突对按左端点归类
            int a = pair[0], b = pair[1];  // 取出冲突对的两个端点
            if (a > b) {  // 保证 a 是较小的端点
                swap(a, b);  // 交换成 a < b
            }  // 结束交换判断
            g[a].push_back(b);  // 记录到左端点 a 的列表中
        }  // 结束冲突对归类

        vector<long long> cnt(n + 2, 0);  // cnt[b1] 记录删掉造成界 b1 的冲突对时能新增的子数组数
        long long ans = 0, add = 0;  // ans 为不删除时的子数组数，add 为删除一个冲突对的最大增量
        int b1 = n + 1, b2 = n + 1;  // b1、b2 分别为当前最小的两个冲突右端点

        for (int a = n; a > 0; --a) {  // 从右往左枚举左端点 a
            for (int b : g[a]) {  // 遍历所有以 a 为左端点的冲突右端点
                if (b < b1) {  // 出现了更小的冲突右端点
                    b2 = b1;  // 原来的最小变成第二小
                    b1 = b;  // 更新最小右端点
                } else if (b < b2) {  // 否则若介于最小与第二小之间
                    b2 = b;  // 更新第二小右端点
                }  // 结束比较分支
            }  // 结束内层遍历
            ans += b1 - a;  // 左端点 a 处的合法子数组数为 b1 - a
            cnt[b1] += b2 - b1;  // 若删掉造成 b1 的那个冲突对，可额外获得 b2 - b1 个
            add = max(add, cnt[b1]);  // 维护所有可删除冲突对带来的最大增量
        }  // 结束左端点枚举

        ans += add;  // 把最优的那次删除带来的增量加到答案上
        return ans;  // 返回最大子数组数目
    }  // 结束方法
};  // 结束类定义
